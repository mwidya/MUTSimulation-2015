//
//  Constants.h
//  MUTSimulation
//
//  Created by Martin Widyanata on 16.10.15.
//
//

#ifndef MUTSimulation_Constants_h
#define MUTSimulation_Constants_h






float factor = 0.2f;
// 1.0 = 1 meter
float levelDistance = 3000*factor;
float f0f1Distance = 2150*factor;
float f3f4Distance = 8600*factor;
float f4f5Distance = 4300*factor;
float f5f6Distance = 11100*factor;
float f8f9Distance = 6000*factor;
float f0Long = 4300*factor;
float f0Short = 1700*factor;
float f1Long = 4300*factor;
float f1Short = 1700*factor;
float f2Long = 3950*factor;
float f2Short = 4300*factor;
float f3Long = 3000*factor;
float f3Short = 1700*factor;
float f4Long = 3000*factor;
float f4Short = 1700*factor;
float f5Long = 3000*factor;
float f5Short = 1700*factor;
float f6Long = 4300*factor;
float f6Short = 1700*factor;
float f7Long = 4300*factor;
float f7Short = 3950*factor;
float f8Long = 4300*factor;
float f8Short = 1700*factor;
float f9Long = 4300*factor;
float f9Short = 1700*factor;

float f4_5Short = 3000*factor;
float f4_5Long = 4300*factor;

int markerIds[10] = {691, 268, 581, 761, 528, 286, 484, 99, 222, 903};

enum{
    FLOOR,
    EAST,
    WEST,
    
};

enum{
    LIGHT_STATUS_LIVES,
    LIGHT_STATUS_DEAD,
};

enum{
    LIGHT_MOVEMENT_POINT_TO_POINT,
    LIGHT_MOVEMENT_SOMEWHERE,
};

#endif
