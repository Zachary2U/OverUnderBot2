#include "main.h"
#include "organization.h"
#include "chassis.h"
#include <initializer_list>
//#include <iostream>

//Create PID objects
PID Linear(20, 0, 2);
PID Angular(1, 0, 0);


//Create Chassis object
Chassis Drive(std::make_unique<pros::MotorGroup>(std::initializer_list<pros::Motor>{LeftBack, LeftHalf, LeftFront}),
std::make_unique<pros::MotorGroup>(std::initializer_list<pros::Motor>{RightBack, RightHalf, RightFront}),
Linear, 
Angular);

/*
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	Gyro.set_rotation(0);
	Flystick.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	Flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	//pros::lcd::initialize();
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//pros::Task screenPrint(printToScreen);

	Drive.turn(90, 10000);
}
	

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

bool flywheelSpin = false;
void opcontrol() {
	pros::Task flywheel(flywheelTask);
	while (true) {
		//screenPrint;
		driverControl();
		if(flywheelSpin){
			flywheel;
		}
		wings();
		flystick();
		intake();
		if(Selector.get_value()){
			pros::Task temps(printTemp);
		}

		//Flywheel movement
		if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
			flywheelSpin = true;
		}
		if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			flywheelSpin = false;
		}
	}
}