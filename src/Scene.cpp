#include "Scene.hpp"  
	
Scene::Scene()
{
	
}

void Scene::_checkForDestruction() {
    if(_isDestruction && _selectedGameObj) {
        removeFromScene(_selectedGameObj);
        _selectedGameObj = nullptr;
    }
}

void Scene::addToScene(GameObject *obj) {
    _gameObjects.push_back(obj);
    // if(typeid(Player) == typeid(*obj))
    //     _player = obj;
}

void Scene::removeFromScene(GameObject* obj) {
    _gameObjects.erase(std::remove(_gameObjects.begin(), _gameObjects.end(), obj), _gameObjects.end());
    delete obj;
}

void Scene::render() {
    _checkForDestruction();
    for (int i = 0; i < _gameObjects.size(); i++) {
        _gameObjects[i]->draw();
    }
    // long int
    //     playerX = _player->getX(),
    //     playerY = _player->getY(),
    //     playerZ = _player->getZ(),
    //     gameObjX = 0,
    //     gameObjY = 0,
    //     gameObjZ = 0,
    //     interactionRange = GameConfigs::PLAYER_INTERACTION_RANGE;
    // unsigned int 
    //     color[4] = {0,0,0,255},
    //     colorStep = 1,
    //     colorIndex = 0;
    // bool finded = false;
        // if(
        //     (playerX-interactionRange <= gameObjX) && (gameObjX <= playerX+interactionRange) &&
        //     (playerY-interactionRange <= gameObjY) && (gameObjY <= playerY+interactionRange) &&
        //     (playerZ-interactionRange <= gameObjZ) && (gameObjZ <= playerZ+interactionRange)           
        // ) {
            
        // }
        // 0) draw
        // 1) grid
        // 2) compare with center pixel
        //      if compared -> set selected
        // 3) replace grid with previous




        //  _gameObjects[i]->draw();
        // if(_gameObjects[i] != _player) {
        //     gameObjX = _gameObjects[i]->getX(); 
        //     gameObjY = _gameObjects[i]->getY();
        //     gameObjZ = _gameObjects[i]->getZ();
        //     // cheking if game object situated in player's interaction range
        //     if (
        //         (playerX-interactionRange <= gameObjX) && (gameObjX <= playerX+interactionRange) &&
        //         (playerY-interactionRange <= gameObjY) && (gameObjY <= playerY+interactionRange) &&
        //         (playerZ-interactionRange <= gameObjZ) && (gameObjZ <= playerZ+interactionRange)
        //     ) {
       //         color[colorIndex] += step;
        //         if(color[colorIndex] == 255 && colorIndex != 3) {
        //             colorIndex++;
        //         } 
        //         _gameObjects[i]->setMaskColorId({color[0],color[1],color[2],color[3]});
        //         GLubyte clr[3];
        //         glReadPixels(GameConfigs::CURRENT_WIDTH/2.0, GameConfigs::CURRENT_HEIGHT/2.0, 1, 1, 
        //         GL_RGB, GL_UNSIGNED_BYTE, clr);
        //         // debug((int)clr[2]);
        //         GameColor _objMaskColorId = _gameObjects[i]->getMaskColorId();
        //         if(_objMaskColorId.r == (int)clr[0] && _objMaskColorId.g == (int)clr[1] && _objMaskColorId.b == (int)clr[2]) {
        //             // _gameObjects[i]->setMaskColorId({255,255,255,255});
        //             if(_selectedGameObj) {
        //                 _selectedGameObj->setSelectedStatus(false);
        //             }
        //             _selectedGameObj = _gameObjects[i];
        //             _selectedGameObj->setSelectedStatus(true);
        //         }                    
        //     }
        //     else {
        //         // debug("no");
        //         _gameObjects[i]->setMaskColorId({0,0,200,255});
        //     }
        // }
}

void Scene::buildBlock(BlockType blockType) {
    if(!_selectedGameObj)
        return;
    double x = _selectedGameObj->getX(),
        y = _selectedGameObj->getY(),
        z = _selectedGameObj->getZ();
    if(_selectedGameObj->isTopHitted())
        y += 1;
    else if(_selectedGameObj->isBottomHitted())
        y -= 1;
    else if(_selectedGameObj->isRightHitted())
        x += 1;
    else if(_selectedGameObj->isLeftHitted())
        x -= 1;
    else if(_selectedGameObj->isForwardHitted())
        z += 1;
    else if(_selectedGameObj->isBackHitted())
        z -= 1;
    addToScene(new Cube(x,y,z,blockType));
    _selectedGameObj->setSelected(false);
    _selectedGameObj = nullptr;
}


void Scene::setDestructionStatus(bool status) {
    status ? _isDestruction = true : _isDestruction = false;
}

void Scene::setSelectedObject(glm::tvec4<double> camPos, std::vector<GameObject*> objects) {
    if(!objects.size()) {
        if(_selectedGameObj)
            _selectedGameObj->setSelected(false);
        _selectedGameObj = nullptr;
        return;
    }
    
    // trying to find the nearest to the player camera game object from vector
    // and set it to _selectedGameObj

    double dx=0, dy=0, dz=0, minDistance=1000, distance = 0;
    // double pitchAngle = camPos.w;
    GameObject* nearestGameObj = nullptr;
    GameObject* hittedObj = nullptr;
    for(int i = 0; i < objects.size(); i++) {
        hittedObj = objects[i];
        dx = camPos.x - hittedObj->getX();
        dy = camPos.y - hittedObj->getY();
        dz = camPos.z - hittedObj->getZ();
        distance = sqrtf(dx*dx+dy*dy+dz*dz);
        if(distance <= minDistance) {
            // this check need to execute moments with hitted object behind player
            // if(
            //     (pitchAngle >= 0 && camPos.y <= hittedObj->getY()-1) ||
            //     (pitchAngle < 0 && camPos.y >= hittedObj->getY()-1)
            // ) {
                minDistance = distance;
                nearestGameObj = hittedObj;   
            // }
        }
    }
    if(_selectedGameObj)
        _selectedGameObj->setSelected(false);
    _selectedGameObj = nearestGameObj;
    if(nearestGameObj) 
        _selectedGameObj->setSelected(true);
}

bool Scene::selectedObjectExist() {
    return _selectedGameObj ? true : false;
}

std::vector<GameObject*> Scene::getGameObjects() {
    return _gameObjects;
}

Scene::~Scene()
{
	
}