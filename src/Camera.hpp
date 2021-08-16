#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "Headers.h"

class Camera  
{
	private:
		// Camera always situated at (0,0,0), so camera position can be updated with coords offsets.
		float
			_yawAngle = 0,
			_pitchAngle = 0;
	public:
		Camera();
		void rotateTo(float horAngle, float verAngle);
		void update();
		float getPitchAngle();
		float getYawAngle();
		~Camera();

};
#endif