#pragma once
#include "api.h"

//Define Controller
inline pros::Controller Master = (pros::E_CONTROLLER_MASTER);

//Define Inertial Sensor
inline pros::IMU Gyro(5);

//Define Motor's
	//Drive Left Side
inline pros::Motor LeftBack(1, pros::E_MOTOR_GEAR_GREEN, true);
inline pros::Motor LeftHalf(2, pros::E_MOTOR_GEAR_GREEN, false);
inline pros::Motor LeftFront(3, pros::E_MOTOR_GEAR_GREEN, true);
	//Drive Right Side
inline pros::Motor RightBack(8, pros::E_MOTOR_GEAR_GREEN, false);
inline pros::Motor RightHalf(9, pros::E_MOTOR_GEAR_GREEN, true);
inline pros::Motor RightFront(10, pros::E_MOTOR_GEAR_GREEN, false);
	//Flystick
inline pros::Motor Flystick(19, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
	//Flywheel
inline pros::Motor Flywheel(20, pros::E_MOTOR_GEAR_BLUE, true);
	//Intake
inline pros::Motor Intake(14, pros::E_MOTOR_GEAR_GREEN, false);

//Declare Motor Groups
	//Drive
inline pros::Motor_Group LeftDB({LeftBack, LeftHalf, LeftFront});
inline pros::Motor_Group RightDB({RightBack, RightHalf, RightFront});
inline pros::Motor_Group DB({LeftBack, LeftHalf, LeftFront, RightBack, RightHalf, RightFront});


//Define API Ports
	//Pneumatics
inline pros::ADIDigitalOut Wings('A', false);
inline pros::ADIDigitalOut Rachet('B', false);
	//Auto Selectors and Temperature Checker
inline pros::ADIDigitalIn Selector('G');

