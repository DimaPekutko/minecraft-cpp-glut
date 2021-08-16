#include "Cube.hpp"  

TextureAtlas* Cube::_blocksTextureAtlas = nullptr;

Cube::Cube(long double x, long double y, long double z, BlockType blockType) : GameObject(x, y, z)
{
    _blockType = blockType;
}

void Cube::setBlocksTextureAtlas(TextureAtlas* atlas) {
    _blocksTextureAtlas = atlas;
}

void Cube::draw() {
    auto renderMode = GameConfigs::debugMode ? GL_LINE_STRIP : GL_TRIANGLES;
    auto cubeEdgeSize = GameConfigs::cubeEdgeSize;

    float size = GameConfigs::cubeEdgeSize;
    float x = _x;
    float y = _y;
    float z = _z;
    
    float texsize = (float)1/_blocksTextureAtlas->getTileSize();
    float tex_x = _blockType.textureAtlasPositions[0][0]*texsize;
    float tex_y = _blockType.textureAtlasPositions[0][1]*texsize;
    float vertex[] = 
    {
        x,y,z,  x+size,y,z,  x,y-size,z,                                      // front
        x,y-size,z,  x+size,y,z,  x+size,y-size,z,

        x,y,z-size,  x+size,y,z-size,  x,y-size,z-size,                       // back
        x,y-size,z-size,  x+size,y,z-size,  x+size,y-size,z-size,

        x+size,y,z, x+size,y,z-size,  x+size,y-size,z,                        // right
        x+size,y-size,z,  x+size,y,z-size,  x+size,y-size,z-size,

        x,y,z, x,y,z-size,  x,y-size,z,                                       // left
        x,y-size,z,  x,y,z-size,  x,y-size,z-size,

        x,y,z,  x,y,z-size,  x+size,y,z,                                      // top
        x+size,y,z,  x,y,z-size,  x+size,y,z-size,

        x,y-size,z,  x,y-size,z-size,  x+size,y-size,z,                       // bottom
        x+size,y-size,z,  x,y-size,z-size,  x+size,y-size,z-size
    };
    
    float textureVertex[] = 
    {
        tex_x,tex_y+texsize,  tex_x+texsize,tex_y+texsize,  tex_x,tex_y,        // front
        tex_x,tex_y,  tex_x+texsize,tex_y+texsize,  tex_x+texsize,tex_y,

        tex_x,tex_y+texsize,  tex_x+texsize,tex_y+texsize,  tex_x,tex_y,        // back
        tex_x,tex_y,  tex_x+texsize,tex_y+texsize,  tex_x+texsize,tex_y,
        
        tex_x,tex_y+texsize,  tex_x+texsize,tex_y+texsize,  tex_x,tex_y,        // right
        tex_x,tex_y,  tex_x+texsize,tex_y+texsize,  tex_x+texsize,tex_y,

        tex_x,tex_y+texsize,  tex_x+texsize,tex_y+texsize,  tex_x,tex_y,        // left
        tex_x,tex_y,  tex_x+texsize,tex_y+texsize,  tex_x+texsize,tex_y,
    
        tex_x,tex_y+texsize,  tex_x+texsize,tex_y+texsize,  tex_x,tex_y,        // top
        tex_x,tex_y,  tex_x+texsize,tex_y+texsize,  tex_x+texsize,tex_y,
        
        tex_x,tex_y+texsize,  tex_x+texsize,tex_y+texsize,  tex_x,tex_y,        // bottom
        tex_x,tex_y,  tex_x+texsize,tex_y+texsize,  tex_x+texsize,tex_y,
    };

    // glColor4ub(255, 255, 255, 255);

    // if(_isSelected) {
    //     system("clear");
    //     std::cout << "top = " << isTopHitted() << "\n";
    //     std::cout << "bottom = " << isBottomHitted() << "\n";
    //     std::cout << "right = " << isRightHitted() << "\n";
    //     std::cout << "left = " << isLeftHitted() << "\n";
    //     std::cout << "forward = " << isForwardHitted() << "\n";
    //     std::cout << "back = " << isBackHitted() << "\n";
    //     debug("POSITION");
    //     debug(_x);
    //     debug(_y);
    //     debug(_z);
    // }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _blocksTextureAtlas->getTexture());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertex);
        glTexCoordPointer(2, GL_FLOAT, 0, textureVertex);
        _isSelected ? glColor4ub(100,100,100,255) : glColor4ub(255,255,255,255);
        glDrawArrays(GL_TRIANGLES,0,36);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindTexture(GL_TEXTURE_2D, 0);

   
    // glBegin(renderMode);
    // //  glColor4ub(255, 0, 0, 1);
    //     glVertex3f(x, y, z);
    //     glVertex3f(x+cubeEdgeSize, y, z);
    //     glVertex3f(x, y-cubeEdgeSize, z);
    // glEnd();
    // glBegin(renderMode);
    //     // glColor3f(0.62, 0.75, 0.54);
    //     glVertex3f(x+cubeEdgeSize, y, z);
    //     glVertex3f(x, y-cubeEdgeSize, z);
    //     glVertex3f(x+cubeEdgeSize, y-cubeEdgeSize, z);
    // glEnd();
    // // Back
    // glBegin(renderMode);
    //     // glColor3f(0.431, 0.32, 0.56);
    //     glVertex3f(x, y, z-cubeEdgeSize);
    //     glVertex3f(x+cubeEdgeSize, y, z-cubeEdgeSize);
    //     glVertex3f(x, y-cubeEdgeSize, z-cubeEdgeSize);
    // glEnd();
    // glBegin(renderMode);
    //     // glColor3f(0.83, 0.48, 0.5);
    //     glVertex3f(x+cubeEdgeSize, y, z-cubeEdgeSize);
    //     glVertex3f(x, y-cubeEdgeSize, z-cubeEdgeSize);
    //     glVertex3f(x+cubeEdgeSize, y-cubeEdgeSize, z-cubeEdgeSize);
    // glEnd();
    // // Right
    // glBegin(renderMode);
    //     // glColor3f(0.91, 0.21, 0.63);
    //     glVertex3f(x+cubeEdgeSize, y, z);
    //     glVertex3f(x+cubeEdgeSize, y, z-cubeEdgeSize);
    //     glVertex3f(x+cubeEdgeSize, y-cubeEdgeSize, z);
    // glEnd();
    // glBegin(renderMode);
    //     // glColor3f(0.23, 0.43, 0.15);
    //     glVertex3f(x+cubeEdgeSize, y, z-cubeEdgeSize);
    //     glVertex3f(x+cubeEdgeSize, y-cubeEdgeSize, z-cubeEdgeSize);
    //     glVertex3f(x+cubeEdgeSize, y-cubeEdgeSize, z);
    // glEnd();
    // // Left
    // glBegin(renderMode);
    //     // glColor3f(0.31, 0.44, 0.33);
    //     glVertex3f(x, y, z);
    //     glVertex3f(x, y, z-cubeEdgeSize);
    //     glVertex3f(x, y-cubeEdgeSize, z);
    // glEnd();
    // glBegin(renderMode);
    //     // glColor3f(0.75, 0.63, 0.65);
    //     glVertex3f(x, y, z-cubeEdgeSize);
    //     glVertex3f(x, y-cubeEdgeSize, z);
    //     glVertex3f(x, y-cubeEdgeSize, z-cubeEdgeSize);
    // glEnd();
    // // Top
    // glBegin(renderMode);
    //     // glColor3f(0.11, 0.15, 0.78);
    //     glVertex3f(x, y-cubeEdgeSize, z);
    //     glVertex3f(x, y-cubeEdgeSize, z-cubeEdgeSize);
    //     glVertex3f(x+cubeEdgeSize, y-cubeEdgeSize, z);
    // glEnd();
    // glBegin(renderMode);
    //     // glColor3f(0.25, 0.93, 0.94);
    //     glVertex3f(x+cubeEdgeSize, y-cubeEdgeSize, z);
    //     glVertex3f(x, y-cubeEdgeSize, z-cubeEdgeSize);
    //     glVertex3f(x+cubeEdgeSize, y-cubeEdgeSize, z-cubeEdgeSize);
    // glEnd();
    // // Bottom
    // glBegin(renderMode);
    //     // glColor3f(0.46, 0.23, 0.89);
    //     glVertex3f(x, y, z);
    //     glVertex3f(x, y, z-cubeEdgeSize);
    //     glVertex3f(x+cubeEdgeSize, y, z);
    // glEnd();
    // glBegin(renderMode);
    //     // glColor3f(0.78, 0.51, 0.48);
    //     glVertex3f(x+cubeEdgeSize, y, z);
    //     glVertex3f(x, y, z-cubeEdgeSize);
    //     glVertex3f(x+cubeEdgeSize, y, z-cubeEdgeSize);
    // glEnd();
}

Cube::~Cube()
{
    
}