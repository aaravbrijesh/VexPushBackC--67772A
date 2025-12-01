#include "main.h"
#include "robot.hpp"
#include "auton.hpp" 

// callback from sample
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}

void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello PROS User!");
  pros::lcd::register_btn1_cb(on_center_button);

  Robot::init();
}

void disabled() {}

void competition_initialize() {}

// PROS 4 automatically finds this function. 
// We call the specific routine from our auton namespace.
void autonomous() {
  Auton::myAuton();
}

// Note: opcontrol() is likely defined in src/opcontrol.cpp. 
// PROS will find it there automatically.