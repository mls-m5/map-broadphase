/*
 * game.cpp
 *
 *  Created on: 24 jan 2015
 *      Author: Mattias Larsson Sköld
 */


#include <game.h>
#include <roamingbroadphase.h>
#include "application.h"
#include "window.h"
#include "draw.h"
#include "texture.h"

#include <iostream>
#include <list>
#include <cmath>

#include "unit.h"

using namespace MatGui;
using namespace std;




int main(int argc, char**argv) {
	Application app(argc, argv);

	Window *window = new Window("mattias");
	auto game = new Game;

	window->addChild(game);

	app.frameUpdate.connect(game, &Game::frameCallback);

	app.mainLoop();

}
