/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/HallTest.h"
#include "Subsystems/SwerveWheel.h"



HallTest::HallTest()  : Subsystem("HallTest") {

  frontLeft = new SwerveWheel(0);
  frontRight = new SwerveWheel(1);
  backLeft = new SwerveWheel(2);
  backRight = new SwerveWheel(3);

  



}

void HallTest::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  //SetDefaultCommand(new RunSwerve());
}

void HallTest::driveSwerve(frc::XboxController *driverJoystick) {
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

// Put methods for controlling this subsystem
// here. Call these from Commands.
