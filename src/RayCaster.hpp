#ifndef RAYCASTER_H
#define RAYCASTER_H
#pragma once

#include "Headers.h"
#include "GameObject.hpp"

class RayCaster  
{
	private:
		void _setRayEndPos(double *objectX, double *objectY, double *objectZ);
		void _checkForHit(GameObject* gameObj, glm::tvec4<double> camPos, glm::tvec3<double> rayEndPos);
		std::vector<GameObject*> _hittedObjects;
	public:
		RayCaster();
		std::vector<GameObject*> rayCast(glm::tvec4<double> camPos, std::vector<GameObject*> gameObjects, bool restrictByRange=true);
		~RayCaster();
};
#endif