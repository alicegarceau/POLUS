#include "serialcomm_functions.hpp"
#include <Arduino.h>
#include <iostream>
#include <string>
#include <vector>
  
  Serial.begin(BAUDRATE);
  begin_time = time.time();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
    if (begin_time - time.time() > 2000) {
      Serial.println("Aucun port détecté");
      begin_time = time.time();
    }
  }