#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <Arduino.h>
#include <vector>
#include <DynamixelWorkbench.h>

class DynamixelWorkbench;

int32_t degrees_to_int(const float angle);

void move_to_pos(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float angles[4]);

bool move_to_pos_wait(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float angles[4]);

void init_motors(DynamixelWorkbench&  motor, const std::vector<uint8_t>& motor_IDs, float motor_angles[4], const uint8_t LINEAR_PIN);

void go_to_home(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float motor_angles[4], const uint8_t LINEAR_PIN);

void start_motors(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs);

void stop_motors(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs);

#endif;