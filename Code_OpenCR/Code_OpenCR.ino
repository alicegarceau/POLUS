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
#include "UDES2.h"
#include "robo.h"
#include "dessin1.h"
#include "dessin2.h"
#include "dessin3.h"


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

const float lineDraw = 21.7;
const float lineApproach = 24;

// ---------- Variables ----------
// --- Motors ---
DynamixelWorkbench dynaArm;
DynamixelWorkbench dynaCar;
Servo servoGripper; 
Servo servoCarrousel; 

float ZOffset = 0;
int dessin = 0;


// --- Data ---
State current_state = State::Sleep;
String msg = String();
float motor_angles_arm[2] = {0, 0};
int stepCurrentPos = 0;

int colorIndex = 0;

// ---------- Main functions ----------
void setup()
{
  //comm_init();
  
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

  if (digitalRead(BDPIN_PUSH_SW_1) == FALSE && digitalRead(BDPIN_PUSH_SW_2) == FALSE) 
  {
    dessin = 1;
  } else if (digitalRead(BDPIN_PUSH_SW_1) == TRUE && digitalRead(BDPIN_PUSH_SW_2) == FALSE)
  {
    dessin = 2;
  } else if (digitalRead(BDPIN_PUSH_SW_1) == FALSE && digitalRead(BDPIN_PUSH_SW_2) == TRUE)
  {
    dessin = 3;
  } else if (digitalRead(BDPIN_PUSH_SW_1) == TRUE && digitalRead(BDPIN_PUSH_SW_2) == TRUE)
  {
    dessin = 4;
  }
  homeZ();
  Serial.println("------------------- NEW PROGRAM ----------------");

}

void loop()
{


  
  int column = 50;
  int nbpts = 0;
  if (dessin == 1)
  {
    int dessin1Size =  sizeof(dessin1)/4;
    for (int i = 0; i < dessin1Size ; i++)
    {
      int color = dessin1[i + 1];
      int j = 2;
      while(TRUE)
      {
        if (dessin1[i+j] == 10000 || dessin1[i+j] == 12000)
        {
          nbpts = j-2;
          break;
        } 
        j++;
      }
      int Coord[nbpts];
      for (int t=0; t < nbpts+1; t++)
      {
        Coord[t] = dessin1[i+t+2];
      } 
      pixelisation(Coord, nbpts, column, dynaArm, MOTOR_IDS_ARM, motor_angles_arm, 
      servoGripper, dynaCar, MOTOR_IDS_CAR, servoCarrousel, color); 
      i = i+nbpts+1;
      if (dessin1[i+1] == 12000)
      {
        break;
      }
      delay(1000);
    }
  }

  if (dessin == 2)
  {
    int dessin2Size =  sizeof(dessin2)/4;
    for (int i = 0; i < dessin2Size ; i++)
    {
      int color = dessin2[i + 1];
      int j = 2;
      while(TRUE)
      {
        if (dessin2[i+j] == 10000 || dessin2[i+j] == 12000)
        {
          nbpts = j-2;
          break;
        } 
        j++;
      }
      int Coord[nbpts];
      for (int t=0; t < nbpts+1; t++)
      {
        Coord[t] = dessin2[i+t+2];
      } 
      pixelisation(Coord, nbpts, column, dynaArm, MOTOR_IDS_ARM, motor_angles_arm, 
      servoGripper, dynaCar, MOTOR_IDS_CAR, servoCarrousel, color); 
      i = i+nbpts+1;
      if (dessin2[i+1] == 12000)
      {
        break;
      }
      delay(1000);
    }
  }

  if (dessin == 3)
  {
    int dessin3Size =  sizeof(dessin3)/4;
    for (int i = 0; i < dessin3Size ; i++)
    {
      int color = dessin3[i + 1];
      int j = 2;
      while(TRUE)
      {
        if (dessin3[i+j] == 10000 || dessin3[i+j] == 12000)
        {
          nbpts = j-2;
          break;
        } 
        j++;
      }
      int Coord[nbpts];
      for (int t=0; t < nbpts+1; t++)
      {
        Coord[t] = dessin3[i+t+2];
      } 
      pixelisation(Coord, nbpts, column, dynaArm, MOTOR_IDS_ARM, motor_angles_arm, 
      servoGripper, dynaCar, MOTOR_IDS_CAR, servoCarrousel, color); 
      i = i+nbpts+1;
      if (dessin3[i+1] == 12000)
      {
        break;
      }
      delay(1000);
    }
  }
    
  if (dessin == 4)
  {
    index_color(dynaCar, MOTOR_IDS_CAR, servoCarrousel,  15);
    pick(servoGripper, dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

    inverse_kinematics( UDES2[0][0] , UDES2[0][1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    stepperGoToPos(lineDraw);

    for (int i = 0 ; i < (sizeof(UDES2)/sizeof(UDES2[1]))-1 ; i++)
      {
        
        
        inverse_kinematics( UDES2[i][0] , UDES2[i][1], motor_angles_arm);
        move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

        if ((abs(UDES2[i][0]-UDES2[i+1][0]) > 2) || (abs(UDES2[i][1]-UDES2[i+1][1]) > 2))
        { 
          Serial.println("MOVE");
          stepperGoToPos(lineApproach);
          delay(200);
          inverse_kinematics( UDES2[i+1][0] , UDES2[i+1][1], motor_angles_arm);
          move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
          stepperGoToPos(lineDraw);
          delay(200);
        }
      
      }

      place(servoGripper, dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
      index_color(dynaCar, MOTOR_IDS_CAR, servoCarrousel,  19);
      pick(servoGripper, dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
      inverse_kinematics( robo[0][0] , robo[0][1], motor_angles_arm);
      move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm); 
      stepperGoToPos(lineDraw);

    for (int i = 0 ; i < (sizeof(robo)/sizeof(robo[1]))-1 ; i++)
      {
        
        
        inverse_kinematics( robo[i][0] , robo[i][1], motor_angles_arm);
        move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

        if ((abs(robo[i][0]-robo[i+1][0]) > 2) || (abs(robo[i][1]-robo[i+1][1]) > 2))
        { 
          Serial.println("MOVE");
          stepperGoToPos(lineApproach);
          delay(200);
          inverse_kinematics( robo[i+1][0] , robo[i+1][1], motor_angles_arm);
          move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
          stepperGoToPos(lineDraw);
          delay(200);
        }
      
      }
    place(servoGripper, dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  }
delay(10000000);

}

  ///////////////////////////////// CALIBRATION POSITIONS /////////////////////////////////
    /*
  inverse_kinematics(-157.31, 92.50, motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  index_color(dynaCar, MOTOR_IDS_CAR, servoCarrousel, 2);
  while(1){
    getArmMotorAngles(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    delay(1000);  
  }
  */
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////// Dessin with troubleshooting prints /////////////////////
/*
  if (dessin == 1)
  {
    int dessin1Size =  sizeof(dessin1)/4;
    Serial.println(dessin1Size);
    for (int i = 0; i < dessin1Size ; i++)
    {
      
      int color = dessin1[i + 1];
      int j = 2;
      Serial.print("Color : ");
      Serial.println(color);
      while(TRUE)
      {
        if (dessin1[i+j] == 10000 || dessin1[i+j] == 12000)
        {
          nbpts = j-2;
          break;
        } 
        j++;
      }
      Serial.println(nbpts);
      int Coord[nbpts];

      for (int t=0; t < nbpts+1; t++)
      {
        Coord[t] = dessin1[i+t+2];
      } 
      for (int r = 0; r < nbpts; r++)
      {
        Serial.print(r);
        Serial.print(" : ");
        Serial.println(Coord[r]);
      }
      Serial.print("--crayon done-- i = ");
      i = i+nbpts+1;
      Serial.println(i);
      Serial.print("j = ");
      Serial.println(j);
      Serial.print("final element : ");
      Serial.println(dessin1[i+1]);
      if (dessin1[i+1] == 12000)
      {
        break;
      }
      //pixelisation(Coord, nbpts, column, dynaArm, MOTOR_IDS_ARM, motor_angles_arm, 
      //servoGripper, dynaCar, MOTOR_IDS_CAR, servoCarrousel, color); 
      delay(1000);
    }
  }
*/
  ////////////////////////////////////////////////////////////////////////////////

