#include "api.h"

//Define Controller
pros::Controller Master = (pros::E_CONTROLLER_MASTER);

//Define Inertial Sensor
pros::IMU Gyro(5);

//Define Motor's
	//Drive Left Side
pros::Motor LeftBack(1, pros::E_MOTOR_GEAR_GREEN, true);
pros::Motor LeftHalf(2, pros::E_MOTOR_GEAR_GREEN, false);
pros::Motor LeftFront(3, pros::E_MOTOR_GEAR_GREEN, true);
	//Drive Right Side
pros::Motor RightBack(8, pros::E_MOTOR_GEAR_GREEN, false);
pros::Motor RightHalf(9, pros::E_MOTOR_GEAR_GREEN, true);
pros::Motor RightFront(10, pros::E_MOTOR_GEAR_GREEN, false);
	//Flystick
pros::Motor Flystick(19, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
	//Flywheel
pros::Motor Flywheel(20, pros::E_MOTOR_GEAR_BLUE, true);
	//Intake
pros::Motor Intake(14, pros::E_MOTOR_GEAR_GREEN, false);

//Declare Motor Groups
	//Drive
pros::Motor_Group LeftDB({LeftBack, LeftHalf, LeftFront});
pros::Motor_Group RightDB({RightBack, RightHalf, RightFront});
pros::Motor_Group DB({LeftBack, LeftHalf, LeftFront, RightBack, RightHalf, RightFront});


//Define API Ports
	//Pneumatics
pros::ADIDigitalOut Wings('A', false);
pros::ADIDigitalOut Rachet('B', false);
	//Auto Selectors and Temperature Checker
pros::ADIDigitalIn SkillsSelector('G');
pros::ADIPotentiometer AutoSelector('H', pros::E_ADI_POT_V2);