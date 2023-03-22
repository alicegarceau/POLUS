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
#include "serialcomm_functions.hpp"
#include <pthread.h>
/*#include "comm_functions.hpp"
#include "inverse_kinematics.hpp"
*/


// ---------- Enumerations ----------
enum class State { Sleep, Wait, Parse, Moving };

// ---------- Constants ----------
// --- Motors ---
//const std::vector<uint8_t> MOTOR_IDS = { (const uint8_t)1, (const uint8_t)2 };
// const std::vector<uint8_t> MOTOR_IDS_ARM = { (const uint8_t)15, (const uint8_t)3 }; //epaule ID = 15, coude ID = 3, caroussel ID = 2
// const std::vector<uint8_t> MOTOR_IDS_CAR = { (const uint8_t)2 };// { (const uint8_t)15, (const uint8_t)3 }; //epaule ID = 15, coude ID = 3, caroussel ID = 2

// const uint8_t nbAvailableColors = 20;

const uint8_t SERVO_PIN = 5;
const uint8_t SWITCH_PIN = 6;



// ---------- Variables ----------
// --- Motors ---
DynamixelWorkbench dynaArm;
DynamixelWorkbench dynaCar;
Servo servoGripper; 
Stepper stepperZ(200, 10, 11, 12, 13);

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

    init_motors(dynaArm, MOTOR_IDS_ARM);
    init_motors(dynaCar, MOTOR_IDS_CAR);
    servoGripper.attach(SERVO_PIN);
    stepperZ.setSpeed(60);

    pinMode(SERVO_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT_PULLUP);

    // Nécessite un interrup pour faire le zero? 
    //attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), ISRzero, FALLING);

    colorIndex = 10;
}

void loop()
{  
  next_msg();
  print_data();
  delay(1000);


  // inverse_kinematics( 0 , 270, motor_angles_arm);
  // move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

  /* if (stepper.distanceToGo() == 0)
  {
    delay(500);
    pos = -pos;
    stepper.moveTo(pos);
  }
  stepper.run();*/

  /*for(float i = 0; i < 30; i++)
  {
    inverse_kinematics( i , 200, motor_angles_arm);
    move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  }

   for(float j = 200; j < 230; j++)
  {
    inverse_kinematics( 30 , j, motor_angles_arm);
    move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
  }

   inverse_kinematics( 0 , 200, motor_angles_arm);
  move_to_pos_wait(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);*/

  /*
  index_color(dynaCar, MOTOR_IDS_CAR, nbAvailableColors, colorIndex);

  inverse_kinematics(56, 80, motor_angles);

  Serial.println(motor_angles[0]);
  Serial.println(motor_angles[1]);
  Serial.println(" ");

  move_to_pos(dyna, MOTOR_IDS, motor_angles);*/
  
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
    delay(1000);
}