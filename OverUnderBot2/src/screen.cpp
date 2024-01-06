#include "api.h"
#include "Objects.h"
#include "Chassis.h"

void printToScreen(){
	while(true){
		pros::lcd::print(0, "Heading: %d", Gyro.get_heading());
	}
}


//Print motor temperatures for convinience
void printTemp(){
	while(true){
		double leftDrive = 0;
		double rightDrive = 0;
		const double DENOM = 3;
	//Left Drive Temp Avg
		for(double d : LeftDB.get_temperatures()){
			leftDrive += d;
		}
		pros::lcd::print(0, "LeftDrive Temp: %d", (leftDrive / DENOM));
	//Right Drive Temp Avg
		for(double d : LeftDB.get_temperatures()){
			rightDrive += d;
		}
		pros::lcd::print(1, "RightDrive Temp: %d", (rightDrive / DENOM));
	//Other Motor Temps
		pros::lcd::print(2, "Flystick Temp: %d", Flystick.get_temperature());
		pros::lcd::print(3, "Flywheel Temp: %d", Flywheel.get_temperature());
		pros::lcd::print(4, "Intake Temp: %d", Intake.get_temperature());
	}
}