/*
Projet: POLUS
Description: Méthode principale (main) qui gère la communication et les actions du robot à haut niveau
Auteurs: Frédérik Desaulniers – DESF3105
         Pierre-Olivier Dupont – DUPP2408
         Alice Garceau – GARA2507
         Enrick Hébert – HEBE2701
         Émile Michaud – MICE1602
*/

#include "stepperZ.hpp"

//Declare variables for functions
const int MAX_MM = 100; // Limit logicielle, hauteur maximale permise par rapport à la position d'origine (interrupteur de fin de course)
const int MIN_MM =   5; // Limit logicielle, hauteur minimale permise par rapport à la position d'origine (interrupteur de fin de course)
static int currPosmm; // Position actuelle en mm
const float OffsetCoeff = 0.0025;

int oneTime = 1;


// Pour deboguage
//Main loop 
//void loop() {
//  while( oneTime ) {
//    homeZ();
//    stepperGoToPos( 20 );
//    delay(5000);
//    stepperGoToPos( 50 );
//    oneTime = 0;
//  }
//}

void setupStepper()
  // À mettre dans la fonction setup du fichier principal
{
  pinMode(PIN_STP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_MS1, OUTPUT);
  pinMode(PIN_MS2, OUTPUT);
  pinMode(PIN_EN, OUTPUT);
  pinMode(PIN_SW, INPUT_PULLUP);
  digitalWrite(PIN_STP, LOW);
  digitalWrite(PIN_DIR, LOW);
  digitalWrite(PIN_MS1, LOW);
  digitalWrite(PIN_MS2, LOW);
  digitalWrite(PIN_EN, HIGH);
}

void resetEDPins()
// Remettre les broches du Easy Driver à leur état de départ (au setup)
{
  digitalWrite(PIN_STP, LOW);
  digitalWrite(PIN_DIR, LOW);
  digitalWrite(PIN_MS1, LOW);
  digitalWrite(PIN_MS2, LOW);
  digitalWrite(PIN_EN, HIGH);
}

void homeZ()
// Retourner à la position d'origine en Z. Descend jusqu'à toucher l'interrupteur de fin de course, puis remonte de MIN_MM.
{
  digitalWrite(PIN_MS1, HIGH);
  digitalWrite(PIN_MS2, HIGH);
  digitalWrite(PIN_EN, LOW);
  digitalWrite(PIN_DIR, LOW);
  while( digitalRead(PIN_SW) != false )
  {
    digitalWrite(PIN_STP,HIGH); // Déclencher un pas
    delayMicroseconds(500);     // Attendre pour le mouvement mécanique du rotor. Delais plus long vs mouvement pour avancer lentement
    digitalWrite(PIN_STP,LOW); // Remettre la broche à l'état BAS, pour pouvoir la réactiver
    delayMicroseconds(500);
  }
  currPosmm = 0;
  //Serial.println(currPosmm);
}

float updateZOffset(float yPos)
{
  float ZOffset;
  ZOffset = yPos * OffsetCoeff;
  return ZOffset;
}

// 1/8th microstep foward mode function
void stepperGoToPos(float goalmm) // goalmm, 
{
// Aller à une position donnée en mm par rapport à la position d'origine. Utilise le mode micro-stepping à 1/8 de pas.


  float displacementmm = goalmm - currPosmm; 
  currPosmm += displacementmm;
  int nMicroSteps = abs((displacementmm / MM_PER_TURN) * STEPS_PER_TURN * MICRO_STEPS); // Calcul du nombre de micro-pas requis pour atteindre la destination
  int direction;
  if (displacementmm < 0) {
    direction = LOW;
  } else {
    direction = HIGH;
  }
  digitalWrite(PIN_DIR, direction); // Établi l'état BAS ou HAUT de la broche de contrôle de la direction. Dépend du signe de la cible (distmm)
  digitalWrite(PIN_MS1, HIGH); // Établi l'état des broches PIN_MS1 et PIN_MS2 à HAUT pour que le mode micro-stepping soit à 1/8 de pas.
  digitalWrite(PIN_MS2, HIGH);
  digitalWrite(PIN_EN, LOW); // Établi l'état BAS de la broche de désactivation pour permettre le mouvement.

  for(int x= 1; x<nMicroSteps; x++)  
  {
    digitalWrite(PIN_STP,HIGH); // Déclencher un pas
    delayMicroseconds(100);     // Délais minimal de 100 microsecondes pour laisser le temps au rotor d'arriver à sa position de micro-pas
    digitalWrite(PIN_STP,LOW); // Remettre la broche à l'état BAS, pour pouvoir la réactiver
    delayMicroseconds(100);
  }

}
