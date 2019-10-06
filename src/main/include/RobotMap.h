/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
//these are static variables that are the indexes for every real thing on the robot
//joystick
const int DRIVER_JOYSTICK = 0;
const int OPERATOR_JOYSTICK = 1;

//joystick axes
const int LEFT_X = 0;
const int LEFT_Y = 1;
const int RIGHT_X = 4;

//hand definitions
#define LHAND frc::GenericHID::kLeftHand
#define RHAND frc::GenericHID::kRightHand

//drive motors
const int FRONT_LEFT_DRIVE = 8;
const int FRONT_LEFT_SPIN = 1;
const int FRONT_RIGHT_DRIVE=9;
const int FRONT_RIGHT_SPIN=3;
const int BACK_LEFT_DRIVE=5;
const int BACK_LEFT_SPIN=4;
const int BACK_RIGHT_DRIVE=7;
const int BACK_RIGHT_SPIN=6;

//encoders
const int FL_ENCODER_0 = 0;
const int FL_ENCODER_1 = 1;
const int FR_ENCODER_0 = 6;
const int FR_ENCODER_1 = 7;
const int BL_ENCODER_0 = 2;
const int BL_ENCODER_1 = 3;
const int BR_ENCODER_0 = 4;
const int BR_ENCODER_1 = 5;

class RobotMap : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  RobotMap();
  void InitDefaultCommand() override;
};
