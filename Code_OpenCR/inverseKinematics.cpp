/*
Projet: POLUS
Description: Fonctions qui gerent la cinematique inverse du robot 
Auteurs: Frédérik Desaulniers – DESF3105
         Pierre-Olivier Dupont – DUPP2408
         Alice Garceau – GARA2507
         Enrick Hébert – HEBE2701
         Émile Michaud – MICE1602
*/

#include "inverseKinematics.hpp"
const float epauleRatio = 1.667;
const float LA = 150; //mm
const float LB = 114.78; //mm
const float epauleZeroOffset = -2.73;
const float coudeZeroOffset = 1.97;

void inverse_kinematics(float x, float y, float THETA[2])
{
    // S'assurer que les coordonnées en entrée sont atteignables
    if ((y >= 0) && ( sqrt(pow(x,2) + pow(y,2)) <= 264.78 ) && (sqrt(pow(x,2) + pow(y,2)) >= 35.22))
    {
        //Calcul d'angle en radian
        THETA[1] = acos((pow(x,2) + pow(y,2) - pow(LA,2) - pow(LB,2) )/(2 * LA * LB));
        THETA[0] = PI/2 - (atan2(y,x) - atan2(LB * sin(THETA[1]), LA + (LB * cos(THETA[1]))));
        

        //Transfert de radian à degré
        THETA[0] = ((-THETA[0] * 180 / PI)*epauleRatio)+(epauleZeroOffset*epauleRatio);
        THETA[1] = ((THETA[1] * 180 / PI))+coudeZeroOffset;

        // S'assurer que les angles ne cause pas de colision avec le bras
        if (THETA[0] < -90*1.667 || THETA[0] > 90*1.667 || THETA[1] < 0 || THETA[1] > 155 /*140*1.667*/ )
        {
            Serial.print("Erreur: Collision évitée : ");
            Serial.print(THETA[0]);
            Serial.print(" : ");
            Serial.println(THETA[1]);
            THETA[0] = 0+(epauleZeroOffset*epauleRatio);
            THETA[1] = 0+coudeZeroOffset;
        }
    }
    else
    {
        Serial.println("Erreur: Angles inatteignable");
        THETA[0] = 0+(epauleZeroOffset*epauleRatio);
        THETA[1] = 0+coudeZeroOffset;
    }
}
