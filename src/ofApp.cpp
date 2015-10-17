#include "ofApp.h"
#include "Constants.h"

#define TCP_NODEJS_IS_LOCAL true
#define OSC_CLIENTS_IS_LOCAL true
#define OSC_AUDIO_IS_LOCAL true
#define OSC_LAMMPS_IS_LOCAL true
#define MIDI_DEVICE_NAME "IAC-Treiber IAC-Bus 1"
//#define MIDI_DEVICE_NAME "MIDISPORT 4x4 Port A"

#define MAX_LIGHTS 4
#define LOOP_LENGTH 3600

// -------------------------------------------------- Setup -------------------------------------------------------
#pragma mark - Setup

void ofApp::setupOSC(){
    
    // const int oscPorts[10] = {6000,6000,6000,6001,6000,6000,6002,6001,6000,6002};
    
    oscSenderToClient0 = new ofxOscSender();
    oscSenderToClient1 = new ofxOscSender();
    oscSenderToClient2 = new ofxOscSender();
    oscSenderToClient3 = new ofxOscSender();
    oscSenderToClient4 = new ofxOscSender();
    oscSenderToClient5 = new ofxOscSender();
    oscSenderToClient6 = new ofxOscSender();
    oscSenderToClient7 = new ofxOscSender();
    oscSenderToClient8 = new ofxOscSender();
    oscSenderToClient9 = new ofxOscSender();
    oscSenderToAudio = new ofxOscSender();
    oscSenderToLammp = new ofxOscSender();
    
    string oscLocalIp = "localhost";
    
    if (OSC_CLIENTS_IS_LOCAL) {
        oscSenderToClient0->setup(oscLocalIp, 6000);
        oscSenderToClient1->setup(oscLocalIp, 6001);
        oscSenderToClient2->setup(oscLocalIp, 6002);
        oscSenderToClient3->setup(oscLocalIp, 6003);
        oscSenderToClient4->setup(oscLocalIp, 6004);
        oscSenderToClient5->setup(oscLocalIp, 6005);
        oscSenderToClient6->setup(oscLocalIp, 6006);
        oscSenderToClient7->setup(oscLocalIp, 6007);
        oscSenderToClient8->setup(oscLocalIp, 6008);
        oscSenderToClient9->setup(oscLocalIp, 6009);
    }
    else{
        oscSenderToClient0->setup("10.0.0.10", 6001);
        oscSenderToClient1->setup("10.0.0.11", 6004);
        oscSenderToClient2->setup("10.0.0.12", 6000);
        oscSenderToClient3->setup("10.0.0.12", 6003);
        oscSenderToClient4->setup("10.0.0.12", 6006);
        oscSenderToClient5->setup("10.0.0.13", 6005);
        oscSenderToClient6->setup("10.0.0.14", 6002);
        oscSenderToClient7->setup("10.0.0.15", 6007);
        oscSenderToClient8->setup("10.0.0.15", 6009);
        oscSenderToClient9->setup("10.0.0.16", 6008);
    }
    
    if (OSC_AUDIO_IS_LOCAL) {
        oscSenderToAudio->setup(oscLocalIp, 6010);
    } else {
        oscSenderToAudio->setup("10.0.0.7", 6010);
    }
    
    if (OSC_LAMMPS_IS_LOCAL) {
        oscSenderToLammp->setup(oscLocalIp, 7000);
    } else {
        oscSenderToLammp->setup("10.0.0.6", 7000);
    }
    
    senders.push_back(oscSenderToClient0);
    senders.push_back(oscSenderToClient1);
    senders.push_back(oscSenderToClient2);
    senders.push_back(oscSenderToClient3);
    senders.push_back(oscSenderToClient4);
    senders.push_back(oscSenderToClient5);
    senders.push_back(oscSenderToClient6);
    senders.push_back(oscSenderToClient7);
    senders.push_back(oscSenderToClient8);
    senders.push_back(oscSenderToClient9);
    
}

void ofApp::setupPlanes(){
    f0.set(f0Long, f0Short);
    f0.setPosition(f4f5Distance*.5 + f3f4Distance + f2Long + f0f1Distance, 0, 0);
    f0.rotate(-90, 0, 1, 0);
    f0.rotate(180, 0, 0, 1);
    
    f1.set(f1Long, f1Short);
    f1.setPosition(f4f5Distance*.5 + f3f4Distance + f2Long, levelDistance + f1Short*.5, 0);
    f1.rotate(90, 0, 1, 0);
    f1.rotate(180, 0,0,1);
    
    f2.set(f2Short, f2Long);
    f2.setPosition(f4f5Distance*.5 + f3f4Distance + f2Long *.5, levelDistance, 0);
    f2.rotate(90, 1, 0, 0);
    f2.rotate(90, 0, 1, 0);
    f2.rotate(180, 0,0,1);
    
    f3.set(f3Long, f3Short);
    f3.setPosition(f4f5Distance*.5 + f3f4Distance, levelDistance + f3Short*.5, -(f2Short-f3Long)*.5f);
    f3.rotate(90, 0, 1, 0);
    f3.rotate(180,1,0,0);
    
    f4.set(f4Long, f4Short);
    f4.setPosition(f4f5Distance * 0.5, 0, 0);
    f4.rotate(90, 0, 1, 0);
    f4.rotate(180, 0,0,1);
    
    f5.set(f5Long, f5Short);
    f5.setPosition(-(f4f5Distance * 0.5), 0, 0);
    f5.rotate(-90, 0, 1, 0);
    f5.rotate(180, 0, 0, 1);
    
    f6.set(f6Long, f6Short);
    f6.setPosition(-(f4f5Distance*.5 + f5f6Distance), levelDistance + f5Short*.5, 0);
    f6.rotate(90, 0, 1, 0);
    f6.rotate(180, 0, 0, 1);
    
    f7.set(f7Long, f7Short);
    f7.setPosition(-(f4f5Distance*.5 + f5f6Distance + f7Short*.5), levelDistance, 0);
    f7.rotate(90, 1, 0, 0);
    f7.rotate(90, 0, 1, 0);
    f7.rotate(180, 0, 0, 1);
    
    f8.set(f8Long, f8Short);
    f8.setPosition(-(f4f5Distance*.5 + f5f6Distance + f7Short), levelDistance + f5Short*.5, 0);
    f8.rotate(-90, 0, 1, 0);
    f8.rotate(180, 0, 0, 1);
    
    f9.set(f8Long, f8Short);
    f9.setPosition(-(f4f5Distance*.5 + f5f6Distance + f7Short + f8f9Distance), 0, 0);
    f9.rotate(90, 0, 1, 0);
    f9.rotate(180, 0, 0, 1);
    
    f4_5.set(f4_5Long, f4_5Short);
    f4_5.setPosition(0, -f4Short*.5, 0);
    f4_5.rotate(90, 1, 0, 0);
    
    planes.push_back(&f0);
    planes.push_back(&f1);
    planes.push_back(&f2);
    planes.push_back(&f3);
    planes.push_back(&f4);
    planes.push_back(&f5);
    planes.push_back(&f6);
    planes.push_back(&f7);
    planes.push_back(&f8);
    planes.push_back(&f9);
    planes.push_back(&f4_5);
    
    
    // Syphon output renders upside down.
    
    if (!isSyphonOutput) {
        for (int i = 0; i < planes.size(); i++) {
            mutPlane *plane = planes[i];
            plane->rotate(180, 0, 0, 1);
        }
    }
    
    
    if (isSyphonOutput) {
        for (int i = 0; i < planes.size(); i++) {
            mutPlane *plane = planes[i];
            plane->fbo.allocate(plane->getWidth(), plane->getHeight());
            plane->syphonClient.setup();
        }
    }
}

void ofApp::setupSyphon(){
    
    syphonServerDirectory.setup();
    ofAddListener(syphonServerDirectory.events.serverAnnounced, this, &ofApp::serverAnnounced);
    ofAddListener(syphonServerDirectory.events.serverUpdated, this, &ofApp::serverUpdated);
    ofAddListener(syphonServerDirectory.events.serverRetired, this, &ofApp::serverRetired);
}

void ofApp::setupMIDI(){
    
    // print the available output ports to the console
    midiOut.listPorts(); // via instance
    //ofxMidiOut::listPorts(); // via static too
    
    // connect
    midiOut.openPort(MIDI_DEVICE_NAME); // by number
    //midiOut.openPort("IAC Driver Pure Data In"); // by name
    //midiOut.openVirtualPort("ofxMidiOut"); // open a virtual port
    
    //	channel = 1;
    currentPgm = 0;
    note = 0;
    velocity = 0;
    pan = 0;
    bend = 0;
    touch = 0;
    polytouch = 0;
    
}

void ofApp::setupTCP(){
    if (TCP_NODEJS_IS_LOCAL) {
        tcpServerIp = "localhost";
    }else
    {
        tcpServerIp = "10.0.0.5";
    }
    tcpClient.setup(tcpServerIp, 12333);
    tcpClient.setMessageDelimiter("\n");
}

void ofApp::setupLights(){
    ofSetGlobalAmbientColor(ofFloatColor(0.5f));
    ofSetSmoothLighting(true);
    
    material.setShininess(120);
    material.setSpecularColor(ofFloatColor(1));
    
    mutLightID = -1;
    
    for (int i = 0; i < 8; i++) {
        mutLight *l = new mutLight();
        l->setMutLightId(i);
        l->setIsActive(false);
        l->setSpotlight();
        l->setSpotlightCutOff(50.0f);
        l->setSpotConcentration(45.0f);
        l->disable();
        lights.push_back(l);
    }
}

void ofApp::setup(){
    
    setupOSC();
    
    setupSyphon();
    
    setupTCP();
    
    setupMIDI();
    
    setupPlanes();
    
    setupLights();
    
    sendPlanePositions();
    
//    drawMarker(markerOn);
    drawMarker(false);
    
    easyCam.setDistance(30000*factor);
    
    roomLength = ofDist(f0.getPosition().x, f0.getPosition().y, f9.getPosition().x, f9.getPosition().y);
    
    lammps.push_back(new lammpsLight());
    lammps.push_back(new lammpsLight());
    lammps.push_back(new lammpsLight());
    lammps.push_back(new lammpsLight());
    
    resetLights();
    
}

// -------------------------------------------------- Moving Lights -------------------------------------------------------
#pragma mark - Moving Lights

void ofApp::update(){
    ofxOscBundle bundle;
    for (int i = 0; i<lammps.size(); i++) {
        lammps[i]->update();
        bundle.addMessage(lammps[i]->getOscMessage());
    }
    oscSenderToLammp->sendBundle(bundle);
    
    if (tcpClient.isConnected())
    {
        string str = tcpClient.receive();
        
        if( str.length() > 0 )
        {
            
            printf("str = %s\n", str.c_str());
            
            ofxJSONElement jsonElement = ofxJSONElement(str);
            ofVec2f touchPoint = ofVec2f(jsonElement["x"].asFloat(), jsonElement["y"].asFloat());
            cout << "touchPoint = " << ofToString(touchPoint) << endl;
            string event = jsonElement["event"].asString();
            int markerId = jsonElement["id"].asInt();
            
            bool isNormedX = (0.0f < touchPoint.x) && (touchPoint.x < 1.0f);
            bool isNormedY = (0 < touchPoint.y) && (touchPoint.y < 1);
            
            if (((event == "press") && isNormedX && isNormedY)) {
                
//                allNotesOff();
                
                mutLightID  = (mutLightID+1) % MAX_LIGHTS;
                
                for (int i = 0; i<lights.size(); i++) {
                    mutLight *l = lights[i];
                    
                    if (l->getMutLightId() == mutLightID) {
                        setLightPositionAndMovementForMarkerId(l, markerId, touchPoint, LIGHT_MOVEMENT_POINT_TO_POINT);
                        resetTime = 0;
                    }
                }
            }
        }
    }
    else
    {
        deltaTime = ofGetElapsedTimeMillis() - connectTime;
        if( deltaTime > 5000 ){
            
            tcpClient.setup(tcpServerIp, 12333);
            tcpClient.setMessageDelimiter("\n");
            
            connectTime = ofGetElapsedTimeMillis();
        }
    }
    
    // WARNING If coordinate is set to fixed value (eg. p->getPosition), every light jumps to this position.
    
    if (p != NULL) {
        
//        ofxOscBundle bundle;
        
        for (int i = 0; i<lights.size(); i++) {
            mutLight *l = lights[i];
            if (l->getIsActive() == true) {
                
                if (l->getStatus() == LIGHT_STATUS_LIVES) {
                    
                    l->setLifetime(ofGetElapsedTimef() - l->getCreationtime());
                    
                    // Light dies after 30 seconds.
                    
                    /*if (l->getLifetime() > 30) {
                     lightDies(l);
                     }*/
                    
                }
                
                if (l->getMovement() == LIGHT_MOVEMENT_POINT_TO_POINT){
                    if (amnt <= 1.0f) {
                        amnt = amnt + speed;
                    }
                    else{
                        l->setStartPosition(l->getTargetPosition());
                        l->setStartOrientation(l->getTargetOrientation());
                    }
                    
                    float x = ofLerp(l->getStartPosition().x, l->getTargetPosition().x, amnt);
                    float y = ofLerp(l->getStartPosition().y, l->getTargetPosition().y, amnt);
                    float z = ofLerp(l->getStartPosition().z, l->getTargetPosition().z, amnt);
                    lerpPos = ofVec3f(x, y, z);
                    l->setPosition(lerpPos);
                    
                    float orientationX = ofLerp(l->getStartOrientation().x, l->getTargetOrientation().x, amnt);
                    float orientationY = ofLerp(l->getStartOrientation().y, l->getTargetOrientation().y, amnt);
                    float orientationZ = ofLerp(l->getStartOrientation().z, l->getTargetOrientation().z, amnt);
                    lerpOrientation = ofVec3f(orientationX, orientationY, orientationZ);
                    l->setOrientation(lerpOrientation);
                }
                
                else if (l->getMovement() == LIGHT_MOVEMENT_SOMEWHERE){
                    
                    /*// Was isn das fŸr nen komisches Zucken ?
                     setLightOri(l, ofVec3f(l->getOrientationEuler().x, l->getOrientationEuler().y , ofGetElapsedTimef()*20));*/
//                    
//                    // ---------------------------------------------- LAMMPS ----------------------------------------
//                    
//                    float r = l->getDiffuseColor().r;
//                    float g = l->getDiffuseColor().g;
//                    float b = l->getDiffuseColor().b;
//                    
////                    float rgbs[] = {r, g, b, r, g, b, r, g, b, r, g, b};
////                    
////                    ofxOscMessage msgLammp = setLammpWithRGBs(l->getMutLightId(), rgbs);
//                    
//                    lammpsLight *light = new lammpsLight();
//                    light->setColor(ofVec3f(r,g,b));
//                    bundle.addMessage(light->getOscMessage());
//                    
//                    // ----------------------------------------------------------------------------------------------
                    
                    if (l->getMutLightId() == 0) {
                        
                        if (animationState == 1) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z - 0.1;
                            setLightOri(l, ori);
                        }
                        if (animationState == 2) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z + 0.1;
                            setLightOri(l, ori);
                        }
                        if (animationState == 3) {
                            ofVec3f vec;
                            vec.x = l->getPosition().x+5;
                            vec.y = l->getPosition().y+5;
                            vec.z = l->getPosition().z+5;
                            l->setPosition(vec);
                        }
                        if (animationState == 4) {
                            ofVec3f vec;
                            vec.x = l->getPosition().x-5;
                            vec.y = l->getPosition().y-5;
                            vec.z = l->getPosition().z-5;
                            l->setPosition(vec);
                        }
                        if (animationState == 5) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.2;
                            ori.y = l->getOrientationEuler().y + 0.2;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState == 6) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.2;
                            ori.y = l->getOrientationEuler().y + 0.2;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState > 7) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z + cos(ofGetElapsedTimef());
                            setLightOri(l, ori);
                        }
                        
                        cout << "l->getOrientationEuler().z = " << l->getOrientationEuler().z * 10000000 << endl;
                        
                    }
                    else if (l->getMutLightId() == 1) {
                        
                        if (animationState == 1) {
                            ofVec3f vec;
                            
                            vec.x = l->getStartPosition().x + cos(ofGetElapsedTimef()) * 10;
                            vec.y = l->getStartPosition().y + sin(ofGetElapsedTimef()) * 10;
                            vec.z = l->getStartPosition().z;
                            
                            l->lookAt(l->getStartPosition());
                            l->setPosition(vec);
                        }
                        if (animationState == 2) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.1;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState == 3) {
                            ofVec3f vec;
                            vec.x = l->getPosition().x+5;
                            vec.y = l->getPosition().y+10;
                            vec.z = l->getPosition().z+5;
                            l->setPosition(vec);
                        }
                        if (animationState == 4) {
                            ofVec3f vec;
                            vec.x = l->getPosition().x-5;
                            vec.y = l->getPosition().y-10;
                            vec.z = l->getPosition().z-5;
                            l->setPosition(vec);
                        }
                        if (animationState == 5) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.2;
                            ori.y = l->getOrientationEuler().y + 0.2;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState == 6) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.2;
                            ori.y = l->getOrientationEuler().y + 0.2;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState > 7) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z + cos(ofGetElapsedTimef());
                            setLightOri(l, ori);
                        }
                        
                        
                    }
                    else if (l->getMutLightId() == 2) {
                        
                        if (animationState == 1) {
                            ofVec3f vec;
                            vec.x = l->getStartPosition().x + cos(ofGetElapsedTimef()) * 10;
                            vec.y = l->getStartPosition().y + sin(ofGetElapsedTimef()) * 10;
                            vec.z = l->getStartPosition().z;
                            l->setPosition(vec);
                        }
                        if (animationState == 2) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.1;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState == 3) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x - 0.1;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState == 4) {
                            ofVec3f vec;
                            vec.x = l->getPosition().x-5;
                            vec.y = l->getPosition().y-10;
                            vec.z = l->getPosition().z-5;
                            l->setPosition(vec);
                        }
                        if (animationState == 5) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.2;
                            ori.y = l->getOrientationEuler().y + 0.2;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState == 6) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.2;
                            ori.y = l->getOrientationEuler().y + 0.2;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState > 7) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z + cos(ofGetElapsedTimef()) * 0.1;
                            setLightOri(l, ori);
                        }
                    }
                    else if (l->getMutLightId() == 3) {
                        
                        if (animationState == 1) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.1;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState == 2) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x - 0.1;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState == 3) {
                            ofVec3f vec;
                            vec.x = l->getPosition().x+0.5;
                            vec.y = l->getPosition().y+1;
                            vec.z = l->getPosition().z+5;
                            l->setPosition(vec);
                        }
                        if (animationState == 4) {
                            ofVec3f vec;
                            vec.x = l->getPosition().x-0.5;
                            vec.y = l->getPosition().y-1;
                            vec.z = l->getPosition().z-5;
                            l->setPosition(vec);
                        }
                        if (animationState == 5) {
                            
                            ofVec3f vec;
                            
                            vec.x = l->getStartOrientation().x;
                            vec.y = l->getStartOrientation().y + ofGetElapsedTimef()*10;
                            vec.z = l->getStartOrientation().z;
                            setLightOri(l, vec);
                        }
                        if (animationState == 6) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x + 0.2;
                            ori.y = l->getOrientationEuler().y + 0.2;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                        if (animationState > 7) {
                            ofVec3f ori;
                            ori.x = l->getOrientationEuler().x - 0.5;
                            ori.y = l->getOrientationEuler().y;
                            ori.z = l->getOrientationEuler().z;
                            setLightOri(l, ori);
                        }
                    }
                    
                    animationDeltaTime = ofGetElapsedTimeMillis() - animationSwitchStateTime;
                    if (animationDeltaTime>5000) {
                        animationState++;
                        animationSwitchStateTime = ofGetElapsedTimeMillis();
                    }
                }
            }
        }
        
//        oscSenderToLammp-> sendBundle(bundle);
    }
    
    resetTime++;
    
    if (resetTime>LOOP_LENGTH) {
        resetLights();
        resetTime = 0;
    }
    
    sendLightPositions();
    
    sendPlanePositions();
    
    if (isSyphonOutput) {
        for (int i = 0; i < planes.size(); i++) {
            mutPlane *plane = planes[i];
            plane->fbo.begin();
            ofClear(255);
            plane->syphonClient.draw(0, 0);
            plane->fbo.end();
        }
    }
}

void ofApp::resetLights(){
    
//    setLightPositionAndMovementForMarkerId(lights[0], markerIds[(int)ofRandom(9.0)], ofVec2f(0.5f, 0.5f), LIGHT_MOVEMENT_SOMEWHERE);
//    setLightPositionAndMovementForMarkerId(lights[1], markerIds[(int)ofRandom(9.0)], ofVec2f(0.5f, 0.5f), LIGHT_MOVEMENT_SOMEWHERE);
//    setLightPositionAndMovementForMarkerId(lights[2], markerIds[(int)ofRandom(9.0)], ofVec2f(0.5f, 0.5f), LIGHT_MOVEMENT_SOMEWHERE);
//    setLightPositionAndMovementForMarkerId(lights[3], markerIds[(int)ofRandom(9.0)], ofVec2f(0.5f, 0.5f), LIGHT_MOVEMENT_SOMEWHERE);
    
    
//    ofxOscBundle bundle;
    for (int i = 0; i<4; i++) {
        mutLight *l = lights[i];
        setLightPositionAndMovementForMarkerId(l, markerIds[(int)ofRandom(9.0)], ofVec2f(0.5f, 0.5f), LIGHT_MOVEMENT_SOMEWHERE);
        l->setDiffuseColor(ofColor(ofRandom(255.0f), ofRandom(255.0f), ofRandom(255.0f)));
        
        
        // ---------------------------------------------- LAMMPS ----------------------------------------
        
        float r = l->getDiffuseColor().r;
        float g = l->getDiffuseColor().g;
        float b = l->getDiffuseColor().b;
        
        //                    float rgbs[] = {r, g, b, r, g, b, r, g, b, r, g, b};
        //
        //                    ofxOscMessage msgLammp = setLammpWithRGBs(l->getMutLightId(), rgbs);
        
//        lammpsLight *light = new lammpsLight();
        lammps[i]->setLammpsLightId(i);
        lammps[i]->setColor(ofVec3f(r,g,b));
//        bundle.addMessage(light->getOscMessage());
        
        // ----------------------------------------------------------------------------------------------
    }
//    oscSenderToLammp-> sendBundle(bundle);
    
    animationState = 0;
    
    
}

void ofApp::lightCreate(mutLight *l){
    
    l->enable();
    l->setCreationtime(ofGetElapsedTimef());
    l->setIsActive(true);
    l->setDiffuseColor(ofColor(ofRandom(255.0f), ofRandom(255.0f), ofRandom(255.0f)));
    l->setStartPosition(l->getPosition());
    l->setTargetPosition(l->getStartPosition());
    l->setStartOrientation(l->getOrientationEuler());
    l->setTargetOrientation(l->getStartOrientation());
    l->setStatus(LIGHT_STATUS_LIVES);
}

void ofApp::setLightOri(ofLight *light, ofVec3f rot){
    ofVec3f xax(1, 0, 0);
    ofVec3f yax(0, 1, 0);
    ofVec3f zax(0, 0, 1);
    ofQuaternion q;
    q.makeRotate(rot.x, xax, rot.y, yax, rot.z, zax);
    light->setOrientation(q);
}

void ofApp::setLightPositionAndMovementForMarkerId(mutLight *l, int markerId, ofVec2f touchPoint, int lightMovement){
    
    
    float planeDistance = 450.0f;
    ofVec2f screenPoint;
    switch (markerId) {
            
        case 691:
        {
            p = planes[0];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x - planeDistance , p->getPosition().y - screenPoint.y, -(p->getPosition().z - screenPoint.x));
            lightOrientationWest = ofVec3f(0,-90,0);
            l->setOrientation(lightOrientationWest);
            orientation = WEST;
            break;
        }
        case 268:
        {
            p = planes[1];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x + planeDistance , p->getPosition().y - screenPoint.y, p->getPosition().z - screenPoint.x);
            lightOrientationEast.set(ofVec3f(0,90,0));
            l->setOrientation(lightOrientationEast);
            orientation = EAST;
            break;
        }
        case 581:
        {
            p = planes[2];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x - screenPoint.y , p->getPosition().y - planeDistance, p->getPosition().z - screenPoint.x);
            lightOrientationFloor = ofVec3f(90, 0, 0);
            setLightOri(l, lightOrientationFloor);
            orientation = FLOOR;
            break;
        }
        case 761:
        {
            p = planes[3];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x - planeDistance , p->getPosition().y - screenPoint.y, -(p->getPosition().z - screenPoint.x));
            lightOrientationWest = ofVec3f(0,-90,0);
            l->setOrientation(lightOrientationWest);
            orientation = WEST;
            break;
        }
        case 528:
        {
            p = planes[4];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x + planeDistance , p->getPosition().y - screenPoint.y, p->getPosition().z - screenPoint.x);
            lightOrientationEast.set(ofVec3f(0,90,0));
            l->setOrientation(lightOrientationEast);
            orientation = EAST;
            break;
        }
        case 286:
        {
            p = planes[5];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x - planeDistance , p->getPosition().y - screenPoint.y, -(p->getPosition().z - screenPoint.x));
            lightOrientationWest = ofVec3f(0,-90,0);
            l->setOrientation(lightOrientationWest);
            orientation = WEST;
            break;
        }
        case 484:
        {
            p = planes[6];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x + planeDistance , p->getPosition().y - screenPoint.y, p->getPosition().z - screenPoint.x);
            lightOrientationEast.set(ofVec3f(0,90,0));
            l->setOrientation(lightOrientationEast);
            orientation = EAST;
            break;
        }
        case 99:
        {
            p = planes[7];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x - screenPoint.y , p->getPosition().y-planeDistance, p->getPosition().z - screenPoint.x);
            lightOrientationFloor = ofVec3f(90, 0, 0);
            setLightOri(l, lightOrientationFloor);
            orientation = FLOOR;
            break;
        }
        case 222:
        {
            p = planes[8];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x - planeDistance , p->getPosition().y - screenPoint.y, -(p->getPosition().z - screenPoint.x));
            lightOrientationWest = ofVec3f(0,-90,0);
            l->setOrientation(lightOrientationWest);
            orientation = WEST;
            break;
        }
        case 903:
        {
            p = planes[9];
            screenPoint = normalizedPointToScreenPoint(ofVec2f(touchPoint.x, touchPoint.y), p);
            l->setPosition(p->getPosition().x + planeDistance , p->getPosition().y - screenPoint.y, p->getPosition().z - screenPoint.x);
            lightOrientationEast.set(ofVec3f(0,90,0));
            l->setOrientation(lightOrientationEast);
            orientation = EAST;
            break;
        }
        default:
            break;
    }
    
    
    playSoundForChannel(l->getMutLightId() + 1);
    
    if (l->getStatus()==LIGHT_STATUS_DEAD) {
        lightCreate(l);
    }
    
    l->setMovement(lightMovement);
    
    if (l->getMovement() == LIGHT_MOVEMENT_POINT_TO_POINT){
        
        l->setTargetPosition(l->getPosition());
        
        if (orientation == FLOOR) {
            l->setTargetOrientation(lightOrientationFloor);
        }
        else if (orientation == EAST){
            l->setTargetOrientation(lightOrientationEast);
        }
        else if (orientation == WEST){
            l->setTargetOrientation(lightOrientationWest);
        }
        
        speed = ofRandom(0.001f, 0.01f);
        amnt = 0;
    }
    
//    cout << "l->getMutLightId() = " << l->getMutLightId() << endl;
//    cout << "l->getIsActive() = " << ofToString(l->getIsActive()) << endl;
//    cout << "l->getPosition() = " << ofToString(l->getPosition()) << endl;
}

void ofApp::lightDies(mutLight*l){
    
    allNotesOffFoChannel(l->getMutLightId() + 1);
    
    l->setIsActive(false);
    l->setLifetime(0.0f);
    l->setStatus(LIGHT_STATUS_DEAD);
}

ofxOscMessage ofApp::setLammpWithRGBs(int lammpId, float rgbs[]){
    mutLight *l = lights[lammpId];
    
    ofxOscMessage msgLammp;
    msgLammp.setAddress("/LAMMPS");
    msgLammp.addIntArg(lammpId);
    for (int i = 0; i<12; i++) {
        msgLammp.addIntArg(rgbs[i]*255);
    }
    
    return msgLammp;
}

float normalizeValue(float min, float max, float val){
    
    float minPosX = min;
    float maxPosX = max;
    float maxDistance = minPosX - maxPosX;
    float offset = 0;
    float currentPosLightX = val;
    float interpolationVal = -(currentPosLightX - maxPosX) / abs(minPosX - maxPosX) + 1;
    float currentPosX = maxDistance * interpolationVal + offset;
    float normalizedValX = currentPosX / maxDistance;
    
    return normalizedValX;
    
}

void ofApp::sendLightPositions(){
    for (int i = 0; i<lights.size(); i++) {
        mutLight *l = lights[i];
        //        if (l->getLightID()==0) {
        //            cout << ofToString(l->getOrientationEuler().z*100000000) << endl;
        //        }
        
        float normalizedValX = normalizeValue(planes[0]->getPosition().x, planes[9]->getPosition().x, l->getPosition().x); // min = 3370, max = - 4640
        float normalizedValY = normalizeValue(planes[4]->getPosition().x + 1000, planes[3]->getPosition().x - 1000, l->getPosition().y);
        float normalizedValZ = normalizeValue(planes[0]->getPosition().x + 1000, planes[0]->getPosition().x - 1000, l->getPosition().z);
        float normalizedValRotY = normalizeValue(0, 360, l->getOrientationEuler().y);
        
        ofxOscMessage msgAudio;
        msgAudio.setAddress("/light"+ofToString(i)+"/position");
        msgAudio.addFloatArg(normalizedValX);
        msgAudio.addFloatArg(normalizedValY);
        msgAudio.addFloatArg(normalizedValZ);
        msgAudio.addFloatArg(normalizedValRotY);
        
        oscSenderToAudio->sendMessage(msgAudio);
        
        for (int j = 0; j < senders.size(); j++) {
            ofxOscMessage m;
            m.setAddress("/light/position");
            m.addFloatArg(l->getPosition().x);
            m.addFloatArg(l->getPosition().y);
            m.addFloatArg(l->getPosition().z);
            m.addFloatArg(l->getDiffuseColor().r);
            m.addFloatArg(l->getDiffuseColor().g);
            m.addFloatArg(l->getDiffuseColor().b);
            m.addFloatArg(l->getSpotlightCutOff());
            m.addFloatArg(l->getSpotConcentration());
            m.addInt64Arg(l->getMutLightId());
            m.addIntArg((int)l->getIsActive());
            m.addFloatArg(l->getOrientationEuler().x);
            m.addFloatArg(l->getOrientationEuler().y);
            m.addFloatArg(l->getOrientationEuler().z);
            senders[j]->sendMessage(m);
        }
    }
}

void ofApp::sendPlanePositions(){
    
    for (int j = 0; j < senders.size(); j++) {
        for (int i = 0; i < planes.size(); i++) {
            ofxOscMessage m2;
            string oscAddress = "f"+ofToString(i)+"/position";
            m2.setAddress(oscAddress);
            m2.addFloatArg(planes[i]->getPosition().x);
            m2.addFloatArg(planes[i]->getPosition().y);
            m2.addFloatArg(planes[i]->getPosition().z);
            
            senders[j]->sendMessage(m2);
        }
    }
}

ofVec2f ofApp::normalizedPointToScreenPoint(ofVec2f normalizedPoint, ofPlanePrimitive *aPlane){
    ofVec2f point;
    
    point.x = normalizedPoint.x * aPlane->getWidth() - aPlane->getWidth()*.5f;
    point.y = normalizedPoint.y * aPlane->getHeight() - aPlane->getHeight()*.5f;
    
    return point;
    
    
}

// -------------------------------------------------- Sound -------------------------------------------------------
#pragma mark - Sound

void ofApp::playI(){
    cout << "playI" << endl;
    
    note = 60;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    int channel = 1;
    playNote(note, velocity, channel);
    note = 64;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 67;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 71;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    
}

void ofApp::playII(){
    cout << "playII" << endl;
    
    note = 62;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    int channel = 1;
    playNote(note, velocity, channel);
    note = 65;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 69;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 72;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    
}

void ofApp::playIII(){
    cout << "playIII" << endl;
    
    note = 64;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    int channel = 1;
    playNote(note, velocity, channel);
    note = 67;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 71;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 74;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    
}

void ofApp::playIV(){
    cout << "playIV" << endl;
    
    note = 65;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    int channel = 1;
    playNote(note, velocity, channel);
    note = 69;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 72;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 76;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    
}

void ofApp::playV(){
    cout << "playV" << endl;
    
    note = 67;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    int channel = 1;
    playNote(note, velocity, channel);
    note = 71;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 74;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 77;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    
}

void ofApp::playVI(){
    cout << "playVI" << endl;
    
    note = 69;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    int channel = 1;
    playNote(note, velocity, channel);
    note = 72;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 76;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 79;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    
}

void ofApp::playVII(){
    cout << "playVII" << endl;
    
    note = 71;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    int channel = 1;
    playNote(note, velocity, channel);
    note = 74;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 77;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    note = 81;//ofMap(key, 48, 122, 0, 127);
    velocity = ofRandom(20, 100);
    playNote(note, velocity, channel);
    
}

void ofApp::allNotesOffFoChannel(int c){
    
    for (int i = 48; i<=122; i++) {
        //ofMap(key, 48, 122, 0, 127);
        note = i;
        velocity = 0;
        playNote(note, velocity, c);
    }
    
}

void ofApp::allNotesOff(){
    for (int c = 1; c <= 3; c++) {
        allNotesOffFoChannel(c);
    }
}

void ofApp::playNote(int note, int velocity, int channel){
    
    midiOut.sendNoteOn(channel, note,  velocity);
    
}

void ofApp::playSoundForChannel(int channel){
    
    //    allNotesOff();
    
    /*int i = ofRandom(1, 7);
     
     if (i==1) {
     playI();
     }else if (i==2){
     playII();
     }else if (i==3){
     playIII();
     }else if (i==4){
     playIV();
     }else if (i==5){
     playV();
     }else if (i==6){
     playVI();
     }else if (i==7){
     playVII();
     }*/
    
    int note = ofRandom(36, 71); // c1 - b3
    int velocity = ofRandom(20, 100);
    
    allNotesOffFoChannel(channel);
    playNote(note, velocity, channel);
    
}

void ofApp::playSound(){
    
    allNotesOff();
    
    /*int i = ofRandom(1, 7);
     
     if (i==1) {
     playI();
     }else if (i==2){
     playII();
     }else if (i==3){
     playIII();
     }else if (i==4){
     playIV();
     }else if (i==5){
     playV();
     }else if (i==6){
     playVI();
     }else if (i==7){
     playVII();
     }*/
    
    int note = ofRandom(40, 80);//ofMap(key, 48, 122, 0, 127);
    int velocity = ofRandom(20, 100);
    for (int c = 1; c<=MAX_LIGHTS; c++) {
        playNote(note, velocity, c);
    }
}

// -------------------------------------------------- Draw / Events -------------------------------------------------------
#pragma mark - Update / Draw / Events

void ofApp::draw(){
    ofClear(0, 0, 0);
    
    
    ofEnableDepthTest();
    
    easyCam.begin();
    
    if (isSyphonOutput) {
        for (int i = 0; i < planes.size(); i++) {
            mutPlane *plane = planes[i];
            if (plane->isAnnounced) {
                plane->fbo.getTextureReference().bind();
                plane->mapTexCoordsFromTexture(plane->fbo.getTextureReference());
                plane->draw();
                plane->fbo.getTextureReference().unbind();
            }else{
                plane->draw();
            }
            
            if (drawNormals) {
                ofSetColor(0);
                plane->drawNormals(50);
                ofSetColor(255);
            }
        }
    }
    else{
        
        material.begin();
        
        for (int i = 0; i < planes.size(); i++) {
            mutPlane *plane = planes[i];
            plane->draw();
            
            if (drawNormals) {
                ofSetColor(0);
                plane->drawNormals(50);
                ofSetColor(255);
            }
        }
    }
    
    if (drawLights) {
        for (int i = 0; i<lights.size(); i++) {
            if (lights[i]->getIsActive()) {
                lights[i]->draw();
            }
        }
    }
    
    material.end();
    
    easyCam.end();
    
    ofDisableDepthTest();
    
    ofDrawBitmapString("Animationstate " + ofToString(animationState), 20, ofGetHeight()-40);
    
    if (tcpClient.isConnected())
    {
        ofDrawBitmapString("TCP is connected to IP " + ofToString(tcpServerIp) + " on port " + ofToString(12333) , 20, ofGetHeight()-20);
    }
    else
    {
        ofDrawBitmapString("TCP is NOT connected to IP " + ofToString(tcpServerIp) + " on port " + ofToString(12333) , 20, ofGetHeight()-20);
    }
}

void ofApp::keyPressed(int key){
    
    if (key=='r') {
        resetLights();
    }
    
    if (key == 'n') {
        drawNormals = !drawNormals;
    }
    
    if (key == 'p') {
        playSound();
    }
    
    if (key == 'l'){
        drawLights = !drawLights;
    }
    
    if (key == 't') {
        sendPlanePositions();
    }
    
    if (key == 'm') {
        
        markerOn = !markerOn;
        drawMarker(markerOn);
    }
    if (key == 'i') {
        
        infoOn = !infoOn;
        showInfo(infoOn);
    }
    
    if (key == 's') {
        isSyphonOutput = !isSyphonOutput;
    }
    if (key == '1') {
        allNotesOffFoChannel(1);
    }
    if (key == '2') {
        allNotesOffFoChannel(2);
    }
    if (key == '3') {
        allNotesOffFoChannel(3);
    }
    if (key == '4') {
        allNotesOffFoChannel(4);
    }
}

void ofApp::drawMarker(bool on){
    ofxOscMessage m;
    m.setAddress("/marker/on");
    m.addIntArg(on);
    for(int i = 0; i<senders.size(); i++){
        senders[i]->sendMessage(m);
    }
    
}

void ofApp::showInfo(bool on){
    ofxOscMessage m;
    m.setAddress("/info/on");
    m.addIntArg(on);
    for(int i = 0; i<senders.size(); i++){
        senders[i]->sendMessage(m);
    }
    
}

void ofApp::mouseDragged(int x, int y, int button){
    
}

// -------------------------------------------------- Syphon Callbacks --------------------------------------------
#pragma mark - Syphon Callbacks

void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg){
    for (auto &dir : arg.servers) {
        /*ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;*/
        if(dir.serverName == "f0"){
            planes[0]->isAnnounced = true;
            planes[0]->syphonClient.set(dir);
        }else if(dir.serverName == "f1"){
            planes[1]->isAnnounced = true;
            planes[1]->syphonClient.set(dir);
        }else if(dir.serverName == "f2"){
            planes[2]->isAnnounced = true;
            planes[2]->syphonClient.set(dir);
        }else if(dir.serverName == "f3"){
            planes[3]->isAnnounced = true;
            planes[3]->syphonClient.set(dir);
        }else if(dir.serverName == "f4"){
            planes[4]->isAnnounced = true;
            planes[4]->syphonClient.set(dir);
        }else if(dir.serverName == "f5"){
            planes[5]->isAnnounced = true;
            planes[5]->syphonClient.set(dir);
        }else if(dir.serverName == "f6"){
            planes[6]->isAnnounced = true;
            planes[6]->syphonClient.set(dir);
        }else if(dir.serverName == "f7"){
            planes[7]->isAnnounced = true;
            planes[7]->syphonClient.set(dir);
        }else if(dir.serverName == "f8"){
            planes[8]->isAnnounced = true;
            planes[8]->syphonClient.set(dir);
        }else if(dir.serverName == "f9"){
            planes[9]->isAnnounced = true;
            planes[9]->syphonClient.set(dir);
        }
    }
}

void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg){
    for (auto &dir : arg.servers) {
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
}

void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg){
    for (auto &dir : arg.servers) {
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
        if(dir.serverName == "F0"){
            planes[0]->isAnnounced = false;
        }else if(dir.serverName == "F1"){
            planes[1]->isAnnounced = false;
        }else if(dir.serverName == "F2"){
            planes[2]->isAnnounced = false;
        }else if(dir.serverName == "F3"){
            planes[3]->isAnnounced = false;
        }else if(dir.serverName == "F4"){
            planes[4]->isAnnounced = false;
        }else if(dir.serverName == "F5"){
            planes[5]->isAnnounced = false;
        }else if(dir.serverName == "F6"){
            planes[6]->isAnnounced = false;
        }else if(dir.serverName == "F7"){
            planes[7]->isAnnounced = false;
        }else if(dir.serverName == "F8"){
            planes[8]->isAnnounced = false;
        }else if(dir.serverName == "F9"){
            planes[9]->isAnnounced = false;
        }
    }
}

void ofApp::exit(){
    allNotesOff();
}














