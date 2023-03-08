#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <Arduino.h>
#include <DynamixelWorkbench.h>
#include <vector>
#include <Servo.h>
#include <AccelStepper.h>
#include <math.h>




class DynamixelWorkbench;

int32_t degrees_to_int(const float angle);

void move_to_pos(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float angles[2]);

bool move_to_pos_wait(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float angles[2]);

int move_Z(AccelStepper& stepperZ, int stepCurrentPos, int stepNextPos);

void init_motors(DynamixelWorkbench&  motor, const std::vector<uint8_t>& motor_IDs);

void go_to_home_arm(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float motor_angles[2]);

void home_Z(AccelStepper& stepperZ, int stepCurrentPos, int SWITCH_PIN);

void start_motors(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs);

void stop_motors(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs);

void open_gripper(Servo& servoGripper);

void close_gripper(Servo& servoGripper);

void index_color(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, int nbAvailableColors, int colorIndex);

void pick(Servo& servoGripper);

void place(Servo& servoGripper);

void pixel_to_pos(int pixel, float pixelPos[2]);



#endif;