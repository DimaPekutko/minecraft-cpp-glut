#ifndef CUBE_H
#define CUBE_H
#pragma once

#include "GameObject.hpp"	
#include "TextureAtlas.hpp"

class Cube : public GameObject
{
	private:
		static TextureAtlas* _blocksTextureAtlas;
		BlockType _blockType;
	public:
		Cube(long double x, long double y, long double z, BlockType blockType);
		static void setBlocksTextureAtlas(TextureAtlas* atlas);
		void draw();
		~Cube();

};
#endif