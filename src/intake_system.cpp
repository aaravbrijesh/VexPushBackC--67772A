#include "main.h" 


void intake_system_control() {
    int power = 100; // Standard power for subsystems


    // --- Intake and Indexing Logic (R1 Button) ---
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    
        my_intake.spinOut(power);
        
        long_outtake.spinIn();

        upper_outtake.spinIn();
    }
    
    // --- Shooting Logic (R2 Button) ---
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        // R2 is pressed: Commands the system to launch game objects.
        
        // 1. Intake: Spins out to score
        my_intake.spinIn();
        

        

        long_outtake.spinOut(power);
        upper_outtake.spinOut(power);
    } 

    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        // L2 is pressed: Commands a gentle inward movement.
        
        // 1. Intake: Spins in to collect objects.
        my_intake.spinOut();
        
        // 2. Long Outtake: Spins in to assist intake.
        long_outtake.stop();
        
        // 3. Upper Outtake: Stops to prevent jamming.
        upper_outtake.stop();
    }

    // --- Secondary Control Logic (L1 Button) ---
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        // L1 is pressed: Commands a gentle outward movement.
        
        // 1. Intake: Spins out to eject objects.
        my_intake.spinIn();
        
        // 3. Outtake: Outtake stops.
        long_outtake.spinIn();
        upper_outtake.spinOut();
    } 

    // --- Neutral/Stop Logic (No Related Buttons Pressed) ---
    else {
        // No related button is pressed: All subsystems stop.
        my_intake.stop();
        long_outtake.stop();
        upper_outtake.stop();
    }
}