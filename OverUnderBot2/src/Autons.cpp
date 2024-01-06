#include "Chassis.h"
#include "organization.h"

//PID's
PID angularPID(0, 0, 0);
PID linearPID(0, 0, 0);

//Unique Pointers

Chassis drive = Chassis(
    std::make_unique<pros::MotorGroup>(std::initializer_list<pros::Motor>({LeftBack, LeftHalf, LeftFront})), 
    std::make_unique<pros::MotorGroup>(std::initializer_list<pros::Motor>({RightBack, RightHalf, RightFront})), 
    linearPID, 
    angularPID
    );

// Instantiate Right side auton
void rightAuton(){

}



// Instantiate Left side auton
void leftAuton(){

}