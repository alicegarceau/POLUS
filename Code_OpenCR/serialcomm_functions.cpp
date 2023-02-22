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
#include <Arduino.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

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
  Serial.println("Communication détecté");
}

bool get_msg()
{
 /**
 * Fonction de lecture de message et filtre le device ID du RaspberryPi
 * @param { } 
 * @return { bool }
 */

// Read the data from the serial port
String inputString = Serial.readStringUntil('\n');

// Split the input string into separate parts
std::string inputStr = inputString.c_str(); // Convert to std::string
std::vector<std::string> parts;
size_t pos = 0, lastPos = 0;
while ((pos = inputStr.find(",", lastPos)) != std::string::npos) {
    parts.push_back(inputStr.substr(lastPos, pos - lastPos));
    lastPos = pos + 1;
}
parts.push_back(inputStr.substr(lastPos));

// Extract the individual values
if (parts.size() == 4 && parts[0] == "sync") {
  Serial.println("Synchronisation réussi");
  color = parts[1];
  std::stringstream(parts[2]) >> rows;
  std::stringstream(parts[3]) >> cols;
  std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
  int value;
  for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
          serie >> value;
          matrix[i][j] = value;
      }
  }  
  // Process the rest of the data as needed
} 
else {
  Serial.println("Erreur de synchronisation");
  return false;
}

  // Définir le message de d'acquittement
   std::string acquittement = "ack\n";

   // Envoyer le message d'acquittement
   Serial.write(acquittement.c_str(), acquittement.size());

   return true;
}

void read_msg();
{

}

String should_wash(String& state)
{
 /**
 * Fonction de lecture de message et détermine si on nettoie la cage
 * @param { String& } state     // state = message à analyser 3 mots, exemple: {"WASH 80 60"}
 * @return { String }           // retourne deux integer en chaine de caractere, exemple: {"80 60"}
 */

 // séparation du message en vecteur de 3 string
  String words[3];
  String out;
  int StringCount = 0;

  while (state.length() > 0)
  {
    int index = state.indexOf(' ');
    if (index == -1) // No space found
    {
      words[StringCount++] = state;
      break;
    }
    else
    {
      words[StringCount++] = state.substring(0, index);
      state = state.substring(index+1);
    }
  }

  // lecture du premier mot et vérification de s'il est égal a WASH
  if (words[0] == "WASH")
  { 
    out = words[1] + " " + words[2];
    return out;
  }
  else
  {
    return out;
  }
  
}

bool should_trash(String& state)
{
 /**
 * Fonction de lecture de message et détermine si on nettoie la poubelle
 * @param { String& } state     // state = message à analyser 1 mots, exemple: {"TRASH"}
 * @return { bool }     
 */
  if (state == "TRASH")
  {
    return true;
  }
  else
  {
    return false;
  }
   
}

String send_msg(const String& msg)
{
 /**
 * Fonction de lecture de message et détermine si on nettoie la cage
 * @param { String& } state     // state = message à analyser 3 mots, exemple: {"WASH 80 60"}
 * @return { String }           // retourne deux integer en chaine de caractere, exemple: {"80 60"}
 */
  String msg_envoye = msg;
  Serial.println(msg_envoye);
  return msg_envoye;
}

bool should_init(const String& state)
{
 /**
 * Fonction de lecture de message et détermine si on active la cage
 * @param { String& } state     // state = message à analyser 1 mots, exemple: {"INIT"}
 * @return { bool }     
 */
  if (state == "INIT")
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool should_start(const String& state)
{
 /**
 * Fonction de lecture de message et détermine si on active la cage
 * @param { String& } state     // state = message à analyser 1 mots, exemple: {"START"}
 * @return { bool }     
 */
  if (state == "START")
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool should_end(const String& state)
{
 /**
 * Fonction de lecture de message et détermine si on désactive la cage
 * @param { String& } state     // state = message à analyser 1 mots, exemple: {"END"}
 * @return { bool }     
 */
  if (state == "END")
  {
    return true;
  }
  else
  {
    return false;
  }
}
