/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#ifndef OI_H
#define OI_H

#include "frc/WPILib.h"
#include <frc/XboxController.h>

class OI {
private:
	std::shared_ptr<frc::XboxController> driverJoyStick;
	std::shared_ptr<frc::XboxController> operatorJoyStick;
public:
	OI();
	std::shared_ptr<frc::XboxController> getDriverJoyStick();
	std::shared_ptr<frc::XboxController> getOperatorJoyStick();
};

#endif
