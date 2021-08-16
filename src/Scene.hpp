#ifndef SCENE_H
#define SCENE_H
#pragma once

#include "Headers.h"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Cube.hpp"

class Scene  
{
	private:
		std::vector<GameObject*> _gameObjects;
		GameObject* _selectedGameObj = nullptr;
		bool _isDestruction = false;
		void _checkForDestruction();
	public:

		Scene();
		void addToScene(GameObject* obj);
		void removeFromScene(GameObject* obj);
		void render();
		void buildBlock(BlockType blockType);
		void setDestructionStatus(bool status);
		void setSelectedObject(glm::tvec4<double> camPos, std::vector<GameObject*> objects);
		bool selectedObjectExist();
		std::vector<GameObject*> getGameObjects();
		~Scene();

};
#endif