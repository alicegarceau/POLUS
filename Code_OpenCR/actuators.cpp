/*
Projet: POLUS
Description: Fonctions qui gerent les actuateurs à haut niveau
Auteurs: Frédérik Desaulniers – DESF3105
         Pierre-Olivier Dupont – DUPP2408
         Alice Garceau – GARA2507
         Enrick Hébert – HEBE2701
         Émile Michaud – MICE1602
Fonctions move_to_pos() et move_to_pos_wait() inspirées du travail original de :
Projet:     SCARUS
Auteurs: Alec Gagnon,      gaga2120
         Étienne Lefebvre, lefe1001
         Robin Mailhot,    mair1803
         Charles Caya,     cayc2401
*/

#include "actuators.hpp"
#include "stepperZ.hpp"
#include "inverseKinematics.hpp"

const int crayonPick = 24;
const int crayonRetreat = 80;
const int crayonApproach = 80;  //60
const int nbAvailableColors = 20;

const int pixelApproach = 24;
const int pixelDraw = 19;

const float epauleRatio = 1.667;
const float degPulse = 0.088;

const float XCarIn = -159.01; 
const float YCarIn = 96.75; 
const float XCarOut = -144.93;
const float YCarOut = 107.01;


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
      
        move_complete = abs(degrees_to_int(angles[0]) - pos0) < 3 && abs(degrees_to_int(angles[1]) - pos1) < 3;

        
        //Debug
        /*Serial.print(" Epaule asked vs real : ");
        Serial.print(degrees_to_int(angles[0]));
        Serial.print(" ");
        Serial.print(pos0);
        Serial.print(" Coude asked vs real : ");
        Serial.print(degrees_to_int(angles[1]));
        Serial.print(" ");
        Serial.println(pos1);*/
        
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


void index_color(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, Servo& servoCarrousel, int colorIndex)
{
    if(colorIndex >= nbAvailableColors)
    {
        Serial.println("Erreur: Index hors de la plage permise");
    }
    else{
      while(servoCarrousel.read()!=70)
      {
        servoCarrousel.write(70);
      }
    delay(500);
    float angleDivision = 360.0 / static_cast<float>(nbAvailableColors); 
    float carAngle = (static_cast<float>(colorIndex)*(angleDivision))-180;
    move_to_pos_wait(motor, motor_IDs, &carAngle);
    while(servoCarrousel.read()!=150)
      {
        servoCarrousel.write(150);
      }
      delay(500);
    }

}

void pick(Servo& servoGripper, DynamixelWorkbench& motor, const std::vector<uint8_t> motor_IDs, float angles[2])
{
  stepperGoToPos(crayonApproach);
  inverse_kinematics( XCarIn , YCarIn, angles);
  move_to_pos_wait(motor, motor_IDs, angles);
  open_gripper(servoGripper);
  stepperGoToPos(crayonPick);
  close_gripper(servoGripper);
  delay(2000);
  stepperGoToPos(crayonRetreat);

  for (float i = 0; i<=1; i += 0.1)
  {
    float moveX = abs((XCarIn - XCarOut)*i);
    float moveY = abs((YCarIn - YCarOut)*i);
    inverse_kinematics( XCarIn + moveX, YCarIn + moveY, angles);
    move_to_pos_wait(motor, motor_IDs, angles);
  }

}

void place(Servo& servoGripper, DynamixelWorkbench& motor, const std::vector<uint8_t> motor_IDs, float angles[2])
{
  stepperGoToPos(crayonRetreat);

  for (float i = 0; i<=1; i += 0.1)
  {
    float moveX = abs((XCarIn - XCarOut)*i);
    float moveY = abs((YCarIn - YCarOut)*i);
    inverse_kinematics( XCarOut - moveX, YCarOut -  moveY, angles);
    move_to_pos_wait(motor, motor_IDs, angles);
  }

  open_gripper(servoGripper);
  delay(1000);
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
  stepperGoToPos(pixelDraw);
  delay(50);
  stepperGoToPos(pixelApproach);
}

void drawLine(DynamixelWorkbench& motor, const std::vector<uint8_t> motor_IDs, float angles[2], int startingPix, int endingPix, int nbColumn)
{
  float pixelStartPos[2];
  float pixelEndPos[2];
  pixel_to_pos(startingPix, pixelStartPos, nbColumn);
  pixel_to_pos(endingPix, pixelEndPos, nbColumn);
  inverse_kinematics( pixelStartPos[0] , pixelStartPos[1], angles);
  move_to_pos_wait(motor, motor_IDs, angles);
  stepperGoToPos(pixelDraw);

  for(float moveX = pixelStartPos[0]; pixelStartPos[0]+moveX < pixelEndPos[0]; moveX = moveX + 0.5)
  {
    inverse_kinematics( pixelStartPos[0] + moveX, pixelStartPos[1], angles);
    move_to_pos_wait(motor, motor_IDs, angles);
  }
}

void pixelisation(int* pixelArray, int sizeArray, int nbColumn, DynamixelWorkbench& armMotors, const std::vector<uint8_t> arm_motor_IDs, float arm_angles[2], 
Servo& servoGripper, DynamixelWorkbench& carMotors, const std::vector<uint8_t>& car_motor_IDs, Servo& servoCarrousel, int carColorIndex)
{
  index_color(carMotors, car_motor_IDs, servoCarrousel, carColorIndex);
  
  pick(servoGripper, armMotors, arm_motor_IDs, arm_angles);

  for(int i = 0; i < sizeArray; i++)
  {
    drawPoint(armMotors, arm_motor_IDs, arm_angles, pixelArray[i], nbColumn);
    if (shouldStop()) break;
  }

  place(servoGripper, armMotors, arm_motor_IDs, arm_angles);
}

void pixelignation(int* pixelArray, int sizeArray, int nbColumn, DynamixelWorkbench& armMotors, const std::vector<uint8_t> arm_motor_IDs, float arm_angles[2], 
Servo& servoGripper, DynamixelWorkbench& carMotors, const std::vector<uint8_t>& car_motor_IDs, Servo& servoCarrousel, int carColorIndex)
{
  bool done = false;
  int i = 0;
  int startingPix = 0;
  int endingPix = 0;
  int endLine = 0;

  index_color(carMotors, car_motor_IDs, servoCarrousel, carColorIndex);
  
  pick(servoGripper, armMotors, arm_motor_IDs, arm_angles);

  while(done != true)
  {

    if(pixelArray[i+1]-pixelArray[i] > 1)
    {
      drawPoint(armMotors, arm_motor_IDs, arm_angles, pixelArray[i], nbColumn);
      i++;
    }
    else
    {
      startingPix = pixelArray[i];
      endLine = (startingPix/nbColumn)*nbColumn + nbColumn-1;
    
      while(pixelArray[i+1]-pixelArray[i] == 1 || pixelArray[i] < endLine)
      {
        i++;
      }
      endingPix = pixelArray[i];

      drawLine(armMotors, arm_motor_IDs, arm_angles, startingPix, endingPix, nbColumn);
    }
    if (shouldStop()) break;
  }
  
  place(servoGripper, armMotors, arm_motor_IDs, arm_angles);
}

bool shouldStop()
{
  int action = change_action();
  if (action == 2)
  {
    while(action != 4 || action != 1);
    {
      action = change_action();
    }
  }
  if (action == 1)  return true;
  return false;
}

void getArmMotorAngles(DynamixelWorkbench& motor, const std::vector<uint8_t> motor_IDs, float angles[2])
{
  int32_t pos0 = 0;
  int32_t pos1 = 0;    
  delay(1000);
  motor.getPresentPositionData(motor_IDs[0], &pos0);
  motor.getPresentPositionData(motor_IDs[1], &pos1);
  float AngleEpaule = (degPulse*(pos0-2048))/epauleRatio;
  float AngleCoude = degPulse*(pos1-2048);
  Serial.print(" Epaule asked vs real : ");
  Serial.print(angles[0]/epauleRatio);
  Serial.print(" ");
  Serial.print(AngleEpaule);
  Serial.print(" Coude asked vs real : ");
  Serial.print(angles[1]);
  Serial.print(" ");
  Serial.println(AngleCoude);
}
