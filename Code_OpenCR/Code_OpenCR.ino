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
    // Nécessite un interrup pour faire le zero? 
    //attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), ISRzero, FALLING);

}
int flag = 0;
void loop()
{
  int time = 100;
  int32_t pos0 = 0;
  int32_t pos1 = 0;



/*
for (float i = 0; i < 90 ; i = i + 5)
    {
        motor_angles_arm[0]=-i*1.667;
        motor_angles_arm[1]=i*1.6;
        
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        //dynaArm.goalPosition(MOTOR_IDS_ARM[1],2048)
        delay(1000); 
        
        dynaArm.getPresentPositionData(MOTOR_IDS_ARM[0], &pos0);
        dynaArm.getPresentPositionData(MOTOR_IDS_ARM[1], &pos1);
        float AngleEpaule = (0.088*abs(2048-pos0))/1.667;
        float AngleCoude = 0.088*abs(2048-pos1);
    Serial.print(" Epaule asked vs real : ");
    Serial.print(motor_angles_arm[0]/1.667);
    Serial.print(" ");
    Serial.print(AngleEpaule);
    Serial.print(" Coude asked vs real : ");
    Serial.print(motor_angles_arm[1]);
    Serial.print(" ");
    Serial.println(AngleCoude);
    }
*/

        //motor_angles_arm[0]=0;
        //motor_angles_arm[1]=0;
   /*     inverse_kinematics( -25 , 150, motor_angles_arm);
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(1000);
        dynaArm.getPresentPositionData(MOTOR_IDS_ARM[0], &pos0);
        dynaArm.getPresentPositionData(MOTOR_IDS_ARM[1], &pos1);
        float AngleEpaule = (0.088*abs(2048-pos0))/1.667;
        float AngleCoude = 0.088*abs(2048-pos1);
    Serial.print(" Epaule asked vs real : ");
    Serial.print(motor_angles_arm[0]/1.667);
    Serial.print(" ");
    Serial.print(AngleEpaule);
    Serial.print(" Coude asked vs real : ");
    Serial.print(motor_angles_arm[1]);
    Serial.print(" ");
    Serial.println(AngleCoude);*/

  
/*
  ///////////////////////// DEMO ////////////////////////

  
  if (flag<=3)
  {

        inverse_kinematics( 100 , 160, motor_angles_arm);
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        inverse_kinematics( -100 , 120, motor_angles_arm);
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(1000);
        inverse_kinematics( 100 , 200, motor_angles_arm);
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(1000);
        motor_angles_arm[0]=0;
        motor_angles_arm[1]=120;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(time);
        motor_angles_arm[0]=-10;
        motor_angles_arm[1]=90;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(time);
        motor_angles_arm[0]=-20;
        motor_angles_arm[1]=120;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(time);
        motor_angles_arm[0]=-30;
        motor_angles_arm[1]=90;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(time);
        motor_angles_arm[0]=-40;
        motor_angles_arm[1]=120;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(time);
        motor_angles_arm[0]=-50;
        motor_angles_arm[1]=90;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(time);
        motor_angles_arm[0]=-60;
        motor_angles_arm[1]=120;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(time);
        motor_angles_arm[0]=-70;
        motor_angles_arm[1]=90;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(time);
        motor_angles_arm[0]=-80;
        motor_angles_arm[1]=120;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(time);
        motor_angles_arm[0]=-85;
        motor_angles_arm[1]=130;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(1000);
        motor_angles_arm[0]=85;
        motor_angles_arm[1]=-130;
        move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);
        delay(1500);
        flag++;
  }

  ///////////////////////// FIN DEMO //////////////
*/
  
  /*Serial.print(motor_angles_arm[0]);
  Serial.print(" ");
  Serial.println(motor_angles_arm[1]);*/
/*
  delay(time);

  inverse_kinematics( 100 , 200, motor_angles_arm);
  Serial.print("100, 200 : ");
  Serial.print(motor_angles_arm[0]);
  Serial.print(" ");
  Serial.println(motor_angles_arm[1]);
  move_to_pos(dynaArm, MOTOR_IDS_ARM, motor_angles_arm);

  delay(time);
*/
        

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
  Serial.println(motor_angles_arm[0]);
  Serial.println(motor_angles_arm[1]);
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
    delay(10);
}