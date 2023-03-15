/*
  Project:      CAGIUS
  Description:  Function Serial Com.
  Authors:      Florence Millette
                Aissatou
                Alexandre
                Laurie Croteau
                Natael Laroche-Latulippe
*/

#include "serialcomm_functions.hpp"

MatrixData Data;

// ========= Functions ========

void comm_init()
{
 /**
 * Initialisation de la communication et attente de connection
 * @param { } 
 * @return { void }
 */
  Serial.begin(BAUDRATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void next_msg()
{
  std::string done = "done/n";
  Serial.write(done.c_str(), done.size());
  delay(1000);
  bool msg_ok;
  while(!msg_ok)
  {
    msg_ok = get_msg();
    //Serial.println(msg_ok);
    delay(100);
  }
}

bool get_msg()
{
 /**
 * Fonction de lecture de message et filtre le device ID du RaspberryPi
 * @param { } 
 * @return { bool }
 */
  //définir le message d'aquittement pour une erreur inconnue;
  std::string acquittement = "err0\n";

  // Read the data from the serial port
  String inputString = Serial.readStringUntil('\n');
  
  if (inputString.startsWith("sync"))
  {
    //Serial.print("Received message: ");
    //Serial.println(inputString);  // Print the message to the serial monito
    std::vector<std::string> parts = Split_msg(inputString);

    // Extract the individual values
    if (parts.size() >= 4) {
      string color;
      int rows;
      int cols;
      
      std::stringstream(parts[1]) >> color;
      std::stringstream(parts[2]) >> rows;
      std::stringstream(parts[3]) >> cols;
      int value;
      int index = 4;  
      Data.color = color;
      Data.cols = cols;
      Data.rows = rows;
      init_matrix(Data);
      // for (int i = 0; i < rows; i++) {
      //   for (int j = 0; j < cols; j++) {
      //     int value;
      //       if (index < parts.size()){
      //         std::stringstream(parts[index]) >> value;
      //         index++;
      //         Data.matrix[i][j] = value;
      //       }
      //       else{
      //         i = rows;
      //         j = cols;
      //         break;            
      //       }
      //   }
      // }
      Serial.println(12345);
      for (int i = 0; i < rows*cols; i++) {
        int value;
        if (index < parts.size()-4){
          std::stringstream(parts[index]) >> value;
          index++;          
          Data.matrix[i] = value;
        }
        else{
          break;            
        }
      }
    } 
    else 
    {
      // Définir le message d'erreur
      // Le message doit contenir la synchronisation, la couleur et les dimenssions de la matrice
      if(parts.size() < 4) acquittement = "err1\n";

      // Envoyer le message d'acquittement    
      Serial.write(acquittement.c_str(), acquittement.size());
      return false;
    }

    // Définir le message de d'acquittement
    acquittement = "ok\n";

    // Envoyer le message d'acquittement
    Serial.write(acquittement.c_str(), acquittement.size());

    return true;
  }
  else 
  {
    // En attente de la synchronisation
    return false;
  }
}

// allocate memory for the matrix based on the values of rows and cols
void init_matrix(MatrixData& data) 
{
    //data.matrix = new int*[data.rows];
    //for (int i = 0; i < data.rows; i++) {      
        //data.matrix[i] = new int[data.cols];        
    //}
    data.matrix = new int[data.rows*data.cols];  
}

// Split the input string into separate parts
std::vector<std::string> Split_msg(String inputString)
{
  std::string inputStr = inputString.c_str(); // Convert to std::string
  std::vector<std::string> parts;
  size_t pos = 0, lastPos = 0;
  while ((pos = inputStr.find(",", lastPos)) != std::string::npos) {
      parts.push_back(inputStr.substr(lastPos, pos - lastPos));
      lastPos = pos + 1;
  }
  parts.push_back(inputStr.substr(lastPos));
  return parts;  
}

void print_data()
{
  Serial.println("");
  Serial.println("___Data___");
  Serial.println(Data.color.c_str());
  
  Serial.print(Data.rows);
  Serial.print(" par ");
  Serial.println(Data.cols);

  for (int i = 0; i < Data.rows; i++) {
    Serial.print("["); 
    for (int j = 0; j < Data.cols; j++) {     
      Serial.print(Data.matrix[i*j]);
      Serial.print(" ");
    }
    Serial.println("]");
  }
}


