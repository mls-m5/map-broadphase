/*
 * broadphase.h
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */

#pragma once
#include <broadphase.h>
#include <list>
#include "draw.h"

class Unit;
class Space {
public:
	virtual ~Space() {}

	virtual void add(Unit *u) = 0;
	virtual void remove(Unit *u) = 0;

	virtual Vec &pos() = 0;
};

class PartSpace : public Space {
public:
	PartSpace();
	virtual ~PartSpace() {}

	void add(Unit* u) override;

	void remove(Unit *u) {
		_units.remove(u);
	}

	void calculateCenter();

	void calculateRadius();

	void draw();

	Vec &pos() override {
		return _pos;
	}

	Unit* getNearest(Vec&, double limit, double *returnDistance);

protected:
	std::list <Unit*> _units;
	Vec _pos;
	double _radius = 1;
};

class RoamingBroadphase : public BroadPhase {
public:
	RoamingBroadphase();
	virtual ~RoamingBroadphase();
	
	Unit* getNearest(Vec &p, double limit) override;

	PartSpace *getNearestPart(Vec &p);

	void add(Unit* u) override;

	void update(double t) override;
	void remove(Unit *u) override;


	//to get for-each to work
	auto inline begin() { //using c++14 auto-standard
		return _units.begin();
	}
	auto inline end() {
		return _units.end();
	}

	void draw() override;

	std::list <Unit *> _units;
	std::list <PartSpace *> _parts;
};
