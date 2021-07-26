/*
 * Library for AEBO Robot 
 * Created by Lokesh Kode, July 26,2021.
 * Released into public domain
*/


#ifndef AEBO_H
#define AEBO_H

#include "Arduino.h"


class AEBO{

  public:
    AEBO();

    //Movement Functions
    void Forward(int speed);
    void Backward(int speed);
    void Left(int speed);
    void Right(int speed);
    void StopRobot();  

    //Distance Function
    float distance(int trigPin, int echoPin);

   private:

    int _trigpin;
    int _echopin;
    
    
};

#endif
