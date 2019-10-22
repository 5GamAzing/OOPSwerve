/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "Subsystems/SwerveWheel.h"
#include "RobotMap.h"
#include "PWMTalonSRX.h"
#include "frc/Encoder.h"

SwerveWheel::SwerveWheel(int idx) : Subsystem("SwerveWheel") {

    if (idx == 0) {
        driveMotor = new frc::PWMTalonSRX(FRONT_LEFT_DRIVE);
        swivelMotor = new frc::PWMTalonSRX(FRONT_LEFT_SPIN);
        driveEncoder = new frc::Encoder(FL_ENCODER_0,FL_ENCODER_1);
        driveEncoder->Reset();
    }
    else if (idx == 1) {
        driveMotor = new frc::PWMTalonSRX(FRONT_RIGHT_DRIVE);
        swivelMotor = new frc::PWMTalonSRX(FRONT_RIGHT_SPIN);
        driveEncoder = new frc::Encoder(FR_ENCODER_0,FR_ENCODER_1);
        driveEncoder->Reset();
    }
    else if (idx == 2) {
        driveMotor = new frc::PWMTalonSRX(BACK_RIGHT_DRIVE);
        swivelMotor = new frc::PWMTalonSRX(BACK_RIGHT_SPIN);
        driveEncoder = new frc::Encoder(BR_ENCODER_0,BR_ENCODER_1);
        driveEncoder->Reset();
    }
    else {
        driveMotor = new frc::PWMTalonSRX(BACK_LEFT_DRIVE);
        swivelMotor = new frc::PWMTalonSRX(BACK_LEFT_SPIN);
        driveEncoder = new frc::Encoder(BL_ENCODER_0,BL_ENCODER_1);
        driveEncoder->Reset();
    }

}


void SwerveWheel::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}


void SwerveWheel::setSpeed(double value){
    driveMotor->Set(value);
}

void SwerveWheel::turnWheel360(int target){
    if (driveEncoder->Get() >= 360) {
      driveEncoder->Reset();
    }
    else if (driveEncoder->Get() <= -360) {
      driveEncoder->Reset();
    }
    
    int x = (driveEncoder->Get() + 360) % 360;
    int min = target - 30;
    int max = target + 30;
    int mode;
    min = (min + 720) % 360;
    max = (max + 360) % 360;

    if (min < max && (x > min && x < max)) {
      swivelMotor->Set(0);
      mode = 0;
    }
    else if (max < min && target < 180 && (x > min + 360 || x < max)) {
      swivelMotor->Set(0);
      mode = 1;
    }
    else if (max < min && target > 180 && (x > min || x < max - 360)) {
      swivelMotor->Set(0);
      mode = 2;
    }
    else if (x + 180 > target) {
    //else if (x > target) {
      swivelMotor->Set(0.5);
      mode = 3;
    }
    else {
      swivelMotor->Set(-0.5);
      mode = 4;
    }
    printf("%d - %d - %d : %d ---- %d\n", min, x, max, mode, driveEncoder->Get());
}

void SwerveWheel::turnWheel(int angle){

    //endcoder has 360 ticks in one revolution
    int encoderValue = ((*driveEncoder).Get())%360;
    int lowTolerance = (angle)-BUFFER;
    int highTolerance = (angle)+BUFFER;
    //double speed = abs(encoderValue-angle)/180*SPEED;
    //for testing
    double speed = SPEED;

    /*encoder value will be a value from -48 to 48, (I have to check if modulo math keeps negatives)
    angle is in radians, dividing by 2pi and multiplying by encoders scales it to an encoder value
    setting the swivel motor to a small value (for now) until it reaches the desired encoder angle
    */
  

    if ((lowTolerance < encoderValue) && (encoderValue < highTolerance)){ //Shouldn't these be if instead of while?
      swivelMotor->Set(0);
    }
    if (encoderValue<lowTolerance){
      swivelMotor->Set(speed);
    }
    if (encoderValue > highTolerance){
      swivelMotor->Set(-speed);
    }

  }

// Put methods for controlling this subsystem
// here. Call these from Commands.
