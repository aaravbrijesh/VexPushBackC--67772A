#include "main.h" 
// Includes global object declarations (controller, my_intake, my_treads, my_outtake).

void intake_system_control() {
    int power = 100; // Standard power for subsystems

    // --- JAM DETECTION GUARDS ---
    // Prevents driver control if any subsystem motor is currently executing an automated jam recovery move.
    if (!my_intake.check_motor_status(power)) return;
    if (!my_treads.check_motor_status(power)) return;
    if (!my_outtake.check_motor_status(power)) return;

    // --- Intake and Indexing Logic (R1 Button) ---
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        // R1 is pressed: Commands the system to pull game objects into the robot.
        
        // 1. Intake: Pulls objects in.
        my_intake.spinIn(power);
        
        // 2. Treads: Treads move forward to index objects toward the outtake.
        my_treads.spinForward(power); 
        
        // 3. Outtake: Stops the outtake to stage the game objects.
        my_outtake.stop();
    }
    
    // --- Shooting Logic (R2 Button) ---
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        // R2 is pressed: Commands the system to launch game objects.
        
        // 1. Intake: Stops the intake to prevent interference.
        my_intake.stop();
        
        // 2. Treads: Treads spin in reverse to feed objects into the outtake.
        my_treads.spinReverse(power); 
        
        // 3. Outtake: Outtake spins out to launch the game objects.
        my_outtake.spinOut(power);
    } 

    // --- Secondary Control Logic (L1 Button) ---
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        // L1 is pressed: Commands a gentle outward movement.
        
        // 1. Intake: Spins out to eject objects.
        my_intake.spinOut();
        
        // 2. Treads: Treads move forward.
        my_treads.spinForward(power); 
        
        // 3. Outtake: Outtake stops.
        my_outtake.stop();
    } 

    // --- Neutral/Stop Logic (No Related Buttons Pressed) ---
    else {
        // No related button is pressed: All subsystems stop.
        my_intake.stop();
        my_treads.stop();
        my_outtake.stop();
    }
}