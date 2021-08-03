#include "main.h"


const int DRIVE_SPEED = 110;
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;


///
// TiP Autons
///

void
solo_awp() {
  // Drive into mogo on platform
  set_drive_pid(drive, -24, 80, true);
  wait_drive();

  // Run the conveyor to score rings in 1pt bucket
  set_conveyor(127);
  pros::delay(300);
  set_conveyor(0);

  // Drive back a little
  set_drive_pid(drive, 2, DRIVE_SPEED);
  wait_drive();

  // Swing turn out of the goal
  set_drive_pid(l_swing, 90, TURN_SPEED);
  wait_drive();

  // Drive into the field a bit
  set_drive_pid(drive, 13.5, DRIVE_SPEED, true);
  wait_drive();

  // Turn to aim for second mogo
  set_drive_pid(turn, 0, TURN_SPEED);
  wait_drive();

  // Drive towards second mogo
  set_drive_pid(drive, -90, DRIVE_SPEED, true);
  wait_until(-24);
  mogo_out(true);
  wait_drive();

  // Swing to angle towards the goal
  set_drive_pid(l_swing, -8, SWING_SPEED);
  wait_drive();

  // Drive into the goal
  set_drive_pid(drive, -12, SWING_SPEED);
  wait_drive();
  mogo_in(true);

  // Run conveyor to score rings onto goal
  // Swing for a better starting position in driver
  set_drive_pid(r_swing, 45, SWING_SPEED);
  set_conveyor(127);
  pros::delay(3000);
  set_conveyor(0);
  wait_drive();
}







///
// Constants
///

// Reset all constants to default
void
reset_constants() {
  reset_slew_min_power();
  reset_slew_distance();
  reset_fw_drive_constants();
  reset_bw_drive_constants();
  reset_turn_constants();
  reset_turn_i_constants();
  reset_swing_constants();
}

// Functions to change constants
/*
void
one_mogo_constants() {
  set_slew_min_power(80, 80);
  set_slew_distance(7, 7);
  set_fw_drive_constants(0.45, 5);
  set_bw_drive_constants(0.375, 4);
  set_turn_constants(5, 0.003, 35);
  set_turn_i_constants(15, 30);
  set_swing_constants(12, 35);
}

void
two_mogo_constants() {
  set_slew_min_power(80, 80);
  set_slew_distance(7, 7);
  set_fw_drive_constants(0.45, 5);
  set_bw_drive_constants(0.375, 4);
  set_turn_constants(5, 0.003, 35);
  set_turn_i_constants(15, 30);
  set_swing_constants(12, 35);
}
*/



// All drive movements use the "set_drive_pid" function
// the first parameter is the type of motion (drive, turn, r_swing, l_swing)
// below are example codes using each type


///
// Drive Example
///
void
auto_1() {
  // The second parameter is target inches
  // The third parameter is max speed the robot will drive at
  // The fourth parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_drive();

  set_drive_pid(drive, -12, DRIVE_SPEED);
  wait_drive();

  set_drive_pid(drive, -12, DRIVE_SPEED);
  wait_drive();
}



///
// Turn Example
///
void
auto_2() {
  // The second parameter is target degrees
  // The third parameter is max speed the robot will drive at


  set_drive_pid(turn, 90, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, 45, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, 0, TURN_SPEED);
  wait_drive();
}



///
// Combining Turn + Drive
///
void
auto_3() {
  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_drive();

  set_drive_pid(turn, 45, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, -45, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, 0, TURN_SPEED);
  wait_drive();

  set_drive_pid(drive, -24, DRIVE_SPEED, true);
  wait_drive();
}



///
// Wait Until
///
void
auto_4() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 12 inches, the intakes will spin until the robot has traveled 24 inches
  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_until(12);
  //set_intake(127); // Commented because no intake function in this code
  wait_drive();
  //set_intake(0); // Commented because no intake function in this code

  set_drive_pid(turn, 45, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, -45, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, 0, TURN_SPEED);
  wait_drive();

  // When the robot gets to -12 inches, the intakes will spin until the robot has traveled -24 inches
  set_drive_pid(drive, -24, DRIVE_SPEED, true);
  wait_until(-12);
  //set_intake(127); // Commented because no intake function in this code
  wait_drive();
  //set_intake(0); // Commented because no intake function in this code
}



///
// Swing Example
///
void
auto_5() {
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  set_drive_pid(l_swing, 45, SWING_SPEED);
  wait_drive();

  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_until(12);

  set_drive_pid(r_swing, 0, SWING_SPEED);
  wait_drive();
}



///
// Auto that tests everything
///
void
test_auton() {
  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_drive();

  set_drive_pid(turn, 45, TURN_SPEED);
  wait_drive();

  set_drive_pid(r_swing, -45, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, 0, TURN_SPEED);
  wait_drive();

  set_drive_pid(drive, -24, DRIVE_SPEED, true);
  wait_drive();
}



void
auto_6() {

}



void
auto_7() {

}



void
auto_8() {

}



void
auto_9() {

}



void
auto_10() {

}
