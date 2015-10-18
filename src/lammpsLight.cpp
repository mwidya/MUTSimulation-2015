
#include "lammpsLight.h"
#include <math.h>


lammpsLight::lammpsLight(){
    currentEvent.state=ST_IDLE;
}
lammpsLight::~lammpsLight(){
    
}
int lammpsLight::getLammpsLightId(){
    return lammpsLightID;
}
lammpsEvent lammpsLight::getCurrentEvent(){
	return currentEvent;
}

void lammpsLight::setColor(ofVec3f RGB){
	for (int i = 0; i < numLEDs; i++){
		rgbO[i] = RGB;
	}
}

void lammpsLight::setInternalColor(ofVec3f RGB){
    for (int i = 0; i < numLEDs; i++){
        rgb[i] = RGB;
    }
}

ofVec3f lammpsLight::getColor(){
	return rgbO[0];
}
ofVec3f lammpsLight::getInternalColor(){
	return rgb[0];
}
void lammpsLight::setLammpsLightId(int id){
    lammpsLightID = id;
}

void lammpsLight::addEvent(lammpsEvent lEvent){
	// if the current event is in forever mode replace it 
	// otherwise add it to the queue
	if (currentEvent.duration < 0)
		currentEvent = lEvent;
	else
		events.push_back(lEvent);
}

void lammpsLight::stateMachine(){
	t = ofGetElapsedTimeMillis();
	dt = t - t_st_start;

	if (dt > currentEvent.duration && currentEvent.duration > 0){
		// go to next event in queue
		if (events.empty()){
			currentEvent.state = ST_IDLE;
			currentEvent.duration = -1;	//forever
			t_st_start = ofGetElapsedTimeMillis();
		}
		else{
			currentEvent = events[0];
			events.erase(events.begin());
			t_st_start = ofGetElapsedTimeMillis();
		}
	}
}

void lammpsLight::update(){
	stateMachine();

	switch (currentEvent.state){
		case ST_FADEOUT:
			for (int i = 0; i < numLEDs; i++)
				rgb[i] = (1.0f - dt / float(currentEvent.duration)) * rgbO[i];
			break;
		case ST_FADEIN:
			for (int i = 0; i < numLEDs; i++)
				rgb[i] = dt / float(currentEvent.duration) * rgbO[i];
			break;
		case ST_FLOAT:
			for (int i = 0; i < numLEDs; i++){
				rgb[i].x = sin(3 * t) * 0.1f * rgbO[i].x;
				rgb[i].y = sin(2 * t) * 0.1f * rgbO[i].y;
				rgb[i].z = sin(5 * t) * 0.1f * rgbO[i].z;
			}
			break;
		case ST_IDLE:
		default:
			break;
	}
}

ofxOscMessage lammpsLight::getOscMessage(){
	ofxOscMessage msgLammp;
	msgLammp.setAddress("/LAMMPS");
	msgLammp.addIntArg(lammpsLightID);
	for (int i = 0; i<numLEDs; i++) {
		msgLammp.addIntArg(rgb[i].x*255);
		msgLammp.addIntArg(rgb[i].y*255);
		msgLammp.addIntArg(rgb[i].z*255);
	}

	return msgLammp;
}

ofxOscMessage lammpsLight::getZeros(){
    ofxOscMessage msgLammp;
    msgLammp.setAddress("/LAMMPS");
    msgLammp.addIntArg(lammpsLightID);
    for (int i = 0; i<numLEDs; i++) {
        msgLammp.addIntArg(0.0f);
        msgLammp.addIntArg(0.0f);
        msgLammp.addIntArg(0.0f);
    }
    
    return msgLammp;
}