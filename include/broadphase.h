/*
 * broadphase.h
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */


#pragma once
#include "vec.h"

class BroadPhase {
public:
	virtual ~BroadPhase() {}
	virtual class Unit* getNearest(Vec &p, double limit) = 0;
	virtual void add(Unit* u) = 0;
	virtual void update(double t) = 0;
	virtual void remove(Unit *u) = 0;
	virtual void draw() = 0;
};

