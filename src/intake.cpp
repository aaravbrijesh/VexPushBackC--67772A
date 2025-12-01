#include "intake.hpp"
#include "main.h" 
#include <cmath> // For std::fabs()

// --- CONSTANTS ---
constexpr int JAM_THRESHOLD_RPM = 5;      // Motor speed below this RPM is considered stuck.
constexpr int JAM_TIME_MS = 500;          // Time (in ms) motor must be stuck before recovery is triggered.
constexpr double UNJAM_DEGREES = 360.0;   // The distance (in degrees) the motor runs backward to clear the jam.
// -----------------

Intake::Intake(pros::Motor& m) : motor_(m) {
  motor_.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Intake::spinOut(int pct) {
  motor_.move(static_cast<int>(pct * 127.0 / 100.0));
  commanded_direction_ = 1; // Motor is commanded to spin out (forward).
}

void Intake::spinIn(int pct) {
  motor_.move(static_cast<int>(-pct * 127.0 / 100.0)); 
  commanded_direction_ = -1; // Motor is commanded to spin in (reverse).
}

void Intake::moveTurns(double turns, int pct) {
  double deg = turns * 360.0;
  motor_.move_relative(static_cast<int>(pct * 127.0 / 100.0), deg);
  commanded_direction_ = 0; // Position control mode does not require active direction tracking.
}

void Intake::stop() {
  motor_.brake();
  // Reset all jam detection state variables upon stopping.
  commanded_direction_ = 0; 
  stuck_time_start_ = 0;
  is_recovery_active_ = false;
}

bool Intake::check_motor_status(int commanded_power) {
    
    // 1. Recovery Check: If actively reversing, block new commands until the move is complete.
    if (is_recovery_active_) {
        // Checks if the motor's move_relative command has finished.
        if (motor_.get_target_velocity() == 0) { 
            is_recovery_active_ = false; // Recovery move finished.
        }
        return false; // Blocks control flow while recovery is active.
    }
    
    // 2. Skip monitoring if the motor isn't commanded to run by the driver.
    if (commanded_direction_ == 0) return true;

    // 3. Jam Detection: Check the actual motor speed.
    double current_rpm = std::fabs(motor_.get_actual_velocity());

    if (current_rpm < JAM_THRESHOLD_RPM) {
        // Start the jam timer if low RPM is detected for the first time.
        if (stuck_time_start_ == 0) {
            stuck_time_start_ = pros::millis();
        } 
        // Triggers recovery if the low RPM condition has persisted beyond the time limit.
        else if (pros::millis() - stuck_time_start_ > JAM_TIME_MS) {
            
            // Jam detected: Initiates a reverse spin to clear the jam.
            is_recovery_active_ = true;
            double speed = static_cast<int>(commanded_power * 127.0 / 100.0);
            
            // Commands the motor to run backward for a set distance at the commanded speed.
            motor_.move_relative(UNJAM_DEGREES * -commanded_direction_, speed);
            return false; // Blocks driver control during the recovery process.
        }
    } else {
        // Motor is running normally, reset the jam timer.
        stuck_time_start_ = 0;
    }

    return true; // Motor is running normally, allows control flow.
}