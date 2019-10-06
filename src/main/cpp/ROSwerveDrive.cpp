/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ROSwerveDrive.h"
#include "SwerveWheel.h"



ROSwerveDrive::ROSwerveDrive()  : Subsystem("ROSwerveDrive") {

  frontLeft = new SwerveWheel(0);
  frontRight = new SwerveWheel(1);
  backLeft = new SwerveWheel(2);
  backRight = new SwerveWheel(3);

  



}

void ROSwerveDrive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
