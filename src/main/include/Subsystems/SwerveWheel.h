/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SWERVEWHEEL_H
#define SWERVEWHEEL_H

#include <frc/commands/Subsystem.h>
#include <frc/PWMTalonSRX.h>
#include <frc/Encoder.h>

class SwerveWheel : public frc::Subsystem {
 private:
  frc::PWMTalonSRX *swivelMotor;
  frc::PWMTalonSRX *driveMotor;
  frc::AnalogInput *driveEncoder;
  
  float SPEED = 0.2;
  int BUFFER = 10;

 public:
  SwerveWheel(int idx);

  void setSpeed(double value);

  void turnWheel(int angle);

  void turnWheel360(int target);

  void InitDefaultCommand() override;
};

#endif