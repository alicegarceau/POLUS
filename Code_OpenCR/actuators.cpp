#include "actuators.hpp"
#include "stepperZ.hpp"
const int crayonPick = 3;
const int crayonRetreat = 74;
const int crayonApproach = 60;



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
  
    for (int i = 0; i < 100 && !move_complete; ++i)
    {
        move_to_pos(motor, motor_IDs, angles);
         
        int32_t pos0 = 0;
        int32_t pos1 = 0;

        motor.getPresentPositionData(motor_IDs[0], &pos0);
        motor.getPresentPositionData(motor_IDs[1], &pos1);

        move_complete = abs(degrees_to_int(angles[0]) - pos0) < 10 && abs(degrees_to_int(angles[1]) - pos1) < 10;
        
        delay(10);
    }
}

int move_Z(AccelStepper& stepperZ, int stepCurrentPos, int stepNextPos)
{
 /* int nbStep =  stepNextPos - stepCurrentPos;
  stepperZ.step(nbStep);

  return stepNextPos;*/
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
/*
void home_Z(AccelStepper& stepperZ, int stepCurrentPos, int SWITCH_PIN)
{
 int step = 0;
 while(digitalRead(SWITCH_PIN)==0) //doit faire un interrupt?
 {
   step--;
   stepperZ.step(step);
 }
}
*/
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
{while(servoGripper.read()!=140)
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

void index_color(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, int nbAvailableColors, int colorIndex)
{
  if(colorIndex >= nbAvailableColors)
  {
      Serial.println("Erreur: Index hors de la plage permise");
  }
  else{
  float angleDivision = 360.0 / static_cast<float>(nbAvailableColors); 
  float carAngle = static_cast<float>(colorIndex)*(angleDivision);

  if(carAngle > 180)
  {
    carAngle = carAngle - 360;
  }

  move_to_pos_wait(motor, motor_IDs, &carAngle);
  }

 

}

void pick(Servo& servoGripper)
{
  
  stepperGoToPos(crayonApproach);
  open_gripper(servoGripper);
  stepperGoToPos(crayonPick);
  close_gripper(servoGripper);
  delay(500);
  stepperGoToPos(crayonRetreat);

}

void place(Servo& servoGripper)
{
  stepperGoToPos(crayonRetreat);
  open_gripper(servoGripper);
}



