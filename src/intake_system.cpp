#include "main.h" 
// main.h provides extern declarations for:
// pros::Controller controller;
// Intake my_intake;
// Treads my_treads;
// Outtake my_outtake;

void intake_system_control() {
    int power = 100; // Standard power for subsystems

    // --- Intake and Indexing Logic (e.g., R1 Button) ---
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        // R1 is pressed: Bring balls IN
        
        // 1. Intake: Pulls balls into the robot
        my_intake.spinIn(power);
        
        // 2. Treads: Indexes balls up toward the output
        // (Uses spinForward based on your original Treads methods)
        my_treads.spinForward(power); 
        
        // 3. Outtake: Must be stopped or held to prevent premature firing
        my_outtake.stop();
    }
    
    // --- Outtake/Shooting Logic (e.g., L1 Button) ---
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        // R2 is pressed: Shoot balls OUT TOP GOAL
        
        // 1. Intake: Stop the intake, or gently reverse to clear the opening
        my_intake.stop();
        
        // 2. Treads: Pushes balls out of the robot
        my_treads.spinReverse(power); 
        
        // 3. Outtake: Spins out to shoot
        my_outtake.spinOut(power);
    } 

        // --- Outtake/Shooting Logic (e.g., L1 Button) ---
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        // R2 is pressed: Shoot balls OUT TOP GOAL
        
        // 1. Intake: Stop the intake, or gently reverse to clear the opening
        my_intake.spinOut();
        
        // 2. Treads: Pushes balls out of the robot
        my_treads.spinForward(power); 
        
        // 3. Outtake: Spins out to shoot
        my_outtake.stop();
    } 

    // --- Neutral/Stop Logic (No Buttons Pressed) ---
    else {
        // No related button is pressed: Stop all subsystems
        my_intake.stop();
        my_treads.stop();
        my_outtake.stop();
    }
}