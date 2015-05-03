/*
 * broadphase.cpp
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */

#include <roamingbroadphase.h>
#include "draw.h"
#include "unit.h"
#include <limits>
#include <cstdlib>

using namespace MatGui;

RoamingBroadphase::RoamingBroadphase() {
	for (int i = 0; i < 20; ++i) {
		_parts.push_back(new PartSpace);
	}
}

RoamingBroadphase::~RoamingBroadphase() {
}

void PartSpace::calculateCenter() {
	Vec center;
	if (_units.empty()) {
		return;
	}
	int count = 0;
	for (auto unit: _units) {
		center += unit->pos();
		++count;
	}

	center /= count;

	_pos = _pos * .9 + center * .1; //Move slowly to the new center
//	_pos = center;
}

void PartSpace::calculateRadius() {
	auto max = .1;
	double objectRadius = 0;
	for (auto it : _units) {
		auto d = it->pos().distance2d2(_pos);
		if (d > max) {
			max = d;
			objectRadius = it->radius(); //We add this later to avoid sqrt-ing it
		}
	}
	_radius = sqrt(max) + objectRadius;
}

Unit* RoamingBroadphase::getNearest(Vec &p, double limit) {
	auto nearestDistance = limit * limit;
	Unit *unit = nullptr;

	for (auto it: _parts) {
		double t;
		auto tu = it->getNearest(p, limit, &t);
		if (t < nearestDistance) {
			nearestDistance = t;
			unit = tu;
		}
	}

	return unit;
}

void PartSpace::draw() {
	MatGui::drawElipse(_pos.x - _radius, _pos.y - _radius, 0, _radius * 2, _radius * 2, DrawStyle::Lines);
}

Unit* PartSpace::getNearest(Vec &p, double limit, double *returnDistance) {
	auto nearestDistance = limit * limit;

	auto distanceToCenter = _pos.distance2d2(p);
	auto maxDistance = limit + _radius;

	//Check if any unit could possibly be near enough
	if (distanceToCenter > maxDistance * maxDistance) {
		*returnDistance = nearestDistance;
		return nullptr;
	}

	Unit *unit = nullptr;
	for (auto it: _units) {
		auto t = it->pos().distance2d2(p);
		if (t < nearestDistance) {
			nearestDistance = t;
			unit = it;
		}
	}
	*returnDistance = nearestDistance;

	return unit;
}

PartSpace* RoamingBroadphase::getNearestPart(Vec& p) {
	PartSpace *nearest = nullptr;
	double distance2 = std::numeric_limits<double>::max();

	for (auto it: _parts) {
		auto t = it->pos().distance2d2(p);
		if (t < distance2) {
			nearest = it;
			distance2 = t;
		}
	}

	return nearest;
}

void RoamingBroadphase::remove(Unit* u) {
	_units.remove(u);
}

void RoamingBroadphase::draw() {
	for (auto it: *this) {
		it->draw();
	}

	for (auto it: _parts) {
		it->draw();
	}
}

void RoamingBroadphase::update(double t) {
	for (auto it: _parts) {
		it->calculateCenter();
		it->calculateRadius();
	}

	for (auto it: *this) {
		it->update(t);

		if (rand() % 100 > 90) { //Limit this expensive calculation
			auto part = getNearestPart(it->pos());
			if (it->space() != part) {
				it->space()->remove(it);
				part->add(it);
			}
		}
	}
}

PartSpace::PartSpace():
	_pos(rand() % 300, rand() % 300){

}

void RoamingBroadphase::add(Unit* u) {
	_units.push_back(u);

	//todo: fix this
	auto part = getNearestPart(u->pos());
	part->add(u);
}

void PartSpace::add(Unit* u) {
	_units.push_back(u);
	u->space(this);
}
