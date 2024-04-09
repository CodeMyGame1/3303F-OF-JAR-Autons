#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

// left motor definitions -- NOTE THAT THESE DEFINITIONS ASSUME THE INTAKE IS THE FRONT OF THE ROBOT!
motor left_back_motor = motor(PORT20, ratio6_1, false);
motor left_front_middle_motor = motor(PORT18, ratio6_1, true);
motor left_back_middle_motor = motor(PORT19, ratio6_1, false);
motor left_front_motor = motor(PORT5, ratio6_1, false);

// right motor definitions -- NOTE THAT THESE DEFINITIONS ASSUME THE INTAKE IS THE FRONT OF THE ROBOT!

motor right_back_motor = motor(PORT13, ratio6_1, false);
motor right_back_middle_motor = motor(PORT12, ratio6_1, true);
motor right_front_middle_motor = motor(PORT11, ratio6_1, false);
motor right_front_motor = motor(PORT3, ratio6_1, false);

//IMU definition

inertial imu = inertial(PORT2);

Drive chassis(

//Specify your drive setup below. There are seven options:
//ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
//For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
ZERO_TRACKER_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(
  left_back_motor
	, left_back_middle_motor
	, left_front_middle_motor
	, left_front_motor
),

//Right Motors:
motor_group(
  right_back_motor
	, right_back_middle_motor
	, right_front_middle_motor
	, right_front_motor
),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT2,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
2.75,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
1,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);

    digital_out Hang = digital_out(Brain.ThreeWirePort.H);
    Hang.set(false);
    digital_out Descore = digital_out(Brain.ThreeWirePort.E);
    Descore.set(false);


//Dont use this gooffy ah auto selecter. just print the funtion down hear or make a new one. kinda funky lookin


  }


void autonomous(void) {

    motor Intake1 = motor(PORT17, ratio18_1, true); 
    motor Intake2 = motor(PORT4, ratio18_1, false); 
    motor_group Intake (Intake1, Intake2);
    digital_out Hang = digital_out(Brain.ThreeWirePort.H);
    Hang.set(false);
    digital_out Descore = digital_out(Brain.ThreeWirePort.E);
    Descore.set(false);
    //You Kinda need all this. Just Copy and paste them into each of  the auton functions.
 
//Print the funtion here....


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


 controller Controller1 = controller(primary);
      
   
    bool RemoteControlCodeEnabled = true;

void usercontrol(void) {

  while (1) {
 
    chassis.control_arcade();

    wait(20, msec); 

    motor Intake1 = motor(PORT17, ratio18_1, true); 
    motor Intake2 = motor(PORT4, ratio18_1, false); 
    motor_group Intake (Intake1, Intake2);
    Intake.setVelocity(100,percent);
    void Ctier();


 if (Controller1.ButtonR1.pressing()) {
        Intake.spin(fwd);
       
      } else if (Controller1.ButtonR2.pressing()) {
        Intake.spin(reverse);
        
      } else {
      Intake.stop();
      }
  

  Controller1.ButtonB.pressed(Ctier);


   









  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
