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

// Instantiate Right side auton
void rightAuton(){
    Intake.move(127);
    Drive.moveToPoint(0, 6, 800);
    pros::delay(1000);
    Drive.moveToPoint(0, -28, 1000, false, 60); 
    Drive.turnTo(-50, 42, 1000, true, 127);
    Wings.set_value(true);
    Drive.moveToPoint(10.5, -44, 1500, false);
    Drive.turnTo(cos(Drive.getPose().x - 4) * 100, -sin(Drive.getPose().y + 3) * 100, 1000);
    Drive.turnTo(Drive.getPose().x, -sin(Drive.getPose().y - 9) * 100, 1000, false);
    Wings.set_value(false);
    pros::delay(1500);
    LeftDB.move(40);
    pros::delay(300);
    DB.move(-127);
    pros::delay(1200);
    Intake.move(-20);
    pros::delay(500);
    Intake.brake();
}



// Instantiate Left side auton
void leftAuton(){
    
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
	rightAuton();
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