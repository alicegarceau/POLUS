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
#include "inverseKinematics.hpp"
#include "stepperZ.hpp"
/*#include "comm_functions.hpp"
#include "inverse_kinematics.hpp"
*/


// ---------- Enumerations ----------
enum class State { Sleep, Wait, Parse, Moving };

// ---------- Constants ----------
// --- Motors ---
//const std::vector<uint8_t> MOTOR_IDS = { (const uint8_t)1, (const uint8_t)2 };
const std::vector<uint8_t> MOTOR_IDS_ARM = { (const uint8_t)2, (const uint8_t)15 }; //epaule ID = 15, coude ID = 3, caroussel ID = 2
const std::vector<uint8_t> MOTOR_IDS_CAR = { (const uint8_t)3 };// { (const uint8_t)15, (const uint8_t)3 }; //epaule ID = 15, coude ID = 3, caroussel ID = 2

const uint8_t nbAvailableColors = 20;

const uint8_t SERVO_PIN = 9;
const uint8_t SWITCH_PIN = 7;
const uint8_t STEPPER_PIN_ENABLE = 5;
const uint8_t STEPPER_PIN_DIR = 10;
const uint8_t STEPPER_PIN_STEP = 11;
const float epauleRatio = 1.667;
const float degPulse = 0.088;


// ---------- Variables ----------
// --- Motors ---
DynamixelWorkbench dynaArm;
DynamixelWorkbench dynaCar;
Servo servoGripper; 
AccelStepper stepper(AccelStepper::DRIVER, 1, 2);




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
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(STEPPER_PIN_ENABLE, OUTPUT);
  pinMode(STEPPER_PIN_DIR, OUTPUT);
  pinMode(STEPPER_PIN_STEP, OUTPUT);

  servoGripper.attach(SERVO_PIN);
    
  stepper.setMaxSpeed(3000);
  stepper.setAcceleration(1000);
  homeZ();
    // Nécessite un interrup pour faire le zero? 
    //attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), ISRzero, FALLING);

}




void loop()
{

  float pixelPos[2];
  stepperGoToPos(45);
    delay(5000);

  for (int pix = 0 ; pix != 49 ; pix++)
  {
    
    pixel_to_pos(pix, pixelPos );
    inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    stepperGoToPos(16);
    delay(50);
    stepperGoToPos(22);
  }
  for (int pix = 49 ; pix != 2499 ; pix=pix+50)
  {
    pixel_to_pos(pix, pixelPos );
    inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    stepperGoToPos(16);
    delay(50);
    stepperGoToPos(22); 
  }
  for (int pix = 2499 ; pix != 2450 ; pix--)
  {
    pixel_to_pos(pix, pixelPos );
    inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    stepperGoToPos(16);
    delay(50);
    stepperGoToPos(22); 
  }
  for (int pix = 2450 ; pix != 0 ; pix=pix-50)
  {
    pixel_to_pos(pix, pixelPos );
    inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
    move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
    stepperGoToPos(16);
    delay(50);
    stepperGoToPos(22); 
  }
  /*
  pixel_to_pos(0, pixelPos );
  inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  stepperGoToPos(16);
  delay(50);
  stepperGoToPos(19);




  pixel_to_pos(49, pixelPos );
  inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  stepperGoToPos(16);
  delay(50);
  stepperGoToPos(19);

  


  pixel_to_pos(2450, pixelPos );
  inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  stepperGoToPos(16);
  delay(50);
  stepperGoToPos(19);

  


  pixel_to_pos(2499, pixelPos );
  inverse_kinematics( pixelPos[0] , pixelPos[1], motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  stepperGoToPos(16);
  delay(50);
  stepperGoToPos(19);
  
  */


  /*int32_t pos0 = 0;
  int32_t pos1 = 0;    
  delay(1000);
  dynaArm.getPresentPositionData(MOTOR_IDS_ARM[0], &pos0);
  dynaArm.getPresentPositionData(MOTOR_IDS_ARM[1], &pos1);
  float AngleEpaule = (degPulse*(pos0-2048))/epauleRatio;
  float AngleCoude = degPulse*(pos1-2048);
  Serial.print(" Epaule asked vs real : ");
  Serial.print(motor_angles_arm[0]/epauleRatio);
  Serial.print(" ");
  Serial.print(AngleEpaule);
  Serial.print(" Coude asked vs real : ");
  Serial.print(motor_angles_arm[1]);
  Serial.print(" ");
  Serial.println(AngleCoude);*/



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