/*
  Projet:       Polus
  Description:  Header: Function Serial Com.
  Auteurs:      Pierre-Olivier Dupont
                Enrick Hébert
                Frédérik Desaulniers
                Alice Garceau
                Émile Michaud
*/

#ifndef serialcomm_functions_h 
#define serialcomm_functions_h

#include <Arduino.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <thread>

using namespace std;

// ========= Constant =========

const int BAUDRATE = 9600;

// ========= Variables =========

class String;

struct DrawData {
    int color = 1;
    int rows = 0;
    int cols = 0;
    std::vector<int> positions;
    int style = 1;
};

struct JogData {
    int pos_x = 0;
    int pos_y = 0;
};

extern DrawData Data;
extern JogData Jog;
// ========= Functions prototype ========

void comm_init();

void next_msg();

bool get_msg();

void read_msg();

void init_matrix(int size);

std::vector<std::string> Split_msg(String inputString);

bool decode_pixel(std::vector<std::string> parts);

bool decode_lignes(std::vector<std::string> parts);

bool decode_jog(std::vector<std::string> parts);

int change_action();

void print_data();


#endif
