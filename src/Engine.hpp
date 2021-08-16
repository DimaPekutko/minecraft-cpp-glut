#ifndef ENGINE_H
#define ENGINE_H
#pragma once

#include "Headers.h"
#include "Cube.hpp"
#include "Scene.hpp"
#include "Player.hpp"
#include "GameObject.hpp"
#include "RayCaster.hpp"
#include "TextureAtlas.hpp"
#include "PlayerInventory.hpp"
#include "GameInterface.hpp"

// namespace is used because glut is a c language lib. 
// It's means that you can't use glut callback functions in classes.

namespace Engine {
	// extern Scene *_scene;
	// extern Player * _player;
	void _renderEngine();
	void _onKeyPressEngine(unsigned char key, int x, int y);
	void _onMouseMove(int x, int y);
	void _onWindowReshape(int w, int h);
	void _initialize();
	void start(int &argc, char **argv);
}

#endif