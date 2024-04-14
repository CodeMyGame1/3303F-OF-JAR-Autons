#include "vex.h"

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}

void far_side() {
  motor Intake1 = motor(PORT17, ratio18_1, true); 
  motor Intake2 = motor(PORT4, ratio18_1, false); 
  motor_group Intake (Intake1, Intake2);
  digital_out Hang = digital_out(Brain.ThreeWirePort.H);
  Hang.set(false);
  digital_out Descore = digital_out(Brain.ThreeWirePort.E);
  Descore.set(false);

  Descore.set(true);
  wait(250, msec);
  Descore.set(false);

  Intake.spin(fwd, 100, percent);
  // will we get DQed for crossing central barrier?
  chassis.drive_to_point(60, -12);
  wait(250, msec);
  Intake.stop(hold);

  chassis.drive_to_point(0, 0);

  chassis.turn_to_point(24, 24);
  Intake.spin(rev, 100, percent);
  wait(250, msec);
  Intake.stop(coast);

  chassis.turn_to_point(0, -36);
  Intake.spin(fwd, 100, percent);
  chassis.drive_to_point(0, -36);
  wait(250, msec);
  Intake.stop(coast);

  chassis.drive_to_point(0, 12);

  chassis.turn_to_point(12, 24);
  Descore.set(true);
  chassis.drive_to_point(12, 24);

  // what if wing rips off oopsies
  chassis.turn_to_point(48, 24);
  Descore.set(false);

  // tune error, settle time, and timeout values (last three values) for ALL `drive_to_point` calls with more than 2 params
  chassis.drive_to_point(48, 24, 12, 0, 4, 400, 1000);
  chassis.drive_to_point(24, 24);
  chassis.turn_to_angle(0);
  // will this drive with BACK of bot or just find closest?
  chassis.drive_to_point(48, 24, 12, 0, 4, 400, 1000);

  chassis.drive_to_point(24, 24);
  chassis.turn_to_point(36, -36);
  Intake.spin(fwd, 100, percent);
  // will this go OVER barrier?
  chassis.drive_to_point(36, -36, 12, 0, 4, 400, 1000);
  Intake.stop(coast);

  chassis.turn_to_point(48, 0);
  chassis.drive_to_point(48, 0);
  chassis.turn_to_point(48, 24);
  chassis.drive_to_point(48, 24, 12, 0, 4, 400, 1000);

  chassis.drive_to_point(48, 0);
  chassis.turn_to_point(60, -36);
  Intake.spin(fwd, 100, percent);
  // will this DQ us for crossing central barrier?
  chassis.drive_to_point(60, -36, 12, 0, 4, 400, 1000);
  Intake.stop(coast);
  chassis.turn_to_point(60, 24);
  chassis.drive_to_point(60, 24, 12, 0, 4, 400, 1000);
}