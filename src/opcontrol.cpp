#include "main.h"

void opcontrol() {
    // The code MUST have a while(true) loop to keep running
    while (true) {
        
        // --- CALL YOUR SUBSYSTEM FUNCTIONS HERE ---
        // Based on your file list, you likely have functions in these files.
        // You must call them inside this loop.
        
        drive_control();   // Call the function from drive.cpp
        intake_system_control(); // Call the function from intake.cpp
        bar_control();     // Call the function from bar.cpp
        
        // --- REQUIRED DELAY ---
        // You must have a delay to let the brain process other background tasks
        pros::delay(20); 
    }
}