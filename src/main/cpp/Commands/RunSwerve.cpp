/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/RunSwerve.h"
#include "Subsystems/FOSwerveDrive.h"
#include "Subsystems/ROSwerveDrive.h"
#include "Subsystems/HallTest.h"
#include <OI.h>
#include <Robot.h>


driveSwerve::driveSwerve() {
  
  frc::XboxController *driverJoystick = Robot::oi.get()->getDriverJoystick();
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  
  Requires(Robot::FOSwerveBase.get());
  Requires(Robot::ROSwerveBase.get());
  Requires(Robot::HallTestBase.get());
}

// Called just before this Command runs the first time
void driveSwerve::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void driveSwerve::Execute() {

  Robot::FOSwerveBase.get()->driveSwerve(driverJoystick);

}

// Make this return true when this Command no longer needs to run execute()
bool driveSwerve::IsFinished() { return false; }

// Called once after isFinished returns true
void driveSwerve::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void driveSwerve::Interrupted() {}
