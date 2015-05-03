/*
 * game.cpp
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */

#include <game.h>
#include "matsig.h"
#include "unit.h"
#include "particle.h"
#include "roamingbroadphase.h"
#include "linearbroadphase.h"

using namespace MatGui;
using namespace std;

Game::Game() {
	if (1) {
		_broadPhase.reset(new RoamingBroadphase);
	} else {
		_broadPhase.reset(new LinearBroadPhase); //For comparison
	}
	clicked.connect(this, &Game::viewClicked);
	for (int i = 0; i < 1000; ++i) {
		_broadPhase->add(new Unit);
	}

	for (int i = 0; i < 100; ++i) {
		_particles.push_back(new Particle(this));
	}
}

void Game::draw() {
	_broadPhase->draw();

	for (auto it: _particles) {
		it->draw();
	}
}

void Game::frameCallback(double t) {
	_broadPhase->update(t);

	for (auto it: _particles) {
		it->update(t);
	}
}

void Game::buttonClicked() {
}

void Game::viewClicked(View::PointerArgument arg) {
}

void Game::refresh() {
}

Unit* Game::getNearest(Vec& p, double limit) {
	return _broadPhase->getNearest(p, limit);
}
