#include "bar.hpp"
#include "main.h" // Includes necessary global object declarations
// Includes the header for the PID class.


Bar::Bar(pros::Motor& m)
  : motor_(m),
    pid_(0.6, 0.0, 0.3, "BarPID"),
    target_deg_(0.0),
    pid_active_(false)
{
  // Sets the motor to hold its position when stopped.
  motor_.set_brake_mode(pros::MotorBrake::hold);
  motor_.tare_position(); 
}

void Bar::setTargetDeg(double deg) {
  target_deg_ = deg;
  pid_.setTarget(deg);
  pid_active_ = true;
}

void Bar::updatePID() {
  if (!pid_active_) return;
  double current = motor_.get_position();
  double pwr = pid_.update(current);
  if (pwr > 100.0) pwr = 100.0;
  if (pwr < -100.0) pwr = -100.0;
  motor_.move(static_cast<int>(pwr * 127.0 / 100.0));
}

void Bar::holdPosition() {
  // Sets the current position as the new PID target to maintain the position.
  setTargetDeg(motor_.get_position());
}

void Bar::stop() {
  // Deactivates the PID loop and brakes the motor.
  pid_active_ = false;
  motor_.brake();
}

double Bar::getPosition() const {
  // Returns the motor's absolute position in degrees.
  return motor_.get_position();
}


void bar_control() {
    // Continually update the PID loop to move the bar towards its target
    my_bar.updatePID();

    // Check for button inputs to override or set new targets
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        my_bar.setTargetDeg(300.0); // Example: Lift bar to position 1
    } 
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        my_bar.setTargetDeg(0.0); // Example: Lower bar to position 0
    }
}