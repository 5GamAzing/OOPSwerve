
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Subsystems/SwerveWheel.h>
#include <frc/XboxController.h>
#include <frc/commands/Subsystem.h>
#include <frc/drive/Vector2d.h>
#include <math.h>
#include "RobotMap.h"


class FOSwerveDrive : public frc::Subsystem {
 private:
  float SPEED = 0.5;
  int ENCODERS = 360;
  
  SwerveWheel *frontLeft;
  SwerveWheel *frontRight;
  SwerveWheel *backLeft;
  SwerveWheel *backRight;

  float angleCalc(float x, float y);

  float distCalc(float x, float y);


  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities


 public:
  FOSwerveDrive();

  
//takes joystick values and determines what angle you want the wheels to be turned
  void driveSwerve(frc::XboxController *driverJoystick, int mode = 0);
    
  void InitDefaultCommand() override;

  FOSwerveDrive* get() { return this; }
};
