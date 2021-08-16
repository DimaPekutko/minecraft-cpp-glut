#include "GameObject.hpp"  
	
GameObject::GameObject(long double x, long double y, long double z, GameColor color)
{
    _color = color;
	setPos(x,y,z);
     _gravity = new Gravity();
}

void GameObject::draw() {
    // glClear(GL_COLOR_BUFFER_BIT);
    // glColor3f(0.4,0.89,0.31);
    // glutSolidCube(20);
}

void GameObject::setPos(long double x, long double y, long double z) {
    _x = x;
    _y = y;
    _z = z;
}

void GameObject::setSelected(bool select) {
    select ? _isSelected = true : _isSelected = false;
}

long double GameObject::getX() {
    return _x;
}

long double GameObject::getY() {
    return _y;    
}

long double GameObject::getZ() {
    return _z;    
}

bool GameObject::isForwardHitted() {
    return _hitBox.forward;
}

bool GameObject::isBackHitted() {
    return _hitBox.back;
}

bool GameObject::isLeftHitted() {
    return _hitBox.left;
}

bool GameObject::isRightHitted() {
    return _hitBox.right;
}

bool GameObject::isTopHitted() {
    return _hitBox.top;
}

bool GameObject::isBottomHitted() {
    return _hitBox.bottom;
}

void GameObject::setHitBox(bool forward, bool back, bool left, bool right, bool top, bool bottom) {
    _hitBox = {forward, back, left, right, top, bottom};
}

void GameObject::clearHitBox() {
    _hitBox = {false,false,false,false,false,false};
}

GameObject::~GameObject()
{

}