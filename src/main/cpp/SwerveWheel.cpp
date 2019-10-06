/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "SwerveWheel.h"
#include "RobotMap.h"
#include "PWMTalonSRX.h"
#include "frc/Encoder.h"

SwerveWheel::SwerveWheel(int idx) : Subsystem("SwerveWheel") {

    if (idx == 0) {
        driveMotor = new frc::PWMTalonSRX(FRONT_LEFT_DRIVE);
        swivelMotor = new frc::PWMTalonSRX(FRONT_LEFT_SPIN);
        driveEncoder = new frc::Encoder(0,1);
        driveEncoder->Reset();
    }
    else if (idx == 1) {
        driveMotor = new frc::PWMTalonSRX(FRONT_RIGHT_DRIVE);
        swivelMotor = new frc::PWMTalonSRX(FRONT_RIGHT_SPIN);
        driveEncoder = new frc::Encoder(3,4);
        driveEncoder->Reset();
    }
    else if (idx == 2) {
        driveMotor = new frc::PWMTalonSRX(BACK_RIGHT_DRIVE);
        swivelMotor = new frc::PWMTalonSRX(BACK_RIGHT_SPIN);
        driveEncoder = new frc::Encoder(5,6);
        driveEncoder->Reset();
    }
    else {
        driveMotor = new frc::PWMTalonSRX(BACK_LEFT_DRIVE);
        swivelMotor = new frc::PWMTalonSRX(BACK_LEFT_SPIN);
        driveEncoder = new frc::Encoder(7,8);
        driveEncoder->Reset();
    }

}


void SwerveWheel::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
