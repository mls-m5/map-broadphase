/*
 * game.h
 *
 *  Created on: 3 maj 2015
 *      Author: Mattias Larsson Sköld
 */


#pragma once
#include "broadphase.h"
#include "view.h"
#include "particle.h"

#include <list>
#include <memory>

class Game : public MatGui::View {
public:
	friend class Unit;

	Game();

	~Game() {
		clicked.disconnect(this);
	}

	void draw() override;

	void frameCallback(double t);

	void buttonClicked();

	void viewClicked(MatGui::View::PointerArgument arg);


	//Called from layout
	void refresh() override;

	Unit *getNearest(Vec &p, double limit);

	double _textureX = 0, _textureY = 0;
	double _angle = 0;
	double _rotation = 1;
	std::unique_ptr<BroadPhase> _broadPhase;

	std::list<Particle*> _particles;
};
