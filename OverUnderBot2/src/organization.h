#include "lemlib/api.hpp"

//Used soley to declare functions so main file is more organized

//Driver control methods

void driverControl();

void wings();

void flystick();

void intake();

void printTemp();


//Declare Flywheel PID

void flywheelPID(double speed);

void flywheelTask();

//Declare Autons

void rightAuton();

void leftAuton();


//Information printing methods

void printToScreen();

void printTemp();