// src/drive.cpp

// 1. INCLUDE THE GLOBAL HEADER FIRST
#include "main.h" 
#include "drive.hpp" 
#include <array>

// ----------------------------------------------------------------------
// MecanumDrive Class Definitions (OK - DO NOT CHANGE THESE)
// ----------------------------------------------------------------------

MecanumDrive::MecanumDrive(pros::Motor& fl, pros::Motor& bl, pros::Motor& fr, pros::Motor& br)
  : fl_(fl), bl_(bl), fr_(fr), br_(br) {}

int MecanumDrive::pctToVel(double pct) {
  if (pct > 100.0) pct = 100.0;
  if (pct < -100.0) pct = -100.0;
  return static_cast<int>(pct * 127.0 / 100.0);
}

void MecanumDrive::setPower(double fl_pct, double bl_pct, double fr_pct, double br_pct) {
  fl_.move(pctToVel(fl_pct));
  bl_.move(pctToVel(bl_pct));
  fr_.move(pctToVel(fr_pct));
  br_.move(pctToVel(br_pct));
}

void MecanumDrive::stop() {
  fl_.brake();
  bl_.brake();
  fr_.brake();
  br_.brake();
}

double MecanumDrive::averagePositionDeg() {
  double sum = fl_.get_position() + bl_.get_position() + fr_.get_position() + br_.get_position();
  return sum / 4.0;
}

void MecanumDrive::resetEncoders() {
  fl_.set_zero_position(0);
  bl_.set_zero_position(0);
  fr_.set_zero_position(0);
  br_.set_zero_position(0);
}


// ----------------------------------------------------------------------
// drive_control() FUNCTION DEFINITION (The Logic Fix)
// ----------------------------------------------------------------------

// You MUST use the MecanumDrive class logic here for a Mecanum robot.
// Assuming you have a global MecanumDrive object named 'chassis' defined in src/robot.cpp

void drive_control() {
    // Read controller inputs
    // Left Joystick Y (Forward/Backward)
    int forward_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    // Right Joystick X (Turning)
    int turn_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    // Left Joystick X (Strafe)
    int strafe_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

    // Apply standard Mecanum kinematics
    // Front Left = Forward + Turn + Strafe
    // Front Right = Forward - Turn - Strafe
    // Back Left = Forward + Turn - Strafe
    // Back Right = Forward - Turn + Strafe
    
    // Note: The sign of Strafe/Turn may need to be flipped based on robot orientation/wiring

    chassis.setPower(
        forward_power + turn_power + strafe_power,  // Front Left
        forward_power + turn_power - strafe_power,  // Back Left (Assuming this is back left)
        forward_power - turn_power - strafe_power,  // Front Right
        forward_power - turn_power + strafe_power   // Back Right (Assuming this is back right)
    );
}