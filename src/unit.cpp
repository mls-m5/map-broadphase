/*
 * unit.cpp
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */

#include "draw.h"
#include "unit.h"
#include "math.h"
#include "roamingbroadphase.h"
#include <cstdlib>

using namespace MatGui;

Unit::Unit() :
		_pos(rand() % 200 + 100, rand() % 200 + 100),
		_vel(.01 * (rand() % 100 - 50), .01 * (rand() % 100 - 50)),
		_radius(rand() % 8){
}

Unit::~Unit() {

}

void Unit::draw() {
	//Apparently open-gl calls is really expensive
	//so this is one of the best optimizations in the program if there is no
	//collision checking
	if (_pos.x > 0 and _pos.y > 0) {
		if (_pos.x < 500 and _pos.y < 500) {
			drawRect( {  _pos.x - _radius, _pos.y - _radius }, 0, _radius * 2
					, _radius * 2, DrawStyle::Filled);
		}
	}
//	drawLine(_pos.x, _pos.y, _space->pos().x, _space->pos().y);

}

void Unit::update(double t) {
	_pos += _vel;
}
