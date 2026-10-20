#include "main.h"

void on_center_button() {}

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1, 2});    
	pros::MotorGroup right_mg({-3, -4});
	pros::MotorGroup cascade_m({11, 12});
	pros::Motor claw_m(20);

	while (true) {
		//Drivetrain
		int dir = master.get_analog(ANALOG_LEFT_Y);    
		int turn = master.get_analog(ANALOG_RIGHT_X);

		const int deadband = 30;
		if (abs(dir) < deadband) dir = 0;
    	if (abs(turn) < deadband) turn = 0;
		left_mg.move(dir - turn);                      
		right_mg.move(3 * (dir + turn));                     
		
		//Cascade
		if (master.get_digital(DIGITAL_R1)) {
      		cascade_m.move_velocity(100);
    	}
    	else if (master.get_digital(DIGITAL_R2)) {
      		cascade_m.move_velocity(-100);
    	}
    	else {
      		cascade_m.move_velocity(0);
    	}

		//Claw
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			claw_m.move(50);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			claw_m.move(-50);
		}
		else {
			claw_m.move(0);
		}

		pros::delay(20);    
	}
}
