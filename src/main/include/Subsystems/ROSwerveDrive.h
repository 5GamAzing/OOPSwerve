
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
#include "RobotMap.h"

class ROSwerveDrive : public frc::Subsystem {
 private:
  
  SwerveWheel *frontLeft;
  SwerveWheel *frontRight;
  SwerveWheel *backLeft;
  SwerveWheel *backRight;


  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities


 public:
  ROSwerveDrive();

  
//takes joystick values and determines what angle you want the wheels to be turned
  void driveSwerve(frc::XboxController *driverJoystick);
    
  void InitDefaultCommand() override;

  ROSwerveDrive* get() { return this; }
};
