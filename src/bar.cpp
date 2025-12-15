#include "bar.hpp"
#include "main.h" 

Bar::Bar(pros::Motor& m)
  : motor_(m),

    pid_(0.4, 0.0, 1.0, "BarPID"), 
    target_deg_(0.0),
    pid_active_(false)
{
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

  // Feed-Forward (FF) remains the same or slightly increased if needed for smooth descent
  if (target_deg_ < current) {
      // Keep this value high enough to smoothly drop against gravity, e.g., -25.0
      pwr += -25.0; 
  }
  
  if (pwr > 100.0) pwr = 100.0;
  if (pwr < -100.0) pwr = -100.0;
  
  motor_.move(static_cast<int>(pwr * 127.0 / 100.0));
}

void Bar::holdPosition() {
  setTargetDeg(motor_.get_position());
}

void Bar::stop() {
  pid_active_ = false;
  motor_.brake();
}

double Bar::getPosition() const {
  return motor_.get_position();
}


void bar_control() {
    my_bar.updatePID();

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        my_bar.setTargetDeg(500.0); 
    } 
    
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        my_bar.setTargetDeg(-500.0); 
    }

    else {
        my_bar.holdPosition();
    }
}