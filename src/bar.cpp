#include "bar.hpp"
#include <cmath>

bool is_moving_to_preset = false;

Bar::Bar(pros::Motor& m) : motor_(m) {} // Init logic

void Bar::setTargetDeg(double deg) {
    is_moving_to_preset = true;
    motor_.move_absolute(deg, 100); 
}

void Bar::moveManual(int voltage) {
    is_moving_to_preset = false; 
    motor_.move_voltage(voltage);
}

void Bar::stop() {
    is_moving_to_preset = false;
    motor_.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    motor_.brake();
}

double Bar::getPosition() const {
    return motor_.get_position();
}

void bar_control() {
    // 1. Manual Triggers (Override)
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        my_bar.moveManual(4000);
        
    } 
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        my_bar.moveManual(-4000);
    } 
    
    // 3. Logic to handle "Coasting" to the target
    else {
        // If we aren't currently trying to hit a preset, stop/hold the motor
        my_bar.stop();
    }
}