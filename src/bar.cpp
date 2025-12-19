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
    motor_.move(voltage);
}

void Bar::stop() {
    is_moving_to_preset = false;
    motor_.brake();
}

double Bar::getPosition() const {
    return motor_.get_position();
}

void bar_control() {
    // 1. Manual Triggers (Override)
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        my_bar.moveManual(100);
    } 
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        my_bar.moveManual(-100);
    } 
    
    // 3. Logic to handle "Coasting" to the target
    else {
        // If we aren't currently trying to hit a preset, stop/hold the motor
        if (!is_moving_to_preset) {
            my_bar.stop();
        } 
        // If we are hitting a preset, check if the motor speed has dropped to ~0
        else if (std::abs(bar_motor.get_actual_velocity()) < 2) {
            is_moving_to_preset = false; 
        }
    }
}