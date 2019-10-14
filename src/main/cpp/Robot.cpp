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
#include "Subsystems/FOSwerveDrive.h"
#include "Subsystems/ROSwerveDrive.h"
#include "Subsystems/HallTest.h"
#include "Robot.h"

std::shared_ptr<FOSwerveDrive> Robot::FOSwerveBase;
std::shared_ptr<ROSwerveDrive> Robot::ROSwerveBase;
std::shared_ptr<HallTest> Robot::HallTestBase;
std::unique_ptr<OI> Robot::oi;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  
  /*Robot::FOSwerveBase = FOSwerveDrive();
  Robot::ROSwerveBase = ROSwerveDrive();
  Robot::HallTestBase = HallTest();
  Robot::OperatorInterface = OI();*/
  FOSwerveBase.reset(new FOSwerveDrive());
  ROSwerveBase.reset(new ROSwerveDrive());
  HallTestBase.reset(new HallTest());
  oi.reset(new OI());
  
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc::Scheduler::GetInstance()->Run();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString(
  //     "Auto Selector", kAutoNameDefault);
  //std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  frc::Scheduler::GetInstance()->Run();
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
    
}

void Robot::TeleopPeriodic() {

  //(*mySwerve). driveSwerve(OperatorInterface->getDriverJoystick());
  frc::Scheduler::GetInstance()->Run();

}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
