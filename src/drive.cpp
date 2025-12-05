// src/drive.cpp

// 1. INCLUDE THE GLOBAL HEADER FIRST
#include "main.h" 
#include "drive.hpp" 
#include <array>
#include <cmath> // Include cmath for std::abs() used in deadband

// ----------------------------------------------------------------------
// MecanumDrive Class Definitions (Keep unchanged)
// ----------------------------------------------------------------------

MecanumDrive::MecanumDrive(pros::Motor& fl, pros::Motor& bl, pros::Motor& fr, pros::Motor& br)
  : fl_(fl), bl_(bl), fr_(fr), br_(br) {}

int MecanumDrive::pctToVel(double pct) {
  if (pct > 100.0) pct = 100.0;
  if (pct < -100.0) pct = -100.0;
  // Converts percentage power (-100 to 100) to PROS voltage (-127 to 127)
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
// drive_control() FUNCTION DEFINITION (Tank Drive Logic)
// ----------------------------------------------------------------------

void drive_control() {
    // 1. Read controller inputs for TANK DRIVE:
    // Left Joystick Y (Forward/Backward for Left Side)
    int left_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    // Right Joystick Y (Forward/Backward for Right Side)
    int right_power = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    
    // 2. Deadband (to prevent motor drift)
    const int deadband = 5;
    if (std::abs(left_power) < deadband) {
        left_power = 0;
    }
    if (std::abs(right_power) < deadband) {
        right_power = 0;
    }

    // 3. Apply TANK DRIVE kinematics to the MecanumDrive class.
    // MecanumDrive setPower(fl_pct, bl_pct, fr_pct, br_pct)
    // Note: Mecanum wheels will not strafe in this mode, but will still drive and turn.
    chassis.setPower(
        left_power,   // Front Left
        left_power,   // Back Left
        right_power,  // Front Right
        right_power   // Back Right
    );
}