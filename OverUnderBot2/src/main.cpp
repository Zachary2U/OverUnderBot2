#include "main.h"
//#include <iostream>


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
pros::Motor FlystickRachetSide(14, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor FlystickNonRachetSide(19, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
	//Flywheel
pros::Motor Flywheel(20, pros::E_MOTOR_GEAR_BLUE, true);

//Declare Motor Groups
	//Drive
pros::Motor_Group LeftDB({LeftBack, LeftHalf, LeftFront});
pros::Motor_Group RightDB({RightBack, RightHalf, RightFront});
pros::Motor_Group DB({LeftBack, LeftHalf, LeftFront, RightBack, RightHalf, RightFront});
	//Flystick
pros::Motor_Group Flystick({FlystickNonRachetSide, FlystickRachetSide});


//Define API Ports
	//Pneumatics
pros::ADIDigitalOut Wings('A', false);
pros::ADIDigitalOut Rachet('B', false);
	//Potentiometer
pros::ADIPotentiometer AutoSelector('H', pros::E_ADI_POT_V2);

//Global Variables
int flystick= 0;

void driverControl(){
	double power = Master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	double turn = Master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

	LeftDB.move(power + turn);
	RightDB.move(power - turn);
}
//Flystick Programs
void FlystickExtend(){
	while(FlystickNonRachetSide.get_position() != 120){
		Flystick.move(100);
	}
	Flystick.brake();
}


//Flywheel speed
void flywheelRun(double volts){}


void flywheelHeightUp(){
	if (flystick < 2) {
		flystick++;
	}
}

void flywheelHeightDown(){
	if (flystick > 0) {
		flystick--;
	}
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	Flystick.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
}
bool fly = false;
void flywheelRun(){
	fly = Master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
	if(fly){
		Flywheel.move(105);
	}
	else{
		Flywheel.move(0);
	}
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

	Flystick.move(30);
	pros::delay(75);
	Flystick.brake();
	DB.move(-30);
	pros::delay(1500);
	DB.brake();


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

/*void moveFlystickTo(double degrees) {
	Flystick.move_absolute(degrees, 100);
}
void flystickThread() {
	while (true) {
		switch (flystick) {
			case 0:
				moveFlystickTo(0); 
				break;
			case 1: 
				moveFlystickTo(-105); 
				break;
			case 2: 
				moveFlystickTo(-150); 
				break;
		}
		pros::delay(20);
	}
}*/
void opcontrol() {
	//pros::Task flystickWork(flystickThread);
	while (true) {

		driverControl();
		flywheelRun();
		/*if (Master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			flywheelHeightUp();
		}
		if (Master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			flywheelHeightDown();
		}*/


		if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
			Flystick.move(60);
		}
		else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			Flystick.move(-60);
		}
		else{
			Flystick.brake();
		}

		if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			Rachet.set_value(true);
		}

		if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			Wings.set_value(false);
		}
		else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			Wings.set_value(true);
		}

	}
}
