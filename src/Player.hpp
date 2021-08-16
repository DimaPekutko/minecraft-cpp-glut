#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "GameObject.hpp"
#include "Camera.hpp"
#include "PlayerInventory.hpp"

class Player : public GameObject
{
	private:
		Camera *_camera;
		PlayerInventory* _inventory;
		float _speed = 0.15;
		float _boostPercent = 0.25;
		bool _isBoosted = false;
		bool _isJumping = false;
		float _startJumpY = 0;
		float _jumpDy = 0.5;
		float _jumpDyStep = 0.05;
		struct {
			bool forward = false;
			bool right = false;
			bool back = false;
			bool left = false;
		} _movementDirections;
		int 
			_lastMouseX = 0, 
			_lastMouseY = 0;
		double
			_preCollisionX = 0,
			_preCollisionY = 0,
			_preCollisionZ = 0;
		float _toRad = 3.14/180.0;
	public:
		Player(long double x, long double y, long double z, GameColor color=GameConfigs::COLOR_RED);
		void draw();
		void moveForward(bool toMove=true);
		void moveRight(bool toMove=true);
		void moveBack(bool toMove=true);
		void moveLeft(bool toMove=true);
		void jump();
		void setBoost(bool toBoost=true);
		void rotateCamera(int mouseX, int mouseY);
		void checkCollisionWithObjects(std::vector<GameObject*> objects);
		PlayerInventory* getInventory();
		glm::tvec4<double> getPlayerCameraPos();
		~Player();
};
#endif