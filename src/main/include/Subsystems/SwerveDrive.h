
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SWERVEDRIVE_H
#define SWERVEDRIVE_H

#include <Subsystems/SwerveWheel.h>
#include <frc/XboxController.h>
#include <frc/commands/Subsystem.h>
#include <frc/drive/Vector2d.h>
#include <math.h>
#include "frc/WPILib.h"
#include "RobotMap.h"


class SwerveDrive : public frc::Subsystem {
 private:
  float SPEED = 0.5;
  int ENCODERS = 360;
  
  SwerveWheel *frontLeft;
  SwerveWheel *frontRight;
  SwerveWheel *backLeft;
  SwerveWheel *backRight;

  frc::SerialPort *serial;

  float angleCalc(float x, float y);

  float distCalc(float x, float y);


  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities


 public:
  SwerveDrive();

  
  //takes joystick values and determines what angle you want the wheels to be turned
  void driveSwerveFO(frc::XboxController *driverJoystick, int mode = 0);
  void driveSwerveRO(frc::XboxController *driverJoystick);
  void testHall(frc::XboxController *driverJoystick);
    
  void InitDefaultCommand() override;

  SwerveDrive* get() { return this; }
};

#endif