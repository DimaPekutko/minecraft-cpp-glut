#include "TextureAtlas.hpp"  

#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"

TextureAtlas::TextureAtlas(const char* path)
{
	_data = stbi_load(path, &_width, &_height, &_componentsPerPixel, 0);
    if(!_data) {
        std::cerr << "Cannot load texture atlas.\n";
        exit(1); 
    }
    _tileSize = sqrt(_width);
    _createTexture();
}

void TextureAtlas::_createTexture() {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned char* TextureAtlas::getData() {
    return _data;
}

unsigned int TextureAtlas::getTexture() {
    return _texture;
}

int TextureAtlas::getWidth() {
    return _width;
}

int TextureAtlas::getHeight() {
    return _height;
}

int TextureAtlas::getTileSize() {
    return _tileSize;
}

TextureAtlas::~TextureAtlas()
{
	stbi_image_free(_data);
}