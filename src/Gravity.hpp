#ifndef GRAVITY_H
#define GRAVITY_H
#pragma once

#include "Headers.h"

class Gravity  
{
	private:
		float _dy = 0,
			  _dyStep = 0.020,
			  _maxDy = 0.98;
	public:

		Gravity();
		void updateGravity(long double* y);
		void resetGravity();
		~Gravity();

};
#endif