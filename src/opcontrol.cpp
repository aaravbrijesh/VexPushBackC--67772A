#include "main.h"

void opcontrol() {
    // The main loop for operator control, runs continuously.
    while (true) {
        
        // --- SUBSYSTEM CONTROL CALLS ---
        
        drive_control();   // Updates the drive train based on controller input.
        intake_system_control(); // Updates the intake/indexing system.
        bar_control();     // Updates the bar subsystem (includes PID control).
        jam_control();   // Monitors and recovers from jams in various subsystems.
        
        // --- LOOP DELAY ---
        // Required delay to prevent hogging system resources and allow background tasks.
        pros::delay(20); 
    }
}