#include "main.h"
#include "robot.hpp"
#include "auton.hpp" 

// Callback function for the center button press on the V5 screen.
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

// Called by the PROS kernel at the start of the autonomous period.
void autonomous() {
  // Executes the selected autonomous routine.
  Auton::myAuton();
}

// The operator control function is defined in 'src/opcontrol.cpp'.