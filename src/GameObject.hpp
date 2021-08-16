#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once

#include "Headers.h"
#include "Gravity.hpp"

class GameObject
{
	private:
		struct HitBox {
			bool forward,back,left,right,top,bottom;
		} _hitBox;
	protected:
		Gravity* _gravity;
		long double _x, _y, _z;
		GameColor _color;
		bool _isSelected = false;
	public:
		GameObject(long double x, long double y, long double z, GameColor color=GameConfigs::COLOR_RED);
		virtual void draw();
		virtual void setPos(long double x, long double y, long double z);
		void setSelected(bool select);
		long double getX();
		long double getY();
		long double getZ();
		bool isForwardHitted();
		bool isBackHitted();
		bool isLeftHitted();
		bool isRightHitted();
		bool isTopHitted();
		bool isBottomHitted();
		void setHitBox(bool forward, bool back, bool left, bool right, bool top, bool bottom);
		void clearHitBox();
		virtual ~GameObject();
};
#endif