#include "inverseKinematics.hpp"


void inverse_kinematics(float x, float y, float THETA[2])
{
    // Makes sure the input coordinates are reachable with the current arm segment lengths
    if ((y >= 0) && ( sqrt(pow(x,2) + pow(y,2)) <= 264.78 ) && (sqrt(pow(x,2) + pow(y,2)) >= 35.22))
    {
        float LA = 150; //mm
        float LB = 114.78; //mm

        //Basé sur video: https://www.youtube.com/watch?v=6KOEQfsgy8Q&ab_channel=Engineering_life
        //Calcul d'angle en radian
        THETA[1] = acos((pow(x,2) + pow(y,2) - pow(LA,2) - pow(LB,2) )/(2 * LA * LB));
        THETA[0] = PI/2 - (atan2(y,x) - atan2(LB * sin(THETA[1]), LA + (LB * cos(THETA[1]))));
        

        //Transfert de radian à degré
        THETA[0] = (-THETA[0] * 180 / PI)*1.667;
        THETA[1] = (THETA[1] * 180 / PI);

        // Makes sure there won't be a collision with the calculated angles
        if (THETA[0] < -90*1.667 || THETA[0] > 90*1.667 || THETA[1] < 0 || THETA[1] > 140 /*140*1.667*/ )
        {
            Serial.println("Erreur: Collision évitée");
            THETA[0] = 0;
            THETA[1] = 0;
        }
    }
    else
    {
        Serial.println("Erreur: Angles inatteignable");
        THETA[0] = 0;
        THETA[1] = 0;
    }
}