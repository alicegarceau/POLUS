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

PixelData Data;
std::time_t last_time = std::time(nullptr);

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

// Alloue la mémoire de la liste des positions.
void init_positions(int size) 
{
    std::vector<int> temp(size);
    Data.positions = temp;
}

void next_msg()
{
  std::string done = "done\n";

  bool msg_ok = false;
  while(!msg_ok)
  {
    Serial.write(done.c_str(), done.size());
    delay(50);
    msg_ok = get_msg();
  }
}

// Lit les données du port série et appelle la bonne fonction selon le type de message envoyé.
bool get_msg()
{
  String inputString = Serial.readStringUntil('\n');
  if (inputString.startsWith("sync")) {
    //Serial.print("Message reçu: ");
    //Serial.println(inputString);
    std::vector<std::string> parts = Split_msg(inputString);
    
    // déterminer le type de message
    if (parts[1] == "pixels") return decode_pixel(parts);
    else if (parts[1] == "lignes") return decode_lignes(parts);
    else if (parts[1] == "jog") return decode_jog(parts);
    else return false;
  }
  else {
    // En attente de la synchronisation
    return false;
  }
}

// Divise la chaîne d'entrée en parties distinctes.
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

bool decode_pixel(std::vector<std::string> parts){
  //définir le message d'aquittement pour une erreur inconnue;
  std::string acquittement = "err0\n";

  // Extract the individual values
  if (parts.size() >= 4) {
    std::stringstream(parts[2]) >> Data.color;
    std::stringstream(parts[3]) >> Data.cols;
    std::stringstream(parts[4]) >> Data.rows;
    
    int value; 
    init_positions(parts.size()-5);
    for (int i = 5; i < parts.size(); i++) {
        std::stringstream(parts[i]) >> value;         
        Data.positions[i-5] = value;
    }

    // Définir le message de d'acquittement
    acquittement = "ok\n";

    // Envoyer le message d'acquittement
    Serial.write(acquittement.c_str(), acquittement.size());

    return true;
  } 
  else {
    // Définir le message d'erreur
    // Le message doit contenir la synchronisation, la couleur et les dimenssions de la matrice
    if(parts.size() < 4) acquittement = "err1\n";

    // Envoyer le message d'acquittement    
    Serial.write(acquittement.c_str(), acquittement.size());
    return false;
  }
}

bool decode_lignes(std::vector<std::string> parts){

  return true;
}

bool decode_jog(std::vector<std::string> parts){
  
  return true;
}

void ChangeAction(){
  std::time_t act_time = std::time(nullptr);
  if (act_time-last_time >= 1)
  {
    String inputString = Serial.readStringUntil('\n');
    if(inputString.startsWith("sync,stop")) Serial.println("Arrêt demandé"); 
    last_time = act_time;
  }
}


void print_data(){
  Serial.println("");
  Serial.println("___Data___");
  Serial.println(Data.color);
  
  Serial.print(Data.rows);
  Serial.print(" par ");
  Serial.println(Data.cols);
  Serial.print("{"); 
  for (int i = 0; i < Data.positions.size(); i++) {  
    Serial.print(Data.positions[i]);
    Serial.print(" ");
  }
  Serial.println("}");
}



