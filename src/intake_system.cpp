#include "main.h" 
// main.h provides extern declarations for:
// pros::Controller controller;
// Intake my_intake;
// Treads my_treads;
// Outtake my_outtake;

void intake_system_control() {
    int power = 100; // Standard power for subsystems

    // --- JAM DETECTION GUARDS (CRITICAL) ---
    // If any motor is currently running a reverse-spin recovery move (returns false), 
    // the 'return' skips all driver commands for this 20ms cycle, allowing the jam 
    // to clear without interference.
    if (!my_intake.check_motor_status(power)) return;
    if (!my_treads.check_motor_status(power)) return;
    if (!my_outtake.check_motor_status(power)) return;

    // --- Intake and Indexing Logic (e.g., R1 Button) ---
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        // R1 is pressed: Bring balls IN
        
        // 1. Intake: Pulls balls into the robot
        my_intake.spinIn(power);
        
        // 2. Treads: Indexes balls up toward the output
        my_treads.spinForward(power); 
        
        // 3. Outtake: Must be stopped or held to prevent premature firing
        my_outtake.stop();
    }
    
    // --- Shooting Logic (e.g., R2 Button) ---
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        // R2 is pressed: Shoot balls OUT TOP GOAL
        
        // 1. Intake: Stop the intake, or gently reverse to clear the opening
        my_intake.stop();
        
        // 2. Treads: Pushes balls out of the robot
        my_treads.spinReverse(power); 
        
        // 3. Outtake: Spins out to shoot
        my_outtake.spinOut(power);
    } 

    // --- Secondary Intake/Outtake Logic (e.g., L1 Button) ---
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        // L1 is pressed: Example logic (Intake out, Treads forward, Outtake stop)
        
        // 1. Intake: Ejects object gently
        my_intake.spinOut();
        
        // 2. Treads: Pushes balls out of the robot
        my_treads.spinForward(power); 
        
        // 3. Outtake: Must be stopped
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