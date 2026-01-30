#pragma once
#include "main.h"
#include "drive.hpp"
#include "intake.hpp"
#include "outtake.hpp"
#include "bar.hpp"


// Ports — match your Python ports
constexpr int PORT_FL = 5;
constexpr int PORT_BL = 6;
constexpr int PORT_FR = 20;
constexpr int PORT_BR = 7;

constexpr int PORT_INTAKE = 10;
constexpr int PORT_LONG_OUTTAKE = 4;
constexpr int PORT_UPPER_OUTTAKE = 3;
constexpr int PORT_BAR = 8;


class Bar;
class Intake;
class Outtake;


namespace Robot {
  extern pros::Controller master;

  extern pros::Motor front_left;
  extern pros::Motor back_left;
  extern pros::Motor front_right;
  extern pros::Motor back_right;

  extern MecanumDrive* drive;
  extern Intake* intake;
  extern Outtake* long_outtake;
  extern Outtake* upper_outtake;
  extern Bar* bar;

  void init();     // initialize objects
  void shutdown(); // cleanup if needed
}
