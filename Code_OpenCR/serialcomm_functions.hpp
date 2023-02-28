/*
  Project:      CAGIUS
  Description:  Header: Function Serial Com.
  Authors:      Florence Millette
                Aissatou
                Alexandre
                Laurie Croteau
                Natael Laroche-Latulippe
*/

#ifndef serialcomm_functions_h 
#define serialcomm_functions_h

#include <Arduino.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// ========= Constant =========

const int BAUDRATE = 115200;

// ========= Variables =========

class String;

struct MatrixData {
    string color = "noir";
    int rows = 0;
    int cols = 0;
    int** matrix;
};

extern MatrixData Data;
// ========= Functions prototype ========

void comm_init();

bool should_init(const String& state);

bool should_start(const String& state);

bool should_end(const String& state);

String should_wash(String& state);

bool should_trash(String& state);

bool get_msg();

void read_msg();

String send_msg(const String& msg);

void init_matrix(MatrixData& data);


#endif
