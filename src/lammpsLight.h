//
//  mutLight.h
//  MUTSimulation
//
//  Created by Martin Widyanata on 03.10.14.
//
//

#ifndef __LAMMPSLIGHT_H__
#define __LAMMPSLIGHT_H__


#include <iostream>
#include "ofMain.h"
#include "ofxOsc.h"

enum lammpsState {ST_IDLE,ST_FADEOUT, ST_FADEIN, ST_FLOAT };

struct lammpsEvent {
	lammpsState state;
	int duration;
};

class lammpsLight
{
public:
    lammpsLight();
    ~lammpsLight();
    
    int getLammpsLightId();
	void setLammpsLightId(int id);
    bool getIsActive();
	lammpsEvent getCurrentEvent();
	void setState(lammpsState state);
	void setColor(ofVec3f rgb);
    void setInternalColor(ofVec3f RGB);
	ofVec3f getColor();
	ofVec3f getInternalColor();
   
	void update();
	void stateMachine();
	void addEvent(lammpsEvent lEvent);
    
	ofxOscMessage getOscMessage();
    ofxOscMessage getZeros();

private:
    int lammpsLightID;

	
	int t_state;
	vector<lammpsEvent> events;
	lammpsEvent currentEvent;

	//timer handling
	int t;
	int t_st_start;
	int dt;

	static const int numLEDs = 4;
	ofVec3f rgbO[numLEDs]; //  rgb richtwert. von außen gesetzt
	ofVec3f rgb[numLEDs]; // eigentlicher wert, durch states erzeugt
};

#endif /* defined(__MUTSimulation__mutLight__) */
