#include <SerialStream.h>
#include <iostream>
#include <string>
#include <vector>

// La fonction de configuration du GPIO
bool Configuration() {
    using namespace LibSerial;

    // Définir le numéro de broche GPIO à utiliser
    const int GPIO_PIN = 4;

    // Configuration de la broche GPIO
    std::string commande = "echo " + std::to_string(GPIO_PIN) + " > /sys/class/gpio/export";
    int resultat = system(commande.c_str());

    if (resultat != 0) {
        std::cerr << "Échec de la configuration de la broche GPIO" << std::endl;
        return false;
    }

    return true;
}

// La fonction de lecture des données série
bool ProtocoleSerie() {
   using namespace LibSerial;

   // Ouvrir la liaison série
   SerialStream serie("/dev/ttyUSB0", LibSerial::BaudRate::BAUD_57600);

   // Vérifier si la communication est établie
   if (!serie.good()) {
      std::cerr << "Impossible d'ouvrir la liaison série" << std::endl;
      return false;
   }

   // Définir les messages de synchronisation et d'acquittement
   std::string synchronisation = "sync\n";
   std::string acquittement = "ack\n";

   // Attendre la réception des 4 premiers caractères (message de synchronisation)
   std::string s;
   std::getline(serie, s);
   if (s != synchronisation) {
      return false;
   }

   // Lecture des données
   std::string color;
   std::getline(serie, color);

   int rows, cols;
   serie >> rows >> cols;

   std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           int value;
           serie >> value;
           matrix[i][j] = value;
       }
   }

   // Envoyer le message d'acquittement
   serie.write(acquittement.c_str(), acquittement.size());

   // Fermer la liaison série
   serie.Close();

   return true;
}
