#include "treads.hpp"
#include "main.h" // Needed for the 'controller' and 'my_treads' externs

// ----------------------------------------------------------------------
// Treads Class Definition (Your original methods retained)
// ----------------------------------------------------------------------

Treads::Treads(pros::Motor& m) : motor_(m) {
  motor_.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Treads::spinForward(int pct) {
  motor_.move(static_cast<int>(pct * 127.0 / 100.0));
}

void Treads::spinReverse(int pct) {
  motor_.move(static_cast<int>(-pct * 127.0 / 100.0));
}

void Treads::stop() {
  motor_.brake();
}

// ----------------------------------------------------------------------
// Treads Control Function (CRITICAL FIX for the linker error)
// ----------------------------------------------------------------------

void treads_control() {

}