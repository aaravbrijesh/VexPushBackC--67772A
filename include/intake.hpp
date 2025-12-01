#pragma once
#include "main.h"

class Intake {
public:
  Intake(pros::Motor& m);
  void spinOut(int pct = 100);
  void spinIn(int pct = 100);
  void moveTurns(double turns, int pct = 100);
  void stop();
  
  // Checks the motor's RPM to detect a jam. 
  // Returns false if a recovery move is running, true otherwise.
  bool check_motor_status(int commanded_power); 
private:
  pros::Motor& motor_;
  
  // State variables for Jam Detection
  int commanded_direction_ = 0;   // Stores the direction the driver is commanding (1 or -1)
  uint32_t stuck_time_start_ = 0; // The timestamp (in ms) when the motor first appeared stuck
  bool is_recovery_active_ = false; // Flag to block new commands while the motor reverses
};