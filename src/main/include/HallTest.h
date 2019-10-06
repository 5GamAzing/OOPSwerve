
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "SwerveWheel.h"
#include <frc/XboxController.h>
#include <frc/commands/Subsystem.h>
#include "RobotMap.h"

class HallTest : public frc::Subsystem {
 private:
  
  SwerveWheel *frontLeft;
  SwerveWheel *frontRight;
  SwerveWheel *backLeft;
  SwerveWheel *backRight;


  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities


 public:
  HallTest();

  
//takes joystick values and determines what angle you want the wheels to be turned
  void testHall(frc::XboxController *driverJoystick) {
  if ((*driverJoystick).GetAButton() == 1) {
    frontLeft->turnWheel360(90);
  }
  if ((*driverJoystick).GetBButton() == 1) {
    frontLeft->turnWheel360(-90);
  }
  if ((*driverJoystick).GetXButton() == 1) {
    frontRight->setSpeed(0.5);
  }
  else if ((*driverJoystick).GetYButton() == 1) {
    frontRight->setSpeed(-0.5);
  }
  else {
    frontRight->setSpeed(0);
  }
  /*(*flTurn).Set(0.2*20000/25849);
  (*frTurn).Set(0.2*20000/9635);
  (*brTurn).Set(0.2*20000/19622);
  (*blTurn).Set(0.2*20000/27311);*/
  //printf("%d %d %d %d\n", (*flHall).Get(), (*frHall).Get(), (*brHall).Get(), (*blHall).Get());
}
    
  void InitDefaultCommand() override;
};
