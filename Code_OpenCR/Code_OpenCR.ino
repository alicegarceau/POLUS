/*
Project:     SCARUS
Description: Main code that moves the motors. To be run from the OpenCR.
Authors: Alec Gagnon,      gaga2120
         Étienne Lefebvre, lefe1001
         Robin Mailhot,    mair1803
         Charles Caya,     cayc2401
*/

// ---------- Libraries ----------
#include "actuators.hpp"
#include "data.h"
//#include "coordinates.h"
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
AccelStepper stepper(AccelStepper::DRIVER, 1, 2);

float ZOffset = 0;


// --- Data ---
State current_state = State::Sleep;
String msg = String();
float motor_angles_arm[2] = {0, 0};
int stepCurrentPos = 0;

int colorIndex = 10;
int pos = 3600;


// ---------- Main functions ----------
void setup()
{
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
  //Position prise crayon

 
  //stepperGoToPos(80);
  //delay(5000); 
  /*inverse_kinematics(-157.74, 92.81, motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

  index_color(dynaCar, MOTOR_IDS_CAR, servoCarrousel, 2);
  while(1){
    getArmMotorAngles(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    delay(1000);
  }*/


  
  int pixelArray[] = {2025, 410};
  int sizeArray = sizeof(pixelArray) / sizeof(pixelArray[0]);
  //index_color(dynaCar, MOTOR_IDS_CAR, servoCarrousel, 2);
  delay(1000);


    pixelisation(pixelArray, sizeArray, nbColumn, dynaArm, MOTOR_IDS_ARM, motor_angles_arm, 
    servoGripper, dynaCar, MOTOR_IDS_CAR, servoCarrousel, 5);

    pixelisation(pixelArray, sizeArray, nbColumn, dynaArm, MOTOR_IDS_ARM, motor_angles_arm, 
    servoGripper, dynaCar, MOTOR_IDS_CAR, servoCarrousel, 2);

    pixelisation(pixelArray, sizeArray, nbColumn, dynaArm, MOTOR_IDS_ARM, motor_angles_arm, 
    servoGripper, dynaCar, MOTOR_IDS_CAR, servoCarrousel, 15);
    
    pixelisation(pixelArray, sizeArray, nbColumn, dynaArm, MOTOR_IDS_ARM, motor_angles_arm, 
    servoGripper, dynaCar, MOTOR_IDS_CAR, servoCarrousel, 4);
 
  



  ////////////////////////Emile Test////////////////////////////////////////////////////////
  
  //inverse_kinematics( data[0][0] , data[0][1], motor_angles_arm);
  //move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

  /*inverse_kinematics( 0 , 100, motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

  stepperGoToPos(22);


  for (float i = 100 ; i < 250 ; i++)
    {
      
      //stepperGoToPos(20);
      inverse_kinematics( 0 , i, motor_angles_arm);
      move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    }*/

/*
  for (int i = 0 ; i < (sizeof(data)/sizeof(data[1]))-1 ; i++)
  {
    
    stepperGoToPos(17);
    inverse_kinematics( data[i][0] , data[i][1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

    if ((abs(data[i][0]-data[i+1][0]) > 2) || (abs(data[i][1]-data[i+1][1]) > 2))
    { 
      Serial.println("MOVE");
      stepperGoToPos(20);
      delay(200);
      inverse_kinematics( data[i+1][0] , data[i+1][1], motor_angles_arm);
      move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
      stepperGoToPos(17);
      delay(200);

    }
    //stepperGoToPos(16);
    //delay(100); 
  }
*/


  //////////////////////////////////////////////////////////////////////////////////////////////////////

  /*pick(servoGripper, dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  
  delay(3000);

  place(servoGripper, dynaArm, MOTOR_IDS_ARM, motor_angles_arm);*/

  /*index_color(dynaCar, MOTOR_IDS_CAR, 2);

  pick(servoGripper, dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

  float pixelPos[2];

  for (int pix = 0 ; pix != 49 ; pix++)
  {
    
    pixel_to_pos(pix, pixelPos, nbColumn );
    inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    stepperGoToPos(16);
    delay(50);
    stepperGoToPos(22);
  }
  for (int pix = 45 ; pix != 2495 ; pix=pix+50)
  {
    pixel_to_pos(pix, pixelPos, nbColumn );
    inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    stepperGoToPos(16);
    delay(50);
    stepperGoToPos(22); 
  }
  for (int pix = 2499 ; pix != 2450 ; pix--)
  {
    pixel_to_pos(pix, pixelPos, nbColumn );
    inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    stepperGoToPos(16);
    delay(50);
    stepperGoToPos(22); 
  }
  for (int pix = 2450 ; pix != 0 ; pix=pix-50)
  {
    pixel_to_pos(pix, pixelPos, nbColumn );
    inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    stepperGoToPos(16);
    delay(50);
    stepperGoToPos(22); 
  }

  place(servoGripper, dynaArm, MOTOR_IDS_ARM, motor_angles_arm);*/

  // prior code 

    /*switch (current_state)
    {
        case State::Sleep:
        {
            
            // Waiting for the signal to start the program
            send_data("Waiting for the START command.");
            delay(100);
            msg = get_data();
            if(should_start(msg))
            {
                send_data("Starting the program.");
                start_motors(dyna, MOTOR_IDS);
                go_to_home(dyna, MOTOR_IDS, motor_angles, LINEAR_PIN);
                current_state = State::Wait;
            }
            break;
        }

        case State::Wait:
        {
            // Waiting for data on the serial port
            msg = get_data();
            if (msg.length() != 0)
            {
                current_state = State::Parse;
            }
            break;
        }

        case State::Parse:
        {
            // Try to parse the received message
            Nut nut = parse_nut(msg);

            if (nut.is_valid)
            {
                current_state = State::Moving;
                current_nut = nut;
            }
            else if (should_stop(msg))
            {
                send_data("Stopping the program.");
                stop_motors(dyna, MOTOR_IDS);
                current_state = State::Sleep;
            }
            else
            {
                // Message is invalid
                current_state = State::Wait;
            }
            break;
        }

        case State::Moving:
        {
            go_to_pick(current_nut, dyna, MOTOR_IDS, motor_angles, LINEAR_PIN, SOLENOID_PIN);
            go_to_drop(current_nut, dyna, MOTOR_IDS, motor_angles, LINEAR_PIN, SOLENOID_PIN);
            send_data("Done");
            
            current_state = State::Wait;
            break;
        }
    }*/
    delay(10);
}