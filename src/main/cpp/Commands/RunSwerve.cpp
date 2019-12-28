/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotMap.h"
#include "Commands/RunSwerve.h"
#include "Subsystems/SwerveDrive.h"
#include <OI.h>
#include <Robot.h>


RunSwerve::RunSwerve() : frc::Command() {
  
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  
  Requires(Robot::SwerveBase.get());
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void RunSwerve::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunSwerve::Execute() {

  frc::XboxController *driverJoystick = Robot::oi.get()->getDriverJoyStick().get();
  switch(SWERVE_MODE) {
  case 0:
    Robot::SwerveBase.get()->driveSwerveFO(driverJoystick, FO_MODE);
    break;
  case 1:
    Robot::SwerveBase.get()->driveSwerveRO(driverJoystick);
    break;
  case 2:
    Robot::SwerveBase.get()->testHall(driverJoystick);
    break;
  default:
    printf("Invalid swerve mode!\n");
  }

}

// Make this return true when this Command no longer needs to run execute()
bool RunSwerve::IsFinished() { return false; }

// Called once after isFinished returns true
void RunSwerve::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunSwerve::Interrupted() {}
