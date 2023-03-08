
#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <Arduino.h>
#include <vector>
#include <DynamixelWorkbench.h>
#include <math.h>


class DynamixelWorkbench;

void inverse_kinematics(float x, float y, float THETA[2]);

#endif; 