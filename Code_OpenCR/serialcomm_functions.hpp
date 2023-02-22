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

// ========= Constant =========

const int BAUDRATE = 115200;

// ========= Variables =========

class String;

std::string color;
int rows;
int cols;

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


#endif
