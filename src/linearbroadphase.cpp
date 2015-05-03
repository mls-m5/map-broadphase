/*
 * LinearBroadPhase.cpp
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */

#include <linearbroadphase.h>
#include "unit.h"
#include <limits>

LinearBroadPhase::LinearBroadPhase() {

}

LinearBroadPhase::~LinearBroadPhase() {
}

class Unit* LinearBroadPhase::getNearest(Vec& p, double limit) {
	Unit *nearest = nullptr;
	double distance2 = limit * limit;

	for (auto it: _units) {
		auto t = it->pos().distance2d2(p);
		if (t < distance2) {
			nearest = it;
			distance2 = t;
		}
	}

	return nearest;
}

void LinearBroadPhase::add(Unit* u) {
	_units.push_back(u);
}

void LinearBroadPhase::draw() {
	for (auto it: _units) {
		it->draw();
	}
}

void LinearBroadPhase::update(double t) {
	for (auto it: _units) {
		it->update(t);
	}
}

void LinearBroadPhase::remove(Unit* u) {
	_units.remove(u);
}
