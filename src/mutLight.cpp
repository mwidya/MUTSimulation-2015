//
//  mutLight.cpp
//  MUTSimulation
//
//  Created by Martin Widyanata on 03.10.14.
//
//

#include "mutLight.h"

enum{
    LIGHT_STATUS_LIVES,
    LIGHT_STATUS_DEAD,
};

enum{
    LIGHT_MOVEMENT_POINT_TO_POINT,
    LIGHT_MOVEMENT_SOMEWHERE,
};

mutLight::mutLight(){
    this->mutLightID = -1;
    this->isActive = false;
    this->status = LIGHT_STATUS_DEAD;
    this->lifetime = 0.0f;
    this->startPosition.set(0, 0, 0);
    this->targetPosition.set(0, 0, 0);
    this->startOrientation.set(0, 0, 0);
    this->targetOrientation.set(0, 0, 0);
}

mutLight::~mutLight(){
    
}

int mutLight::getMutLightId(){
    return mutLightID;
}
bool mutLight::getIsActive(){
    return isActive;
}
int mutLight::getStatus(){
    return status;
}
float mutLight::getLifetime(){
    return lifetime;
}
float mutLight::getCreationtime(){
    return creationtime;
}
int mutLight::getMovement(){
    return movement;
}
ofVec3f mutLight::getStartPosition(){
    return startPosition;
}
ofVec3f mutLight::getTargetPosition(){
    return targetPosition;
}
ofVec3f mutLight::getStartOrientation(){
    return startOrientation;
}
ofVec3f mutLight::getTargetOrientation(){
    return targetOrientation;
}


void mutLight::setMutLightId(int mutLightID){
    this->mutLightID = mutLightID;
}
void mutLight::setIsActive(bool val){
    this->isActive = val;
}
void mutLight::setStatus(int status){
    this->status = status;
}
void mutLight::setLifetime(float lifetime){
    this->lifetime = lifetime;
}
void mutLight::setCreationtime(float time){
    this->creationtime = time;
}
void mutLight::setMovement(int movement){
    this->movement = movement;
}
void mutLight::setStartPosition(ofVec3f startPosition){
    this->startPosition = startPosition;
}
void mutLight::setTargetPosition(ofVec3f targetPosition){
    this->targetPosition = targetPosition;
}
void mutLight::setStartOrientation(ofVec3f startOrientation){
    this->startOrientation = startOrientation;
}
void mutLight::setTargetOrientation(ofVec3f targetOrientation){
    this->targetOrientation = targetOrientation;
}