#ifndef STEPPERZ_H
#define STEPPERZ_H

#include <Arduino.h>


//Declare pins
#define PIN_STP 2
#define PIN_DIR 1
#define PIN_MS1 5
#define PIN_MS2 6
#define PIN_EN  7
#define PIN_SW  8 // Limit switch bottom of Z

#define MICRO_STEPS 8 // Default mode of Easydriver
#define STEPS_PER_TURN 200
#define MM_PER_TURN 8


void setupStepper();

//Reset Easy Driver pins to default states
void resetEDPins();

void homeZ();

float updateZOffset(float yPos);

// 1/8th microstep foward mode function
void stepperGoToPos(float goalmm);
#endif
