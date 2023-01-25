#include "cinematiqueInverse.hpp"
//#include <Arduino.h>
#include <math.h>

void cinematiqueInverse(float x, float y)
{
    // Makes sure the input coordinates are reachable with the current arm segment lengths
    float THETA[2] = { 0, 0 };

    if ((x >= -100 && x <= 100) && (y >= 0 && y <= 200))
    {
        float LA = 150; //mm
        float LB = 120; //mm
    
        THETA[0] = atan(y/x)-acos((LA^2-LB^2+x^2+y^2)/(2*LA*sqrt(x^2+y^2)));
        THETA[1] = 180-acos((LA^2 + LB^2 - x^2 - y^2)/(2*LA*LB));

        // Makes sure there won't be a collision with the calculated angles
        // Danger zone = (-THETA[0] (Quadrant 3) and +THETA[1] (Quadrant 1))
        if (THETA[0] < 0 || THETA[0] > 180 || THETA[1] < 0 || THETA[1] > 180)
        {
            //Serial.println("Erreur: Collision évitée");
            THETA[0] = 0;
            THETA[1] = 0;
        }
    }
    else
    {
        //Serial.println("Erreur: Angles inatteignable");
        THETA[0] = 0;
        THETA[1] = 0;
    }

    return THETA;
}