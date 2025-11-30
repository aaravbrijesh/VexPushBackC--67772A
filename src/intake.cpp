#include "intake.hpp"
#include "main.h" // Needed for controller and my_intake externs

Intake::Intake(pros::Motor& m) : motor_(m) {
  motor_.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Intake::spinOut(int pct) {
  motor_.move(static_cast<int>(pct * 127.0 / 100.0));
}

void Intake::spinIn(int pct) {
  motor_.move(static_cast<int>(-pct * 127.0 / 100.0)); // reverse for inward
}

void Intake::moveTurns(double turns, int pct) {
  double deg = turns * 360.0;
  motor_.move_relative(static_cast<int>(pct * 127.0 / 100.0), deg);
}

void Intake::stop() {
  motor_.brake();
}
