#include "api.h"
#include "PID.h"
#include <iostream>

class Chassis{
    //Instance data
    private:
    PID linearPID;
    PID angularPID;
    std::unique_ptr<pros::MotorGroup> Left;
    std::unique_ptr<pros::MotorGroup> Right;

    public: Chassis(std::unique_ptr<pros::MotorGroup> left, std::unique_ptr<pros::MotorGroup> right, PID linear, PID angular){
        linearPID = linear;
        angularPID = angular;
        Left = std::move(left);
        Right = std::move(right);
    }


    void drivePID(double distance, double timeout){
        //while()
    }

    void turnPID(double angle, double timeout){
        double startTime = pros::millis();
        while(angularPID.getError() > 0.5 + Gyro.get_heading() && pros::millis() < timeout + startTime){
            turnPower(angularPID.update(Gyro.get_heading(), true));
        }
        angularPID.setSetPoint(0, Left->get_positions(), Right->get_positions());
    }

    double drivePower(double volts){
        Right->move(volts);
        Left->move(volts);
    }

    double turnPower(double volts){
        Right->move(volts);
        Left->move(-volts);
    }
}
;