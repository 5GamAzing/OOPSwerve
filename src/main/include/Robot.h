/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _ROBOT_H
#define _ROBOT_H

#include <string>
#include "Subsystems/SwerveDrive.h"
#include "OI.h"
#include "frc/WPILib.h"
#include "frc/commands/Command.h"
#include "frc/livewindow/LiveWindow.h"
#include "Commands/AutonomousCommand.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>



class Robot : public frc::TimedRobot {
 public:

  /*static FOSwerveDrive FOSwerveBase;
  static ROSwerveDrive ROSwerveBase;
  static HallTest HallTestBase;*/
  static std::shared_ptr<SwerveDrive> SwerveBase;
  
  //static OI OperatorInterface;
	static std::unique_ptr<OI> oi;

	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;


 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};

#endif