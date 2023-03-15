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

const int BAUDRATE = 9600;

// ========= Variables =========

class String;

struct MatrixData {
    string color = "noir";
    int rows = 0;
    int cols = 0;
    int* matrix;
};

extern MatrixData Data;
// ========= Functions prototype ========

void comm_init();

void next_msg();

bool get_msg();

void read_msg();

void init_matrix(MatrixData& data);

std::vector<std::string> Split_msg(String inputString);

void print_data();


#endif
