#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup left_mg({1, 2});    
pros::MotorGroup right_mg({-3, -4});
pros::Motor cascade_m1(11);
pros::Motor cascade_m2(12);
pros::Motor claw_m(15);
pros::Distance sensor(16);
pros::Motor toggle(18);
pros::Motor intake_m1(19);
pros::Motor intake_m2(20);

void on_center_button() {}

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    bool isBlueTeam = true;
    //true is blue  - santhosh radhakrishnan
    while (sensor.get() > 150.0) {
        left_mg.move(-80);
        right_mg.move(-80);

        pros::delay(20);
    }

    left_mg.move(0);
    right_mg.move(0);

    pros::delay(200);

    if (isBlueTeam) {
        toggle.move(127);
    } else {
        toggle.move(-127);
    }

    pros::delay(500);

    toggle.move(0);

    pros::delay(20);
}

void opcontrol() {    
	bool clawRunning = false;

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
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      		cascade_m1.move(127);
            cascade_m2.move(127);
    	}
    	else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			cascade_m1.move(-127);
            cascade_m2.move(-127);
    	}
    	else {
      		cascade_m1.move(0);
            cascade_m2.move(0);
    	}

		//Claw
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) &&
            !master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            claw_m.move(127);
        }

        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) &&
                 !master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            claw_m.move(-127);
        }

        else {
            claw_m.move(0);
        }

		//Intake
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            clawRunning = !clawRunning;
        }
        if (clawRunning) {
            intake_m1.move(-127);
            intake_m2.move(127);
        } else {
            intake_m1.move(0);
            intake_m2.move(0);
        }
		pros::delay(20);  
	}
}
