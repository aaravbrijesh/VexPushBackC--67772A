#include "outtake.hpp"
#include "main.h" 
#include <cmath> // For std::fabs()

// --- CONSTANTS ---
constexpr int JAM_THRESHOLD_RPM = 5;      // Motor speed below this RPM is considered stuck
constexpr int JAM_TIME_MS = 500;          // Time (in ms) motor must be stuck before recovery is triggered
constexpr double UNJAM_DEGREES = 360.0;   // The distance (in degrees) the motor runs backward to clear the jam
// -----------------


Outtake::Outtake(pros::Motor& m) : motor_(m) {
  motor_.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Outtake::spinIn(int pct) {
  motor_.move(static_cast<int>(pct * 127.0 / 100.0));
  commanded_direction_ = 1; // Motor is commanded to spin in
}

void Outtake::spinOut(int pct) {
  motor_.move(static_cast<int>(-pct * 127.0 / 100.0));
  commanded_direction_ = -1; // Motor is commanded to spin out
}

void Outtake::moveTurns(double turns, int pct) {
  double deg = turns * 360.0;
  motor_.move_relative(static_cast<int>(pct * 127.0 / 100.0), deg);
  commanded_direction_ = 0; // move_relative manages position autonomously
}

void Outtake::stop() {
  motor_.brake();
  // Reset all state variables when the motor is manually stopped
  commanded_direction_ = 0; 
  stuck_time_start_ = 0;
  is_recovery_active_ = false;
}

bool Outtake::check_motor_status(int commanded_power) {
    
    // 1. Recovery Check: If actively reversing, block new commands until it stops.
    if (is_recovery_active_) {
        // FIX: Check if the motor's target velocity has been set to 0 (meaning move_relative finished)
        if (motor_.get_target_velocity() == 0) { 
            is_recovery_active_ = false; // Recovery move finished
        }
        return false; // Block new commands while recovery is active
    }
    
    // 2. Skip if the motor isn't commanded to run by the driver.
    if (commanded_direction_ == 0) return true;

    // 3. Jam Detection (check the actual speed)
    double current_rpm = std::fabs(motor_.get_actual_velocity());

    if (current_rpm < JAM_THRESHOLD_RPM) {
        // Start the jam timer if low RPM is detected for the first time
        if (stuck_time_start_ == 0) {
            stuck_time_start_ = pros::millis();
        } 
        // Trigger recovery if motor has been stuck for long enough (500ms)
        else if (pros::millis() - stuck_time_start_ > JAM_TIME_MS) {
            
            // JAM DETECTED: Initiate reverse spin
            is_recovery_active_ = true;
            double speed = static_cast<int>(commanded_power * 127.0 / 100.0);
            
            // Run UNJAM_DEGREES (360) in the opposite direction
            motor_.move_relative(UNJAM_DEGREES * -commanded_direction_, speed);
            return false; // Return false to pause the control loop
        }
    } else {
        // Motor is running normally, reset the jam timer
        stuck_time_start_ = 0;
    }

    return true; // Motor is running normally, allow control flow
}