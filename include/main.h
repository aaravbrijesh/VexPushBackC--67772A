/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * \copyright Copyright (c) 2017-2024, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convenient for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"

/**
 * You should add more #includes here
 */
//#include "okapi/api.hpp"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
// using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>

// --- CRITICAL FIX: INCLUDE CUSTOM HEADERS HERE ---
// These declarations are needed before they are used in extern statements.
#include "robot.hpp"     // Defines constants and the Robot namespace (used in src/robot.cpp)
#include "drive.hpp"     // Defines the MecanumDrive class
#include "intake.hpp"    // Defines the Intake class
#include "outtake.hpp"   // Defines the Outtake class
#include "bar.hpp"       // Defines the Bar class
#include "treads.hpp"    // Defines the Treads class
// ---------------------------------------------------


// --- REQUIRED GLOBAL C++ FUNCTION PROTOTYPES ---
// These allow opcontrol.cpp to call functions defined in other source files.
void drive_control();
void intake_control();
void outtake_control();
void treads_control();
void intake_system_control();
void bar_control(); 
void treads_control();
// ---------------------------------------------------

#endif // __cplusplus

// --- REQUIRED GLOBAL C++ VARIABLE DECLARATIONS ---
// These 'extern' statements tell the compiler that these objects are defined 
// in exactly one other place (src/robot.cpp).

// PROS API Global Objects
extern pros::Controller controller;
extern pros::MotorGroup left_motors; 
extern pros::MotorGroup right_motors;

// Custom Subsystem Global Objects (FIX: Removed Robot:: prefix to resolve error)
extern MecanumDrive chassis;
extern Intake my_intake;
extern Outtake my_outtake;
extern Bar my_bar;
extern Treads my_treads;
// ---------------------------------------------------

#endif  // _PROS_MAIN_H_