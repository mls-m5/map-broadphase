/*
 * Particle.cpp
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */

#include "particle.h"
#include <cstdlib>
#include "draw.h"
#include "game.h"
#include "unit.h"

const double radius = 2;

using namespace MatGui;

Particle::Particle(Game *game) :
	_pos(rand() % 200 + 100, rand() % 200 + 100),
	_vel(.01 * (rand() % 100 - 50), .01 * (rand() % 100 - 50)),
	_game(game){

}

Particle::~Particle() {
}

void Particle::draw() {
	if (_pos.x > 0 and _pos.y > 0) {
		if (_pos.x < 500 and _pos.y < 500) {
			drawRect( {  _pos.x - radius, _pos.y - radius }, 0, radius * 2
					, radius * 2, DrawStyle::Filled);
		}
	}

	if (_target) {
		drawLine(_pos.x, _pos.y, _target->pos().x, _target->pos().y);
	}
}

void Particle::update(double t) {
	_pos += _vel;

	_target = _game->getNearest(_pos, 500);

	if (_target) {

		auto d = _target->pos() - _pos;
		_vel += d / _vel.abs2() / 100.;
	}
}
