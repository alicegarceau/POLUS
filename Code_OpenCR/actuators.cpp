#include "actuators.hpp"
#include "stepperZ.hpp"
#include "inverseKinematics.hpp"

const int crayonPick = 3;
const int crayonRetreat = 74;
const int crayonApproach = 60;
const int nbAvailableColors = 20;
const int pixelApproach = 22;
const int pixelDraw = 16;

/// Custom function to convert an angle to a value that can be sent
/// to the Dynamixel motors.
int32_t degrees_to_int(const float angle)
{
    return (int32_t)(4095*(angle+180)/360);
}

/// Moves the motors to a wanted position.
void move_to_pos(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float angles[2])
{
    for (size_t i = 0; i < motor_IDs.size(); ++i)
    {
        motor.goalPosition(motor_IDs[i], degrees_to_int(angles[i]));
    }
}

/// Calls move_to_pos and waits until the movements are complete.
bool move_to_pos_wait(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float angles[2])
{
    bool move_complete = false;
    move_to_pos(motor, motor_IDs, angles);
  
    for (int i = 0; i < 100 && !move_complete; ++i)
    {
        int32_t pos0 = 0;
        int32_t pos1 = 0;

        motor.getPresentPositionData(motor_IDs[0], &pos0);
        motor.getPresentPositionData(motor_IDs[1], &pos1);
      
        move_complete = abs(degrees_to_int(angles[0]) - pos0) < 13 && abs(degrees_to_int(angles[1]) - pos1) < 5;

        /*
        //Debug
        Serial.print(" Epaule asked vs real : ");
        Serial.print(degrees_to_int(angles[0]));
        Serial.print(" ");
        Serial.print(pos0);
        Serial.print(" Coude asked vs real : ");
        Serial.print(degrees_to_int(angles[1]));
        Serial.print(" ");
        Serial.print(pos1);*/
        
        delay(10);
    }
}

void init_motors(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs)
{
    for (size_t i = 0; i < motor_IDs.size(); ++i)
    {
        const char* motor_name = i+"";
        uint16_t model_number = 0;
        const char* error_message;
        motor.init(motor_name, 57600, &error_message);
        motor.ping(motor_IDs[i], &model_number, &error_message);
        motor.jointMode(motor_IDs[i], 150, 0, &error_message);
        motor.torqueOn(motor_IDs[i]);
    }
}

void go_to_home_arm(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float motor_angles[2])
{
    for (int i = 0; i < motor_IDs.size(); ++i)
    {
        motor_angles[i] = 0;
    }
    delay(1000);
    move_to_pos_wait(motor, motor_IDs, motor_angles);
}

void start_motors(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs)
{
    for (size_t i = 0; i < motor_IDs.size(); ++i)
    {
        motor.torqueOn(motor_IDs[i]);
    }
}

void stop_motors(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs)
{
    for (size_t i = 0; i < motor_IDs.size(); ++i)
    {
        motor.torqueOff(motor_IDs[i]);
    }
}

void open_gripper(Servo& servoGripper)
{
  while(servoGripper.read()!=140)
  {
    servoGripper.write(140);
  }
}

void close_gripper(Servo& servoGripper)
{
  while(servoGripper.read()!=0)
  {
    servoGripper.write(0);
  }
    
}

void index_color(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, int colorIndex)
{
  if(colorIndex >= nbAvailableColors)
  {
      Serial.println("Erreur: Index hors de la plage permise");
  }
  else{
  float angleDivision = 360.0 / static_cast<float>(nbAvailableColors); 
  float carAngle = (static_cast<float>(colorIndex)*(angleDivision))-180;


  move_to_pos_wait(motor, motor_IDs, &carAngle);
  }

}

void pick(Servo& servoGripper, DynamixelWorkbench& motor, const std::vector<uint8_t> motor_IDs, float angles[2])
{
  stepperGoToPos(crayonApproach, 0);
  move_to_pos_wait(motor, motor_IDs, angles);
  open_gripper(servoGripper);
  stepperGoToPos(crayonPick, 0);
  close_gripper(servoGripper);
  delay(500);
  stepperGoToPos(crayonRetreat, 0);

}

void place(Servo& servoGripper, DynamixelWorkbench& motor, const std::vector<uint8_t> motor_IDs, float angles[2])
{
  stepperGoToPos(crayonRetreat, 0);
  move_to_pos_wait(motor, motor_IDs, angles);
  open_gripper(servoGripper);
}

void pixel_to_pos(int pixel, float pixelPos[2], int nbColumn)
{
  int goalRow = pixel / nbColumn;
  int goalColumn = pixel - (goalRow*nbColumn);
  pixelPos[0] = -75 + (goalColumn * 3);
  pixelPos[1] = 250 - (goalRow * 3);
}

void drawPoint(DynamixelWorkbench& motor, const std::vector<uint8_t> motor_IDs, float angles[2], int pixel, int nbColumn)
{
  float pixelPos[2];
  pixel_to_pos(pixel, pixelPos, nbColumn);
  inverse_kinematics( pixelPos[0] , pixelPos[1], angles);
  move_to_pos_wait(motor, motor_IDs, angles);
  stepperGoToPos(pixelDraw, pixelPos[1]);
  delay(50);
  stepperGoToPos(pixelApproach, pixelPos[1]);
}

void pixelisation(int pixelArray[], int nbColumn, DynamixelWorkbench& armMotors, const std::vector<uint8_t> arm_motor_IDs, float arm_angles[2], 
Servo& servoGripper, DynamixelWorkbench& carMotors, const std::vector<uint8_t>& car_motor_IDs, int carColorIndex)
{
  index_color(carMotors, car_motor_IDs, carColorIndex);
  pick(servoGripper, armMotors, arm_motor_IDs, arm_angles);

  for(int i = 0; i < sizeof(pixelArray); i++)
  {
    drawPoint(armMotors, arm_motor_IDs, arm_angles, pixelArray[i], nbColumn);
  }

  place(servoGripper, armMotors, arm_motor_IDs, arm_angles);
}


