/*
 * unit.h
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */


#pragma once

#include "vec.h"

class Unit {
public:
	Unit();
	virtual ~Unit();

	void draw();
	void update(double t);

	Vec &pos() {
		return _pos;
	}

	auto space() {
		return _space;
	}

	void space(class Space *space) {
		_space = space;
	}

	auto radius() {
		return _radius;
	}

protected:
	Vec _pos;
	Vec _vel;
	double _radius;

	class Space *_space;
};
