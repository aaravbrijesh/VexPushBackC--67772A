#include "outtake.hpp"
#include "main.h" 
#include <cmath> // For std::fabs()

// --- CONSTANTS ---
constexpr int JAM_THRESHOLD_RPM = 5;      // Motor speed below this RPM is considered stuck.
constexpr int JAM_TIME_MS = 500;          // Time (in ms) motor must be stuck before recovery is triggered.
constexpr double UNJAM_DEGREES = 360.0;   // The distance (in degrees) the motor runs backward to clear the jam.
// -----------------


Outtake::Outtake(pros::Motor& m) : motor_(m) {
  motor_.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Outtake::spinIn(int pct) {
  motor_.move(static_cast<int>(pct * 127.0 / 100.0));
  commanded_direction_ = 1; // Motor is commanded to spin in (forward).
}

void Outtake::spinOut(int pct) {
  motor_.move(static_cast<int>(-pct * 127.0 / 100.0));
  commanded_direction_ = -1; // Motor is commanded to spin out (reverse).
}

void Outtake::moveTurns(double turns, int pct) {
  double deg = turns * 360.0;
  motor_.move_relative(static_cast<int>(pct * 127.0 / 100.0), deg);
  commanded_direction_ = 0; // Position control mode does not require active direction tracking.
}

void Outtake::stop() {
  motor_.brake();
  // Reset all jam detection state variables upon stopping.
  commanded_direction_ = 0; 
  stuck_time_start_ = 0;
  is_recovery_active_ = false;
}



