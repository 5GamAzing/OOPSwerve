/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/PWMTalonSRX.h>
#include <frc/Encoder.h>

static const int BUFFER = 10;

class SwerveWheel : public frc::Subsystem {
 private:
  frc::PWMTalonSRX *swivelMotor;
  frc::PWMTalonSRX *driveMotor;
  frc::Encoder *driveEncoder;
  
  float SPEED = 0.2;

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  SwerveWheel(int idx);

  void setSpeed(double value){
    driveMotor->Set(value);
  }

  void turnWheel(int angle){

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

  void turnWheel360(int target){
    //Keep encoder values between -360 and 360
    if (driveEncoder->Get() >= 360) {
      driveEncoder->Reset();
    }
    else if (driveEncoder->Get() <= -360) {
      driveEncoder->Reset();
    }
    
    int x = (driveEncoder->Get() + 360) % 360;
    int min = target - BUFFER;
    int max = target + BUFFER;
    min = (min + 720) % 360;
    max = (max + 360) % 360;

    if (min < max && (x > min && x < max)) {
      swivelMotor->Set(0);
    }
    else if (target < 180 && (x > min + 360 || x < max)) {
      swivelMotor->Set(0);
    }
    else if (target > 180 && (x > min || x < max - 360)) {
      swivelMotor->Set(0);
    }
    else if (((x + 180) % 360) < target) {
      swivelMotor->Set(SPEED);
    }
    else {
      swivelMotor->Set(-SPEED);
    }
  }

  void InitDefaultCommand() override;
};
