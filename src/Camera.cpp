#include "Camera.hpp"  
	
Camera::Camera()
{
    
}

void Camera::rotateTo(float horAngle, float verAngle) {
    _pitchAngle += verAngle;
    _yawAngle += horAngle;

    if(_yawAngle < 0) {
        _yawAngle = 360-_yawAngle;
    }
    else if(_yawAngle >= 360) {
        _yawAngle = _yawAngle-360;
    }

    if (GameConfigs::MOUSE_MIN_VERTICAL_ANGLE > _pitchAngle)
        _pitchAngle = GameConfigs::MOUSE_MIN_VERTICAL_ANGLE;
    else if (_pitchAngle > GameConfigs::MOUSE_MAX_VERTICAL_ANGLE)
        _pitchAngle = GameConfigs::MOUSE_MAX_VERTICAL_ANGLE;
}	

void Camera::update() {
    glRotatef(-_pitchAngle, 1, 0, 0);
	glRotatef(-_yawAngle, 0, 1, 0);
}

float Camera::getPitchAngle() {
    return _pitchAngle;
}

float Camera::getYawAngle() {
    return _yawAngle;
}

Camera::~Camera()
{
	
}