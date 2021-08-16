#include "RayCaster.hpp"  
	
RayCaster::RayCaster()
{
	
}

void RayCaster::_setRayEndPos(double *objectX, double *objectY, double *objectZ) {
    int vp[4];
    double mMatrix[16], pMatrix[16];
    float z;

    glGetIntegerv(GL_VIEWPORT, vp);
    int x = GameConfigs::CURRENT_WIDTH/2;
    int y = GameConfigs::CURRENT_HEIGHT/2;
    y = vp[3]-y-1;

    glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, pMatrix);
    glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&z);
    gluUnProject(x,y,z,mMatrix,pMatrix,vp,objectX,objectY,objectZ);
    // system("clear");
    // double ___x = *objectX, ___y = *objectY, ___z = *objectZ;
    // double x =2.0f;
    // debug("x=%f, y=%f, z=%f", *objectX,*objectY,*objectZ);
    // debug(___y);
    // debug(____z);
}

void RayCaster::_checkForHit(GameObject* gameObj, glm::tvec4<double> camPos, glm::tvec3<double> rayEndPos) {
    glm::vec3 raycastVector(camPos.x-rayEndPos.x,camPos.y-rayEndPos.y,camPos.z-rayEndPos.z);
    glm::vec3 rayToObjVector;
    glm::vec3 normalVector;
    double t_multiplier;
    glm::vec3 point;

    int objX = gameObj->getX();
    int objY = gameObj->getY();
    int objZ = gameObj->getZ();
    double plx = camPos.x;
    double ply = camPos.y;
    double plz = camPos.z; 
    bool isObjHitted = false;

    int objSize = GameConfigs::cubeEdgeSize;

    // right 
    rayToObjVector = {plx-(objX+objSize),ply-objY,plz-objZ};
    normalVector = {10.0f,0,0};
    t_multiplier = -(dot(rayToObjVector, normalVector)/dot(raycastVector,normalVector));
    point = {plx+raycastVector[0]*t_multiplier,ply+raycastVector[1]*t_multiplier,plz+raycastVector[2]*t_multiplier};
    if(
        (plx > objX) &&
        (objY-objSize <= point.y && point.y <= objY) &&
        (objZ-objSize <= point.z && point.z <= objZ)
    ) {
        isObjHitted = true;
        gameObj->setHitBox(false,false,false,true,false,false);
    }
    // left
    rayToObjVector = {plx-objX,ply-objY,plz-objZ};
    normalVector = {-10.0f,0,0};
    t_multiplier = -(dot(rayToObjVector, normalVector)/dot(raycastVector,normalVector));
    point = {plx+raycastVector[0]*t_multiplier,ply+raycastVector[1]*t_multiplier,plz+raycastVector[2]*t_multiplier};
    if(
        (plx < objX) &&
        (objY-objSize <= point.y && point.y <= objY) &&
        (objZ-objSize <= point.z && point.z <= objZ)
    ) {
        isObjHitted = true;
        gameObj->setHitBox(false,false,true,false,false,false);
    }
    // forward 
    rayToObjVector = {plx-objX,ply-objY,plz-objZ};
    normalVector = {0,0,10.0f};
    t_multiplier = -(dot(rayToObjVector, normalVector)/dot(raycastVector,normalVector));
    point = {plx+raycastVector[0]*t_multiplier,ply+raycastVector[1]*t_multiplier,plz+raycastVector[2]*t_multiplier};
    if(
        (objX <= point.x && point.x <= objX+objSize) &&
        (objY-objSize <= point.y && point.y <= objY) &&
        (plz > objZ)
    ) {
        isObjHitted = true;
        gameObj->setHitBox(true,false,false,false,false,false);
    }
    // back
    rayToObjVector = {plx-objX,ply-objY,plz-(objZ-objSize)};
    normalVector = {0,0,-10.0f};
    t_multiplier = -(dot(rayToObjVector, normalVector)/dot(raycastVector,normalVector));
    point = {plx+raycastVector[0]*t_multiplier,ply+raycastVector[1]*t_multiplier,plz+raycastVector[2]*t_multiplier};
    if(
        (objX <= point.x && point.x <= objX+objSize) &&
        (objY-objSize <= point.y && point.y <= objY) &&
        (plz < objZ)
    ) {
        isObjHitted = true;
        gameObj->setHitBox(false,true,false,false,false,false);
    }
    // top
    rayToObjVector = {plx-objX,ply-objY,plz-objZ};
    normalVector = {0,10.0f, 0};
    t_multiplier = -(dot(rayToObjVector, normalVector)/dot(raycastVector,normalVector));
    point = {plx+raycastVector[0]*t_multiplier,ply+raycastVector[1]*t_multiplier,plz+raycastVector[2]*t_multiplier};
    if(
        (objX <= point.x && point.x <= objX+objSize) &&
        (ply > objY) &&
        (objZ-objSize <= point.z && point.z <= objZ)
    ) {
        isObjHitted = true;
        gameObj->setHitBox(false,false,false,false,true,false);
    }

    // bottom
    rayToObjVector = {plx-objX,ply-(objY-objSize),plz-objZ};
    normalVector = {0,-10.0f, 0};
    t_multiplier = -(dot(rayToObjVector, normalVector)/dot(raycastVector,normalVector));
    point = {plx+raycastVector[0]*t_multiplier,ply+raycastVector[1]*t_multiplier,plz+raycastVector[2]*t_multiplier};
    if(
        (objX <= point.x && point.x <= objX+objSize) &&
        (ply < objY) &&
        (objZ-objSize <= point.z && point.z <= objZ)
    ) {
        isObjHitted = true;
        gameObj->setHitBox(false,false,false,false,false,true);
    }

    if (isObjHitted)
        _hittedObjects.push_back(gameObj);
}

std::vector<GameObject*> RayCaster::rayCast(glm::tvec4<double> camPos, std::vector<GameObject*> gameObjects, bool restrictByRange) {
    _hittedObjects.clear();
    glm::tvec3<double> rayEndPos;
    _setRayEndPos(&rayEndPos.x, &rayEndPos.y, &rayEndPos.z);
    int interactionRange = GameConfigs::PLAYER_INTERACTION_RANGE;
    double camYawAngle = camPos.w;
    double objX, objY, objZ;
    debug("yaw=%f", camPos.w);
    for(int i = 0; i < gameObjects.size(); i++) {
        objX = gameObjects[i]->getX(); 
        objY = gameObjects[i]->getY(); 
        objZ = gameObjects[i]->getZ();
        if(restrictByRange) {
            // if (
            // (camPos.x-interactionRange <= objX) && (objX <= camPos.x+interactionRange) &&
            // (camPos.y-interactionRange <= objY) && (objY <= camPos.y+interactionRange) &&
            // (camPos.z-interactionRange <= objZ) && (objZ <= camPos.z+interactionRange)) 
            // {
            //     gameObjects[i]->clearHitBox();
            //     _checkForHit(gameObjects[i], camPos, rayEndPos);
            // }
            if(360 > camYawAngle && camYawAngle > 270) {
                if (
                ((int)camPos.x <= objX) && (objX <= (int)camPos.x+interactionRange) &&
                (camPos.y-interactionRange <= objY) && (objY <= camPos.y+interactionRange) &&
                ((int)camPos.z-interactionRange <= objZ) && (objZ <= (int)camPos.z)) 
                {
                    gameObjects[i]->clearHitBox();
                    _checkForHit(gameObjects[i], camPos, rayEndPos);
                }
            }
            else if(270 > camYawAngle && camYawAngle > 180) {
                if (
                ((int)camPos.x <= objX) && (objX <= (int)camPos.x+interactionRange) &&
                (camPos.y-interactionRange <= objY) && (objY <= camPos.y+interactionRange) &&
                ((int)camPos.z <= objZ) && (objZ <= (int)camPos.z+interactionRange)) 
                {
                    gameObjects[i]->clearHitBox();
                    _checkForHit(gameObjects[i], camPos, rayEndPos);
                }
            }
            else if(180 > camYawAngle && camYawAngle > 90) {
                if (
                ((int)camPos.x-interactionRange <= objX) && (objX <= (int)camPos.x) &&
                (camPos.y-interactionRange <= objY) && (objY <= camPos.y+interactionRange) &&
                ((int)camPos.z <= objZ) && (objZ <= (int)camPos.z+interactionRange)) 
                {
                    gameObjects[i]->clearHitBox();
                    _checkForHit(gameObjects[i], camPos, rayEndPos);
                }
            }
            else if(90 > camYawAngle && camYawAngle > 0) {
                if (
                ((int)camPos.x-interactionRange <= objX) && (objX <= (int)camPos.x) &&
                (camPos.y-interactionRange <= objY) && (objY <= camPos.y+interactionRange) &&
                ((int)camPos.z-interactionRange <= objZ) && (objZ <= (int)camPos.z)) 
                {
                    gameObjects[i]->clearHitBox();
                    _checkForHit(gameObjects[i], camPos, rayEndPos);
                }
            }
            // else {
            //     if (
            //     (camPos.x-interactionRange <= objX) && (objX < camPos.x) &&
            //     (camPos.y-interactionRange <= objY) && (objY <= camPos.y+interactionRange) &&
            //     (camPos.z-interactionRange <= objZ) && (objZ <= camPos.z+interactionRange)) 
            //     {
            //         gameObjects[i]->clearHitBox();
            //         _checkForHit(gameObjects[i], camPos, rayEndPos);
            //     }
            // }
        }
        else {
            gameObjects[i]->clearHitBox();
            _checkForHit(gameObjects[i], camPos, rayEndPos);
        }
    }
    return _hittedObjects;
}

RayCaster::~RayCaster()
{
	
}