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

    public: PID(double KP, double KI, double KD){
        kP = KP;
        kI = KI;
        kD = KD;
    }

    double update(double reading, bool isTurn){
        error = reading;
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

    double getError(){
        return error;
    }

    double getMotorAvgPosition(std::vector<double> left, std::vector<double> right){
        double rightReadings = 0;
        double leftReadings = 0;
        double denominator = 6;
        for(double m : left){
            leftReadings += m;
        }
        for(double m : right){
            rightReadings += m;
        }
        return (rightReadings + leftReadings) / denominator;
    }

    void setSetPoint(double point, std::vector<double> left, std::vector<double> right){
        setPoint = point + getMotorAvgPosition(right, left);
    }
};