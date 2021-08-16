#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H
#pragma once

#include "Headers.h"
#include "Player.hpp"
#include "TextureAtlas.hpp"	

class GameInterface  
{
	private:
		Player* _player;
		TextureAtlas* _blocksTextureAtlas;
		float _slotSize = 50;
		float _slotsCount = 0;
		float _centerPointerSize = 5;
		void _setOrthographicView();
		void _drawInventorySlots(float x, float y);
		void _drawCenterPointer();
	public:
		GameInterface(Player* player);
		void draw();
		void setBlocksTextureAtlas(TextureAtlas* blocksTextureAtlas);
		~GameInterface();

};
#endif