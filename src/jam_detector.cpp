#include "jam_detector.hpp" 
#include "main.h"      
#include <cmath>       // Access to std::fabs (Absolute Value)

// Assuming these constants and variables are defined in jam_detector.hpp:
/* // CONSTANTS (If defined here instead of .hpp)
constexpr int JAM_THRESHOLD_RPM = 5;
constexpr int JAM_TIME_MS = 500;
constexpr double UNJAM_DEGREES = 360.0;
*/

// Constructor: Connects this Detector to a specific motor.
JamDetector::JamDetector(pros::Motor& m) : motor_(m) {}

// Step 1: Tell the detector which way the motor SHOULD be moving.
void JamDetector::set_commanded_run(int direction) {
    commanded_direction_ = direction;
    if (direction == 0) {
        stuck_time_start_ = 0; // Reset timer if the motor is stopped.
    }
}

// Step 2: The Core Logic. Runs every 20ms.
bool JamDetector::check_status() {
    // 1. If we are in recovery, check if the motor finished moving 360 degrees.
    if (recovery_active_) {
        // FIX: Replaced motor_.is_stopped() with the correct PROS check for move_relative completion.
        if (motor_.get_target_velocity() == 0) { 
            recovery_active_ = false; // Recovery is over.
        }
        return false; // BLOCK new commands while recovering.
    }
    
    // 2. Skip if the driver isn't pressing the button.
    if (commanded_direction_ == 0) return true;

    // 3. Check for the JAM.
    double current_rpm = std::fabs(motor_.get_actual_velocity());

    if (current_rpm < JAM_THRESHOLD_RPM) {
        // Start the timer if it hasn't started yet.
        if (stuck_time_start_ == 0) {
            stuck_time_start_ = pros::millis();
        } 
        // If the motor has been stuck for too long (500ms):
        else if (pros::millis() - stuck_time_start_ > JAM_TIME_MS) {
            // --- JAM DETECTED! ---
            recovery_active_ = true;
            // Move motor backwards (opposite of commanded direction)
            // Assuming 100% power is correct for recovery
            motor_.move_relative(UNJAM_DEGREES * -commanded_direction_, 100);
            return false; // Block control.
        }
    } else {
        // Motor is fine, reset the jam timer.
        stuck_time_start_ = 0;
    }

    return true; // Motor is running normally.
}