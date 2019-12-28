/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>
#include "Commands/AutonomousCommand.h"
#include "OI.h"
#include <frc/XboxController.h>

OI::OI() {
   driverJoyStick.reset(new frc::XboxController(0));
   operatorJoyStick.reset(new frc::XboxController(1));
}

std::shared_ptr<frc::XboxController> OI::getDriverJoyStick() {
   return driverJoyStick;
}

std::shared_ptr<frc::XboxController> OI::getOperatorJoyStick() {
   return operatorJoyStick;
}