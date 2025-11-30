#include "outtake.hpp"
#include "main.h" // Needed for controller and my_outtake externs

Outtake::Outtake(pros::Motor& m) : motor_(m) {
  motor_.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Outtake::spinIn(int pct) {
  motor_.move(static_cast<int>(pct * 127.0 / 100.0));
}

void Outtake::spinOut(int pct) {
  motor_.move(static_cast<int>(-pct * 127.0 / 100.0));
}

void Outtake::moveTurns(double turns, int pct) {
  double deg = turns * 360.0;
  motor_.move_relative(static_cast<int>(pct * 127.0 / 100.0), deg);
}

void Outtake::stop() {
  motor_.brake();
}
