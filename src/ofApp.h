#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "mutPlane.h"
#include "ofxOsc.h"
#include "ofxNetwork.h"
#include "ofxJSONElement.h"
#include "mutLight.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp{
    
public:
    void setupOSC();
    void setupPlanes();
    void setupSyphon();
    void setupMIDI();
    void setupTCP();
    void setupLights();
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void exit();
    
    void resetLights();
    int resetTime;
    
    void drawMarker(bool on);
    void showInfo(bool on);
    
    ofVec3f getLightOri(ofQuaternion *quat);
    void setLightOri(ofLight *light, ofVec3f rot);
    
    void sendLightPositions();
    void sendPlanePositions();
    
    ofxOscMessage setLammpWithRGBs(int lammpId, int rgbs[], int length);
    
    void playSoundForChannel(int channel);
    void playSound();
    void playNote(int note, int velocity, int channel);
    
    void allNotesOff();
    void allNotesOffFoChannel(int c);
    void playI();
    void playII();
    void playIII();
    void playIV();
    void playV();
    void playVI();
    void playVII();
    
    
    void setLightPositionAndMovementForMarkerId(mutLight *l, int markerId, ofVec2f touchPoint, int lightMovement);
    void lightDies(mutLight*l);
    void lightCreate(mutLight *l);
    void lightSetMovementPointToPoint(mutLight *l);
    void lightSetMovementSomewhere(mutLight *l);
    
    
    
    ofVec2f normalizedPointToScreenPoint(ofVec2f, ofPlanePrimitive *aPlane);
    
    // ----- Syphon -----
    
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    ofxSyphonServerDirectory syphonServerDirectory;
    
    // ----- Primitives -----
    
    ofEasyCam easyCam;
    
    mutPlane f0;
    mutPlane f1;
    mutPlane f2;
    mutPlane f3;
    mutPlane f4;
    mutPlane f5;
    mutPlane f6;
    mutPlane f7;
    mutPlane f8;
    mutPlane f9;
    mutPlane f4_5;
    
    ofPlanePrimitive *p = NULL;
    
    vector<mutPlane*> planes;
    
    
    
    
    
    ofMaterial material;
    deque<mutLight*> lights;
    long mutLightID;
    
    ofVec3f lerpPos;
    ofVec3f lerpOrientation;
    
    float amnt;
    float speed;
    
    ofVec3f lightOrientationFloor;
    ofVec3f lightOrientationEast;
    ofVec3f lightOrientationWest;
    
    ofxMidiOut midiOut;
    //	int channel;
    
    unsigned int currentPgm;
    int note, velocity;
    int pan, bend, touch, polytouch;
    
    
    float roomLength;
    
    
    
    vector<ofxOscSender*> senders;
    ofxOscSender *oscSenderToClient0;
    ofxOscSender *oscSenderToClient1;
    ofxOscSender *oscSenderToClient2;
    ofxOscSender *oscSenderToClient3;
    ofxOscSender *oscSenderToClient4;
    ofxOscSender *oscSenderToClient5;
    ofxOscSender *oscSenderToClient6;
    ofxOscSender *oscSenderToClient7;
    ofxOscSender *oscSenderToClient8;
    ofxOscSender *oscSenderToClient9;
    ofxOscSender *oscSenderToAudio;
    ofxOscSender *oscSenderToLammp;
    
    string tcpServerIp;
    ofxTCPClient tcpClient;
    int deltaTime = 0;
    int connectTime = 0;
    
    int animationState = 0;
    int animationDeltaTime = 0;
    int animationSwitchStateTime = 0;
    
    ofSoundPlayer soundPlayer;
    
    int orientation;
    
    bool isSyphonOutput = true;
    bool markerOn = true;
    bool infoOn = true;
    bool drawNormals = false;
    bool drawLights = true;
};
