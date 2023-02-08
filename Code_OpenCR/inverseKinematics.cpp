#include "inverseKinematics.hpp"


void inverse_kinematics(float x, float y, float THETA[2])
{
    // Makes sure the input coordinates are reachable with the current arm segment lengths
    if ((x >= -200 && x <= 200) && (y >= 0 && y <= 270))
    {
        float LA = 150; //mm
        float LB = 120; //mm

        //Basé sur video: https://www.youtube.com/watch?v=6KOEQfsgy8Q&ab_channel=Engineering_life
        //Calcul d'angle en radian
        //THETA[0] = PI/2 - (atan(y/x)-acos(pow(LA,2) - pow(LB,2) + pow(x,2) + pow(y,2) / ( 2 * LA * sqrt(pow(x,2) + pow(y,2)))));
        THETA[0] =  PI/2 - (atan(y/x)-acos(pow(LA,2) - pow(LB,2) + pow(x,2) + pow(y,2) / ( 2 * LA * sqrt(pow(x,2) + pow(y,2)))));
        THETA[1] = -(PI-acos((pow(LA,2) + pow(LB,2) - pow(x,2) - pow(y,2))/(2 * LA * LB)));

        //Transfert de radian à degré
        THETA[0] = THETA[0] * 180 / PI;
        THETA[1] = THETA[1] * 180 / PI;

        // Makes sure there won't be a collision with the calculated angles
        // Danger zone = (-THETA[0] (Quadrant 3) and +THETA[1] (Quadrant 1))
        /*if (THETA[0] < -100 || THETA[0] > 100 || THETA[1] < -100 || THETA[1] > 100)
        {
            Serial.println("Erreur: Collision évitée");
            THETA[0] = 0;
            THETA[1] = 0;
        }*/

        Serial.println(THETA[0]);
        Serial.println(THETA[1]);
        Serial.println(" ");
    }
    else
    {
        Serial.println("Erreur: Angles inatteignable");
        THETA[0] = 0;
        THETA[1] = 0;
    }
}