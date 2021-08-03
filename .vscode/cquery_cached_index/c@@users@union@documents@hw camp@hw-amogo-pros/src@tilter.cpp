#include "main.h"


const int TILTER_IN   = 20; // Bringing Mogos Up
const int TILTER_OUT  = 230; // Intaking Mogos
const int TILTER_DOWN = 445; // Untipping Mogos


// Driver Control Variables
bool tilter_up = true;
bool is_at_down = false;
int tilter_lock   = 0;
int controller_tilter_timer = 0;

bool is_in = false;
bool is_mid = false;
bool is_down = false;


pros::Motor tilter(15, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);


void set_tilter(int input)  { tilter = input; }

void zero_tilter()    { tilter.tare_position(); }
int  get_tilter()     { return tilter.get_position(); }
int  get_tilter_vel() { return tilter.get_actual_velocity(); }

void
set_tilter_position(int target, int speed) {
  tilter.move_absolute(target, speed);
}


///
// Tilter  Control
//  - we like to use the same functions for autonomous and driver,
//  - so these functions are used for both.
///

// Check if tilter is within a range of target for X amount of time
// or if tilter is at 0 velocity for Y amount of time
bool
timeout(int target, int vel, int current) {
  static int vel_timeout;
  static int small_timeout;

  if (abs(target-current) < 20) {
    small_timeout+=DELAY_TIME;
    if (small_timeout>50) {
      small_timeout = 0;
      vel_timeout = 0;
      return true;
    }
  } else {
    small_timeout = 0;
  }

  if (vel == 0) {
    vel_timeout+=DELAY_TIME;
    if (vel_timeout>250) {
      vel_timeout = 0;
      small_timeout = 0;
      return true;
    }
  } else {
    vel_timeout = 0;
  }

  return false;
}

// Tilter In
void
tilter_in (bool hold) {
  // Run built in PID to bring tilter lift to TILTER_IN
  set_tilter_position(TILTER_IN, 127);
  is_in = timeout(TILTER_IN, get_tilter_vel(), get_tilter());

  // If running during autonomous,
  if (hold) {
    // Set states so the mogo will be in the last position in driver it was in during auto
    tilter_up = true;
    is_at_down = false;
    // Loop if robot isn't there yet
    pros::delay(DELAY_TIME);
    tilter_in(!is_in);
  }
}

// Tilter Down
void
tilter_down(bool hold) {
  // Run built in PID to bring tilter lift to TILTER_DOWN
  set_tilter_position(TILTER_DOWN, 127);
  is_down = timeout(TILTER_DOWN, get_tilter_vel(), get_tilter());

  // If running during autonomous,
  if (hold) {
    // Set states so the mogo will be in the last position in driver it was in during auto
    is_at_down = true;
    // Loop if robot isn't there yet
    pros::delay(DELAY_TIME);
    tilter_down(!is_down);
  }
}

// Tilter Out
void
tilter_out(bool hold) {
  // Run built in PID to bring tilter lift to TILTER_OUT
  set_tilter_position(TILTER_OUT, 127);
  is_mid = timeout(TILTER_OUT, get_tilter_vel(), get_tilter());

  // If running during autonomous,
  if (hold) {
    // Set states so the mogo will be in the last position in driver it was in during auto
    tilter_up = false;
    is_at_down = false;
    // Loop if robot isn't there yet
    pros::delay(DELAY_TIME);
    tilter_out(!is_mid);
  }
}


///
// Driver Control
//  - when L2 is pressed, toggle between in and out.
//  - when L2 is held, bring the tilter all the way down
///
void
tilter_control() {
  // Toggle for tilter
  if (master.get_digital(DIGITAL_L2) && tilter_lock==0) {
    if (is_at_down)
      tilter_up = false;
    else
      tilter_up = !tilter_up;

    is_at_down = false;
    tilter_lock = 1;
  }
  // If button is held, bring tilter all the way down
  else if (master.get_digital(DIGITAL_L2)) {
    controller_tilter_timer+=DELAY_TIME;
    if (controller_tilter_timer>=300)
      is_at_down = true;
  }
  // Reset when button is let go
  else if (!master.get_digital(DIGITAL_L2)) {
    tilter_lock  = 0;
    controller_tilter_timer = 0;
  }

  // Bring tilter to position based on is_at_down and tilter_up
  if (is_at_down)
    tilter_down();
  else if (tilter_up)
    tilter_in();
  else if (!tilter_up)
    tilter_out();
}
