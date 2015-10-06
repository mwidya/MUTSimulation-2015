//
//  mutPlane.h
//  MUTSimulation
//
//  Created by Martin Widyanata on 31.07.14.
//
//

#ifndef __MUTSimulation__mutPlane__
#define __MUTSimulation__mutPlane__

#include <iostream>
#include "ofMain.h"
#include "ofxSyphon.h"

class mutPlane : public ofPlanePrimitive
{
public:
    bool isAnnounced;
    ofPlanePrimitive plane;
    ofFbo fbo;
    ofxSyphonClient syphonClient;
};

#endif /* defined(__MUTSimulation__mutPlane__) */
