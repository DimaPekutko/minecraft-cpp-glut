#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H
#pragma once

#include "Headers.h"

class TextureAtlas  
{
	private:
		unsigned char* _data = nullptr;
		unsigned int _texture;
		int _width, 
			_height, 
			_componentsPerPixel,
			_tileSize;
		void _createTexture();
	public:
		TextureAtlas(const char* path);
		unsigned char* getData();
		unsigned int getTexture();
		int getWidth();
		int getHeight();
		int getTileSize();
		~TextureAtlas();

};
#endif