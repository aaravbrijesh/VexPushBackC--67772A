#pragma once
#include "main.h"

// Constants
constexpr int JAM_THRESHOLD_RPM = 5;
constexpr int JAM_TIME_MS = 500;
constexpr double UNJAM_DEGREES = 360.0;

class JamDetector {
public:
    // Constructor takes a reference to the motor it monitors
    JamDetector(pros::Motor& m);

    // Called when the driver presses the button
    void set_commanded_run(int direction); // direction: 1 or -1

    // The main logic. Returns true if motor is fine, false if recovery ran.
    bool check_status();
    
private:
    pros::Motor& motor_;
    int commanded_direction_ = 0;
    uint32_t stuck_time_start_ = 0;
    bool recovery_active_ = false;
};