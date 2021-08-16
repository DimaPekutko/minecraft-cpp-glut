#include "Player.hpp"  
	
Player::Player(long double x, long double y, long double z, GameColor color) : GameObject(x,y,z, color)
{
	_camera = new Camera();
    _inventory = new PlayerInventory();
    // _camera->setPosTo(x,y,z);
}

void Player::draw() {
    float yaw = _camera->getYawAngle();
    float speed = _isBoosted ? _speed*2 : _speed;
    _camera->update();
    
    short activeMoveDirectCount = 
        int(_movementDirections.forward) +
        int(_movementDirections.right) +
        int(_movementDirections.back) +
        int(_movementDirections.left);

    // for diagonale movement
    if(activeMoveDirectCount && !(activeMoveDirectCount%2))
        speed /= sqrt(2);

    _preCollisionX = _x;
    _preCollisionY = _y;
    _preCollisionZ = _z;

    if(_movementDirections.forward) {
        _x += cos((yaw+90)*_toRad)*speed;
        _z -= sin((yaw+90)*_toRad)*speed;
    }
    if(_movementDirections.right) {
        _x += cos((yaw)*_toRad)*speed;
        _z -= sin((yaw)*_toRad)*speed;
    }
    if(_movementDirections.back) {
        _x += cos((yaw+270)*_toRad)*speed;
        _z -= sin((yaw+270)*_toRad)*speed;
    }
    if(_movementDirections.left) {
        _x += cos((yaw+180)*_toRad)*speed;
        _z -= sin((yaw+180)*_toRad)*speed;
    }
    if(_isJumping) {
        _jumpDy -= _jumpDyStep;
        _y += _jumpDy;
        if(_jumpDy <= 0) {
            // debug("((");
            _jumpDy = 0.5;
            _isJumping = false;
            _startJumpY = 0;
            _gravity->resetGravity();
        }
    } 

    if(!_isJumping)
        _gravity->updateGravity(&_y);

    glTranslatef(-_x, -_y-GameConfigs::PLAYER_CAMERA_HEIGHT, -_z);
    // debug(int(x));
}	

void Player::moveForward(bool toMove) {
    if (toMove)
        _movementDirections.forward = true;
    else
        _movementDirections.forward = false;
}

void Player::moveRight(bool toMove) {
    if (toMove)
        _movementDirections.right = true;
    else
        _movementDirections.right = false;
}

void Player::moveBack(bool toMove) {
    if (toMove)
        _movementDirections.back = true;
    else
        _movementDirections.back = false;
}

void Player::moveLeft(bool toMove) {
    if (toMove)
        _movementDirections.left = true;
    else
        _movementDirections.left = false;
}

void Player::jump() {
    if(_isJumping)
        return; 
    _isJumping = true;
    _startJumpY = _y;
}

void Player::setBoost(bool toBoost) {
    toBoost ? _isBoosted = true : _isBoosted = false;
    std::cout << "Boost set to " << _isBoosted << "\n";
}

void Player::rotateCamera(int mouseX, int mouseY) {
    if(_lastMouseX || _lastMouseY) {
        float angleX = (float)(GameConfigs::CURRENT_WIDTH/2-mouseX)*GameConfigs::MOUSE_SENSITIVITY;
        float angleY = (float)(GameConfigs::CURRENT_HEIGHT/2-mouseY)*GameConfigs::MOUSE_SENSITIVITY;
        _camera->rotateTo(angleX, angleY);
    }
    _lastMouseX = mouseX;
    _lastMouseY = mouseY;
}

void Player::checkCollisionWithObjects(std::vector<GameObject*> objects) {
    int interactionRange = GameConfigs::PLAYER_INTERACTION_RANGE;
    int objSize = GameConfigs::cubeEdgeSize;
    float playerBodyRadius = GameConfigs::PLAYER_BODY_RADIUS;
    float playerHeight = GameConfigs::PLAYER_CAMERA_HEIGHT;
    double objX, objY, objZ;
    for(int i = 0; i < objects.size(); i++) {
        objX = objects[i]->getX(); 
        objY = objects[i]->getY()-objSize; 
        objZ = objects[i]->getZ()-objSize;
        if (
            (_x-interactionRange <= objX) && (objX <= _x+interactionRange) &&
            (_y-interactionRange <= objY) && (objY <= _y+interactionRange) &&
            (_z-interactionRange <= objZ) && (objZ <= _z+interactionRange)) 
        {
            // main collision logic
            if (
                (_x-objSize <= objX) && (objX <= _x+playerBodyRadius) &&
                (_y-objSize <= objY) && (objY <= _y+playerHeight) &&
                (_z-objSize <= objZ) && (objZ <= _z+playerBodyRadius))
            {
                _y = _preCollisionY;
                // for casual collision
                if(objY+objSize > _y) {
                    _x = _preCollisionX;
                    _z = _preCollisionZ;
                }
                // for gravity collision
                else {
                    _y = objY+objSize;
                    _gravity->resetGravity();
                    // _isJumping = false;
                }
            }
        }
    }
}

PlayerInventory* Player::getInventory() {
    return _inventory;
}

glm::tvec4<double> Player::getPlayerCameraPos() {
    return glm::tvec4<double>(_x, _y+GameConfigs::PLAYER_CAMERA_HEIGHT, _z, _camera->getYawAngle());
}

Player::~Player()
{
	
}