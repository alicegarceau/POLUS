/*
Projet: POLUS
Description: Méthode principale (main) qui gère la communication et les actions du robot à haut niveau
Auteurs: Frédérik Desaulniers – DESF3105
         Pierre-Olivier Dupont – DUPP2408
         Alice Garceau – GARA2507
         Enrick Hébert – HEBE2701
         Émile Michaud – MICE1602

Inspiré du travail original de :
Projet:     SCARUS
Auteurs: Alec Gagnon,      gaga2120
         Étienne Lefebvre, lefe1001
         Robin Mailhot,    mair1803
         Charles Caya,     cayc2401
*/

// ---------- Libraries ----------
#include "actuators.hpp"
#include "inverseKinematics.hpp"
#include "serialcomm_functions.hpp"
#include <pthread.h>
#include "udes.h"
#include "robo.h"

/*#include "comm_functions.hpp"
#include "inverse_kinematics.hpp"
*/


// ---------- Enumerations ----------
enum class State { Sleep, Wait, Parse, Moving };

// ---------- Constants ----------
// --- Motors ---
//epaule ID = 20, coude ID = 15, caroussel ID = 3 from: Example/Dynamixel2Arduino/Basic/ScanDynamixel
const std::vector<uint8_t> MOTOR_IDS_ARM = { (const uint8_t)20, (const uint8_t)15 }; 
const std::vector<uint8_t> MOTOR_IDS_CAR = { (const uint8_t)2 };

const uint8_t nbAvailableColors = 20;
const uint8_t nbColumn = 50;

const uint8_t SERVO_PIN = 11;
const uint8_t SERVO_CAR = 9;

// ---------- Variables ----------
// --- Motors ---
DynamixelWorkbench dynaArm;
DynamixelWorkbench dynaCar;
Servo servoGripper; 
Servo servoCarrousel; 

float ZOffset = 0;


// --- Data ---
State current_state = State::Sleep;
String msg = String();
float motor_angles_arm[2] = {0, 0};
int stepCurrentPos = 0;

int colorIndex = 0;

// ---------- Main functions ----------
void setup()
{
  comm_init();
  
  const int BAUDRATE = 115200;
  Serial.begin(BAUDRATE);
  setupStepper();

  init_motors(dynaArm, MOTOR_IDS_ARM);
  init_motors(dynaCar, MOTOR_IDS_CAR);

  pinMode(SERVO_PIN, OUTPUT);
  pinMode(SERVO_CAR, OUTPUT);


  servoGripper.attach(SERVO_PIN);
  servoCarrousel.attach(SERVO_CAR);

  inverse_kinematics(0, 150, motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  index_color(dynaCar, MOTOR_IDS_CAR, servoCarrousel,  1);
  homeZ();
}

void loop()
{
  next_msg();
  int Coord[Data.positions.size()];
  for (int i = 0; i < Data.positions.size(); i++)
  {
    Coord[i] = Data.positions[i];
  } 
  
  pixelisation(Coord, Data.positions.size(), Data.cols, dynaArm, MOTOR_IDS_ARM, motor_angles_arm, 
    servoGripper, dynaCar, MOTOR_IDS_CAR, servoCarrousel, Data.color);   

  delay(1000);
    
  /*
  ///////////////////////////////// CALIBRATION POSITIONS /////////////////////////////////
  inverse_kinematics(-159.01, 96.75, motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  index_color(dynaCar, MOTOR_IDS_CAR, servoCarrousel, 2);
  while(1){
    getArmMotorAngles(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    delay(1000);  
  }
/////////////////////////////////////////////////////////////////////////////////////////
*/
}
