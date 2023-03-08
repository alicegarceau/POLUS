#include "stepperZ.hpp"

//Declare variables for functions
const int MAX_MM = 100; // Soft limit, max height allowed relative to home pos (lim switch)
const int MIN_MM =   5; // Soft limit, min height allowed relative to home pos (lim switch)
static int currPosmm; // Current position in mm

int oneTime = 1;



//Main loop
//void loop() {
//  while( oneTime ) {
//    homeZ();
//    stepperGoToPos( 20 );
//    delay(5000);
//    stepperGoToPos( 50 );
//    oneTime = 0;
//  }
//}

void setupStepper()
{
  pinMode(PIN_STP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_MS1, OUTPUT);
  pinMode(PIN_MS2, OUTPUT);
  pinMode(PIN_EN, OUTPUT);
  pinMode(PIN_SW, INPUT_PULLUP);
  digitalWrite(PIN_STP, LOW);
  digitalWrite(PIN_DIR, LOW);
  digitalWrite(PIN_MS1, LOW);
  digitalWrite(PIN_MS2, LOW);
  digitalWrite(PIN_EN, HIGH);
}

//Reset Easy Driver pins to default states
void resetEDPins()
{
  digitalWrite(PIN_STP, LOW);
  digitalWrite(PIN_DIR, LOW);
  digitalWrite(PIN_MS1, LOW);
  digitalWrite(PIN_MS2, LOW);
  digitalWrite(PIN_EN, HIGH);
}

void homeZ()
{
  digitalWrite(PIN_MS1, HIGH);
  digitalWrite(PIN_MS2, HIGH);
  digitalWrite(PIN_EN, LOW);
  digitalWrite(PIN_DIR, LOW);
  while( digitalRead(PIN_SW) != false )
  {
    digitalWrite(PIN_STP,HIGH); //Trigger one step forward
    delayMicroseconds(500);
    digitalWrite(PIN_STP,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(500);
  }
  currPosmm = 0;
  Serial.println(currPosmm);
}

// 1/8th microstep foward mode function
void stepperGoToPos(int goalmm ) // goalmm, 
{
  // Todo : add software limits
  float displacementmm = goalmm - currPosmm; 
  currPosmm += displacementmm;
  int nMicroSteps = abs((displacementmm / MM_PER_TURN) * STEPS_PER_TURN * MICRO_STEPS); // Take absolue value
  int direction;
  if (displacementmm < 0) {
    direction = LOW;
  } else {
    direction = HIGH;
  }
  digitalWrite(PIN_DIR, direction); // Pull direction pin low to move "forward". Make LOW/HIGH depend on sign of distmm
  digitalWrite(PIN_MS1, HIGH); //Pull PIN_MS1, and PIN_MS2 high to set logic to 1/8th microstep resolution
  digitalWrite(PIN_MS2, HIGH);
  digitalWrite(PIN_EN, LOW); // Pull Enable pin low (logic high) to allow
  Serial.println(nMicroSteps);

  for(int x= 1; x<nMicroSteps; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(PIN_STP,HIGH); //Trigger one step forward
    delayMicroseconds(100);
    digitalWrite(PIN_STP,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(100);
  }

  //Serial.println(currPosmm);

}