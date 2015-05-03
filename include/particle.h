/*
 * Particle.h
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */

#pragma once
#include "vec.h"

class Particle {
public:
	Particle(class Game *game);
	virtual ~Particle();

	void draw();
	void update(double t);

	Vec _pos, _vel;
	class Game *_game;
	class Unit *_target = nullptr;
};

