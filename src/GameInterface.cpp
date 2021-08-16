#include "GameInterface.hpp"  
	
GameInterface::GameInterface(Player* player)
{
	_player = player;
    _slotsCount = _player->getInventory()->getSlotsCount();
}

void GameInterface::_setOrthographicView() {
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,GameConfigs::CURRENT_WIDTH,GameConfigs::CURRENT_HEIGHT,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
}

void GameInterface::_drawInventorySlots(float x, float y) {
    int selecedBlockIndex = _player->getInventory()->getSelectedSlotIndex();
    float texsize = (float)1/_blocksTextureAtlas->getTileSize();
    BlockType itemBlockType;
    float tex_x;
    float tex_y;
    float vertex[] = {x,y, x+_slotSize,y, x,y+_slotSize, x,y+_slotSize, x+_slotSize,y, x+_slotSize,y+_slotSize};

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _blocksTextureAtlas->getTexture());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        for(int i = 0; i < _slotsCount; i++) {
            if(_player->getInventory()->getBlockTypeByIndex(&itemBlockType, i)) {
                tex_x = itemBlockType.textureAtlasPositions[0][0]*texsize;
                tex_y = itemBlockType.textureAtlasPositions[0][1]*texsize;
                float textureVertex[] = 
                {
                    tex_x,tex_y+texsize,  tex_x+texsize,tex_y+texsize,  tex_x,tex_y,
                    tex_x,tex_y,  tex_x+texsize,tex_y+texsize,  tex_x+texsize,tex_y
                };
                glVertexPointer(2, GL_FLOAT, 0, vertex);
                glTexCoordPointer(2, GL_FLOAT, 0, textureVertex);
                selecedBlockIndex == i ? glColor4ub(255,255,255,255) : glColor4ub(100,100,100,255);
                glDrawArrays(GL_TRIANGLES,0,6);
            }

            for(int j = 0; j < 12; j +=2)
                vertex[j] += _slotSize;
        }
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void GameInterface::_drawCenterPointer() {
    glColor4ub(255,255,255,255);
    float x = GameConfigs::CURRENT_WIDTH/2-_centerPointerSize/2;
    float y = GameConfigs::CURRENT_HEIGHT/2-_centerPointerSize/2;
    glBegin(GL_POLYGON);
        glVertex2d(x,y);
        glVertex2d(x+_centerPointerSize,y);
        glVertex2d(x+_centerPointerSize,y+_centerPointerSize);
        glVertex2d(x,y+_centerPointerSize);
    glEnd();
}

void GameInterface::draw() {
    _setOrthographicView();
    _drawInventorySlots(GameConfigs::CURRENT_WIDTH/2-(_slotsCount*_slotSize/2),GameConfigs::CURRENT_HEIGHT-_slotSize);
    _drawCenterPointer();
}

void GameInterface::setBlocksTextureAtlas(TextureAtlas* blocksTextureAtlas) {
    _blocksTextureAtlas = blocksTextureAtlas;
}

GameInterface::~GameInterface()
{
	
}