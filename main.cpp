#include "main.h"

void on_center_button() {

}

void initialize() {
	
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1, 2});    
	pros::MotorGroup right_mg({-3, -4});
	pros::Motor cascade_m({11);


	while (true) {
		//Drivetrain (Arcade Control)
		int dir = master.get_analog(ANALOG_LEFT_Y);    
		int turn = master.get_analog(ANALOG_RIGHT_X);
		
		//Deadband
		const int deadband = 5;
		if (abs(dir) < deadband) dir = 0;
    	if (abs(turn) < deadband) turn = 0;
		
		left_mg.move(dir - turn);                      
		right_mg.move(dir + turn);                     
		pros::delay(20);    
		
		//Cascade
	 	if (master.get_digital(DIGITAL_R1)) {
      	cascade_m.move_velocity(100); //VALUE IS THE MOTOR SPEED
    	}
    	else if (master.get_digital(DIGITAL_R2)) {
      	cascade_m.move_velocity(-100); //VALUE IS THE -MOTOR SPEED
    	}
    	else {
      	cascade_m.move_velocity(0);
    	}
	}
}