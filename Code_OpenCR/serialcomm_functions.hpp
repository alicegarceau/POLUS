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

struct PixelData {
    string color = "noir";
    int rows = 0;
    int cols = 0;
    std::vector<int> positions;
};

extern PixelData Data;
// ========= Functions prototype ========

void comm_init();

void next_msg();

bool get_msg();

void read_msg();

void init_matrix(int size);

std::vector<std::string> Split_msg(String inputString);

void print_data();

bool decode_pixel(std::vector<std::string> parts);

bool decode_lignes(std::vector<std::string> parts);

bool decode_jog(std::vector<std::string> parts);


#endif
