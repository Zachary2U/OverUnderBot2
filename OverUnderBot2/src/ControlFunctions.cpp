//Declare methods
#include "Objects.h"

void driverControl(){
	double power = Master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	double turn = Master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

	LeftDB.move(power + turn);
	RightDB.move(power - turn);
}

void intake(){
	if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
		Intake.move(127);
	}
	else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
		Intake.move(-127);
	}
	else{
		Intake.brake();
	}
}

void wings(){
	if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			Wings.set_value(false);
		}
	else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			Wings.set_value(true);
		}
}

void flystick(){
	if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
		Flystick.move(127);
	}
	else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
		Flystick.move(-127);
	}
	else{
		Flystick.brake();
	}
}


//PID loop for flywheel

void flywheelPID(double speed){
	double volts = 100;
	Flywheel.move(volts);
	if(Flywheel.get_actual_velocity() * 72/12 < speed - 100){
		volts += 0.1;
	}
	else if(Flywheel.get_actual_velocity() * 72/12 > speed + 100){
		volts += 0.1;
	}
}

void flywheelTask(){
	flywheelPID(2000);
}