/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/commands/Scheduler.h>

#include "OI.h"
#include "Subsystems/SwerveWheel.h"
#include "Subsystems/SwerveDrive.h"
#include "Robot.h"

std::shared_ptr<SwerveDrive> Robot::SwerveBase;
std::unique_ptr<OI> Robot::oi;

void Robot::RobotInit() {
  //chooser.SetDefaultOption("Autonomous Command", new AutonomousCommand());
  //m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  //frc::SmartDashboard::PutData("Auto Modes", &chooser);
  
  /*Robot::FOSwerveBase = FOSwerveDrive();
  Robot::ROSwerveBase = ROSwerveDrive();
  Robot::HallTestBase = HallTest();
  Robot::OperatorInterface = OI();*/
  SwerveBase.reset(new SwerveDrive());
  oi.reset(new OI());
}

//void Robot::RobotPeriodic() {
  //frc::Scheduler::GetInstance()->Run();
//}

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	//autonomousCommand = chooser.GetSelected();
	//if (autonomousCommand != nullptr)
	//	autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	//if (autonomousCommand != nullptr)
	//	autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {

  //(*mySwerve). driveSwerve(OperatorInterface->getDriverJoystick());
  frc::Scheduler::GetInstance()->Run();

}

//void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main(int argc, char** argv) {
    return frc::StartRobot<Robot>();
}
#endif
