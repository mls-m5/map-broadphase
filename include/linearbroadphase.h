/*
 * LinearBroadPhase.h
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */

#pragma once
#include "broadphase.h"
#include <list>

class LinearBroadPhase : public BroadPhase {
public:
	LinearBroadPhase();
	virtual ~LinearBroadPhase();

	class Unit* getNearest(Vec &p, double limit) override;
	void add(Unit* u) override;
	void update(double t) override;
	void remove(Unit *u) override;
	void draw() override;

	std::list<Unit *> _units;
};

