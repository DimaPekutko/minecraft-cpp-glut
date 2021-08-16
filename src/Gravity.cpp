#include "Gravity.hpp"  
	
Gravity::Gravity()
{
	
}

void Gravity::updateGravity(long double* y) {
    _dy += _dyStep;
    if(_dy >= _maxDy) {
        _dy = _maxDy;
    }
    *y -= _dy;
}

void Gravity::resetGravity() {
    _dy = 0;
}

Gravity::~Gravity()
{
	
}