/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/SerialPort.h>

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

//swerve mode
const int SWERVE_MODE = 0; //0 = Field Oriented, 1 = Robot Oriented, 2 = HallTest
const int FO_MODE = 5; //0 = all wheels together, 1 = 1 joystick control (no turns), 2 = 90 deg turns, 3 = variable turns, 4 = custom vector math, 5 = WPILIB vector math w/ gyro

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
const int FL_ANALOG = 0;
const int FR_ANALOG = 1;
const int BL_ANALOG = 2;
const int BR_ANALOG = 3;

const int GYRO_SERIAL_BAUDRATE = 115200;
const frc::SerialPort::Port GYRO_SERIAL_PORT = frc::SerialPort::kUSB;

class RobotMap : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  RobotMap();
  void InitDefaultCommand() override;
};
