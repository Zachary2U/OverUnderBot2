#pragma once
#include "api.h"
#include "PID.h"
#include <iostream>

class Chassis{
    //Instance data
    private:
    int settlingStart = 0;
    bool isSettling = false;

    PID linearPID;
    PID angularPID;
    std::unique_ptr<pros::MotorGroup> Left;
    std::unique_ptr<pros::MotorGroup> Right;

    double motorStart;

    public: 
    inline Chassis(std::unique_ptr<pros::MotorGroup> left, std::unique_ptr<pros::MotorGroup> right, PID linear, PID angular){
        linearPID = linear;
        angularPID = angular;

        Left = std::move(left);
        Right = std::move(right);
        Left->tare_position();
        Right->tare_position();
        motorStart = getMotorAvgPosition();
        Left->set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_ROTATIONS);
        Right->set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_ROTATIONS);
    }

    inline double getMotorAvgPosition(){
        double readings = 0;
        double denominator = 6;
        for(double m : Left->get_positions()){
            readings += m;
        }
        for(double m : Right->get_positions()){
            readings += m;
        }
        return (readings / denominator) * 2 * M_PI * 1.625 * 60.0/36.0 - motorStart;
    }


    inline void move(double distance, double timeout){
        double startTime = pros::millis();
        setLinearTarget(distance);
        isSettling = false;
        double startingPos = getMotorAvgPosition();
        pros::lcd::print(4, "Avg Position: %f", startingPos);
        pros::lcd::print(1, "Current error: %f", linearPID.getError());
        while(true){

            int currentTime = pros::millis();

            if (linearPID.getError() < 0.5) {
                if(!isSettling) {
                    isSettling = true;
                    settlingStart = pros::millis();
                } else {
                    if (currentTime - settlingStart > 500) {
                        break;
                    }
                }
            } else if (currentTime - startTime > timeout) {
                break;
            } else {
                isSettling = false;
            }

            pros::lcd::print(0, "Setpoint: %f", linearPID.getSetPoint());
            pros::lcd::print(1, "Current error: %f", linearPID.getError());
            
            double power = linearPID.update(getMotorAvgPosition());
            drivePower(power);
        }
        drivePower(0);
        pros::lcd::print(3, "Final Position: %f", (linearPID.getError() + fabs(startingPos)));
    }

    inline void turn(double angle, double timeout){
        double startTime = pros::millis();
        angularPID.setSetPoint(angle);
        while(angularPID.getError() > 0.5 + Gyro.get_heading() && pros::millis() < timeout + startTime){
            turnPower(angularPID.update(Gyro.get_heading()));
            pros::lcd::print(0, "Gyro Position: %f", (Gyro.get_heading()));
        }
        pros::lcd::print(0, "Gyro End: %f", (Gyro.get_heading()));
    }

    inline void drivePower(double volts){
        Right->move(volts);
        Left->move(volts);
    }

    inline void turnPower(double volts){
        Right->move(volts);
        Left->move(-volts);
    }

    private: void setLinearTarget(double inches){
        linearPID.setSetPoint(getMotorAvgPosition() + inches);
    }

};

