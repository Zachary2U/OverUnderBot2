#include "main.h"
#include "organization.h"
#include "Objects.h"
//#include "chassis.h"
#include <cerrno>
#include <initializer_list>
//#include <iostream>

//Lemlib Stuff
//=================================================

lemlib::Drivetrain drivetrain {
    &LeftDB, // left drivetrain motors
    &RightDB, // right drivetrain motors
    11.5, // track width
    lemlib::Omniwheel::NEW_325, // wheel diameter
    (200 * (60.0/36.0)),// wheel rpm
    2
};

lemlib::OdomSensors sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &Gyro // inertial sensor
};

//Forward Backward Movement
lemlib::ControllerSettings lateralController {
    9, // kP
    0, // kI
    37, // kD
    3, 
    0.6, // smallErrorRange
    250, // smallErrorTimeout
    1.3, // largeErrorRange
    500, // largeErrorTimeout
    12 // slew rate
};
 
// Left Right Movement
lemlib::ControllerSettings angularController {
    1.87, // kP
    0, // kI
    12.34, // kD
    3, 
    0.7, // smallErrorRange
    300, // smallErrorTimeout
    1.2, // largeErrorRange
    500, // largeErrorTimeout
    11 // slew rate
};

lemlib::Chassis Drive(drivetrain, lateralController, angularController, sensors);

//PID's
//PID angularPID(0, 0, 0);
//PID linearPID(0, 0, 0);

//Unique Pointers

/*Chassis drive = Chassis(
    std::make_unique<pros::MotorGroup>(std::initializer_list<pros::Motor>({LeftBack, LeftHalf, LeftFront})), 
    std::make_unique<pros::MotorGroup>(std::initializer_list<pros::Motor>({RightBack, RightHalf, RightFront})), 
    linearPID, 
    angularPID
    );*/


void turn(double theta, bool forwards, double timeout, double maxSpeed){
	theta = theta * -1 ;
	//Account for current degrees rotated
	theta += Drive.getPose().theta;

	// Find coordinates accounting for current position
	double x = 1000 * (cos(theta) + Drive.getPose().x);
  	double y = 1000 * (sin(theta) + Drive.getPose().y);

	//Execution
	Drive.turnTo(x, y, timeout, forwards, maxSpeed);
}

// Instantiate Right side auton
void oldRightAuton(){
    Intake.move(127);
    Drive.moveToPoint(0, 8, 1000, true, 127);
    pros::delay(600);
    Drive.moveToPoint(2, -23, 1200, false, 70, false);
    Drive.moveToPose(5, -35, -17, 1200, {.forwards = false});
    Drive.moveToPose(6.7, -37.8, -36, 1500, {.forwards = false}, false);
    Wings.set_value(true);
    Drive.moveToPoint(10.4, -43, 1000, false, 127, false);
    Drive.moveToPose(14.5, -45, -85, 1200, {.forwards = false, .maxSpeed = 75}, false);
    Wings.set_value(false);
    Drive.moveToPoint(64.5, -66, 1000, false, 127, true);
    Drive.waitUntil(12);
    Wings.set_value(false);
    Drive.moveToPoint(23, -48, 1000);
    Drive.turnTo(Drive.getPose().x * 100, Drive.getPose().y, 1000, true, 90, false);
    pros::delay(500);
    Intake.move(-127);
    pros::delay(550);
    Drive.moveToPoint(64.5, -66, 1000);
    Drive.turnTo(Drive.getPose().x * 100, Drive.getPose().y, 1000, false, 90, false);
}


//Instantiate Right side auton
void newRightAuton(){
    Intake.brake();
    Drive.moveToPoint(0, 42, 1500);
    Drive.turnTo(1000, 42, 1000, true, 90, false);
    Intake.move(-127);
    pros::delay(600);
    Drive.moveToPoint(-40, 33, 1500, true, 100);
    Intake.move(127);
    Drive.moveToPose( -1, 54, -90, 2000, {.forwards = false, .chasePower = 3});
    Drive.waitUntil(12);
    Wings.set_value(true);
    Drive.moveToPoint(24, 52, 1000, false);
    Drive.moveToPoint(5, 52, 1000);
    Wings.set_value(false);
    Drive.turnTo(100, 52, 1000, true, 90, false);
    Intake.move(-127);
    pros::delay(600);
    Drive.turnTo(-100, 52, 1000, true);
    Intake.move(127);
    Drive.moveToPoint(-40, 57, 1000);
    Drive.turnTo(100, 52, 1000, true);
    Drive.moveToPoint(24, 52, 1000);
    Drive.waitUntil(16);
    Intake.move(-127);
}


// Instantiate Left side auton
void oldLeftAutonAWP(){
    Drive.moveToPose(25.4, 35, 54, 1000, {}, false);
    pros::delay(500);
    Wings.set_value(true);
    Drive.moveToPoint(4, 15, 1000, false);
    Drive.turnTo(0, 100, 1000);
    Wings.set_value(false);
    Flystick.move(127);
    pros::delay(1100);
    Flystick.brake();
    Drive.moveToPoint(-5, -40, 1000, false, 80, false);
    Flystick.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

// Instantiate Left side auton (Focused on scoring points)
void newLeftAuton(){
    Drive.moveToPoint(0, -44, 1000, false);
    Drive.turnTo(-1000, -44, 1000, false, 127, false);
    Wings.set_value(true);
    Drive.moveToPoint(-34, -44, 1000, false, 127, false);
    Wings.set_value(false);
    Drive.moveToPose(13, -1, 50, 3000, {.chasePower = 5, .minSpeed = 40}, false);
    Drive.turnTo(-2, 23, 1000, false, 127, false);
    Drive.moveToPoint(1, 15, 1000, false, 50);
    Wings.set_value(true);
    Drive.waitUntilDone();
    Wings.set_value(false);
    pros::delay(1000);
    Drive.turnTo(-100, 0, 1000, false, 55);
    pros::delay(500);
    Drive.moveToPoint(-31, 12, 1500, false, 90);
}

void mattLeftAuto(){
    //decent tested
    Drive.moveToPoint( 0,  -38, 1000, false);
    //not tested 
    Drive.moveToPose(10,-40, 90, 1000, {.forwards = false} );
    //def mot tested
    /*Wings.set_value(true);
    Drive.moveToPoint(-15,-40,1000,false);
    Drive.moveToPoint(-10,-40,1000,true);
    Drive.moveToPoint(-15,-40,1000,false);
    Wings.set_value(false);
    Drive.moveToPoint(-10,-40,1000,true);
    Drive.moveToPose(0,-20,45,1000,{.forwards=true});
    Drive.moveToPose()*/

}

void oldSkillsAuto(){
    DB.move(-20);
    Flystick.move(127);
    pros::delay(500);
    Flystick.brake();
    flywheelPID(1800);
    //pros::delay(48000); // Delay for matchloading
    Drive.moveToPose(-8, -45, 0, 1000, {.forwards = false});
}

void newSkillsAuto(){
    Drive.moveToPose(-54, -28, 90, 1300, {.forwards = false});
}


void printToScreen(){
        lemlib::Pose pose = Drive.getPose(); // get the current position of the robot
        pros::lcd::print(0, "X: %f", pose.x); // print the x position
        pros::lcd::print(1, "Y: %f", pose.y); // print the y position
        pros::lcd::print(2, "Theta: %f", pose.theta); // print the heading
        pros::delay(20);
}

//Create PID objects
//PID Linear(20, 0, 2);
//PID Angular(1, 0, 0);


//Create Chassis object
//Chassis Drive(std::make_unique<pros::MotorGroup>(std::initializer_list<pros::Motor>{LeftBack, LeftHalf, LeftFront}),
//std::make_unique<pros::MotorGroup>(std::initializer_list<pros::Motor>{RightBack, RightHalf, RightFront}),
//Linear, 
//Angular);

/*
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	pros::lcd::initialize();
    Drive.calibrate();
	Gyro.reset(true);
	Flystick.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	Flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	Drive.setPose(0, 0, 0, false);
    
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
	//leftAutonAWP(); //AWP Left Side Auton
    //rightAuton(); //12-15 Point Right Side 
    //mattLeftAuto();
    //oldSkillsAuto();
    


    //ACTUALLY USED
    newSkillsAuto(); //Skills!
    //newLeftAuton();
    //newRightAuton();
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
 
void opcontrol() {
    pros::Task screenPrint2(printToScreen);
    Flystick.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	while (true) {
		//screenPrint;
		driverControl();
		if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			flywheelPID(1700);
		}
		else{
			flywheelPID(0);
		}
		wings();
		flystick();
		intake();
		if(Selector.get_value()){
			//temps;
		}
		if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			Rachet.set_value(true);
		}
        printToScreen();
	}
}