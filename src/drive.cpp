// src/drive.cpp

// Includes global declarations and PROS API headers
#include "main.h" 
#include "drive.hpp" 
#include <array>

// ----------------------------------------------------------------------
// MecanumDrive Class Implementations
// ----------------------------------------------------------------------

MecanumDrive::MecanumDrive(pros::Motor& fl, pros::Motor& bl, pros::Motor& fr, pros::Motor& br)
  : fl_(fl), bl_(bl), fr_(fr), br_(br) {}

// Converts a percentage power (-100 to 100) to PROS voltage units (-127 to 127).
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
// Drive Control Function (Operator Control)
// ----------------------------------------------------------------------

// Controls the Mecanum drive using the global 'chassis' object.
void drive_control() {
    // Read controller inputs
    // Left Joystick Y (Forward/Backward power)
    int forward_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    // Right Joystick X (Turning power)
    int turn_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    // Left Joystick X (Strafe power)
    int strafe_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

    // Apply standard Mecanum kinematics
    // Front Left = Forward + Turn + Strafe
    // Front Right = Forward - Turn - Strafe
    // Back Left = Forward + Turn - Strafe
    // Back Right = Forward - Turn + Strafe
    
    // Note: Sign conventions for Strafe/Turn may need adjustment based on motor wiring.

    chassis.setPower(
        forward_power + turn_power + strafe_power,  // Front Left
        forward_power + turn_power - strafe_power,  // Back Left
        forward_power - turn_power - strafe_power,  // Front Right
        forward_power - turn_power + strafe_power   // Back Right
    );
}