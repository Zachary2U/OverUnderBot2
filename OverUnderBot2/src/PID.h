#pragma once
#include "api.h"
#include "Objects.h"
#include <vector>
//Used soley for organizing the code for simplicity and ease of access

class PID{
    protected:
    double kP;
    double kI;
    double kD;
    double pastError;
    double pastTime;
    double setPoint;
    double error;
    
    public: PID(){
        kP = 0;
        kI = 0;
        kD = 0;
    }

    public: 
    
    inline PID(double KP, double KI, double KD){
        kP = KP;
        kI = KI;
        kD = KD;
    }

    inline double update(double reading){
        error = setPoint - reading;
        double time = pros::millis() / 1000.0;
        double deltaError = error - pastError;
        double deltaTime = time - pastTime;
        double p = kP * error;
        double i = kI * deltaTime;
        double d = ((error - pastError) / deltaTime) * kD;
        pros::delay(20);
        pastError = error;
        pastTime = time;
        return p + i + d;
    }

    inline double getError(){
        return error;
    }

    inline double getSetPoint() {
        return setPoint;
    }

    inline void setSetPoint(double point){
        setPoint = point;
        error = setPoint;
    }
};