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

// Convertir un angle a une valeur pour moteur Dynamixel
int32_t degrees_to_int(const float angle)
{
    return (int32_t)(4095*(angle+180)/360);
}

// Bouger le moteur à une position donnée
void move_to_pos(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float angles[2])
{
    for (size_t i = 0; i < motor_IDs.size(); ++i)
    {
        motor.goalPosition(motor_IDs[i], degrees_to_int(angles[i]));
    }
}

// Appeler move_to_pos et atteint que le mouvement soit fini
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

// Initialiser les moteurs
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

// Bouger les moteurs à la position de départ
void go_to_home_arm(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs, float motor_angles[2])
{
    for (int i = 0; i < motor_IDs.size(); ++i)
    {
        motor_angles[i] = 0;
    }
    delay(1000);
    move_to_pos_wait(motor, motor_IDs, motor_angles);
}

// Départ des moteurs
void start_motors(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs)
{
    for (size_t i = 0; i < motor_IDs.size(); ++i)
    {
        motor.torqueOn(motor_IDs[i]);
    }
}

// Arrêt des moteurs
void stop_motors(DynamixelWorkbench& motor, const std::vector<uint8_t>& motor_IDs)
{
    for (size_t i = 0; i < motor_IDs.size(); ++i)
    {
        motor.torqueOff(motor_IDs[i]);
    }
}

// Ouvrir la pince
void open_gripper(Servo& servoGripper)
{
  while(servoGripper.read()!=140)
  {
    servoGripper.write(140);
  }
}

// Fermer la pince
void close_gripper(Servo& servoGripper)
{
  while(servoGripper.read()!=0)
  {
    servoGripper.write(0);
  }
    
}


// Indexer le carrousel à une couleur donnée
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

// Prendre un crayon donné dans le carrousel
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

// Déposer un crayon dans le carrousel
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

// Convertir une position de pixel en coordonnées XY
void pixel_to_pos(int pixel, float pixelPos[2], int nbColumn)
{
  int goalRow = pixel / nbColumn;
  int goalColumn = pixel - (goalRow*nbColumn);
  pixelPos[0] = -75 + (goalColumn * 3);
  pixelPos[1] = 250 - (goalRow * 3);
}

// Déplacer et dessiner un point 
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

// Prendre un crayon, dessiner tous les points d'une couleur et déposer le crayon
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

// Lire les messages d'entrées pour déterminer les prochaines actions du bras
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

// Retourner les angles des moteurs
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
