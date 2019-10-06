
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <SwerveWheel.h>
#include <frc/XboxController.h>
#include <frc/commands/Subsystem.h>
#include "RobotMap.h"

class ROSwerveDrive : public frc::Subsystem {
 private:
  
  SwerveWheel *frontLeft;
  SwerveWheel *frontRight;
  SwerveWheel *backLeft;
  SwerveWheel *backRight;


  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities


 public:
  ROSwerveDrive();

  
//takes joystick values and determines what angle you want the wheels to be turned
  void driveSwerve(frc::XboxController *driverJoystick){
    frontLeft->turnWheel(0.2);
    frontRight->turnWheel(0.2);
    backLeft->turnWheel(0.2);
    backRight->turnWheel(0.2);
    
    /*double xvalue = driverJoystick-> GetRawAxis(LEFT_X);
    double yvalue = driverJoystick-> GetRawAxis(LEFT_Y);
  
    //angle section
    double angleRad = atan2(yvalue, xvalue);
    double angleDeg = angleRad* 180/3.14159265;
    
    double spinValue = driverJoystick->GetRawAxis(RIGHT_X); 
    double spinAngle = spinValue*90;
    /*the spinValue math determines how much to spin the robot proportional to the right joystick
    it is always a fraction of  degrees towards the turn for the front motors, away from the turn for the back
    this if statement is so that it is more efficient and the wheel never turns more than 180 degrees*/
   /*if(angleDeg<0){
     angleDeg= angleDeg+180;
   }
   else
   {
     angleDeg=angleDeg;
   }
   
    frontLeft->turnWheel(angleDeg+ spinAngle);
    frontRight->turnWheel(angleDeg + spinAngle);
    backLeft->turnWheel(angleDeg - spinAngle);
    backRight->turnWheel(angleDeg - spinAngle);
    
    //speed section
    double magnitude = sqrt(xvalue*xvalue + yvalue*yvalue);
    
    //speed is always the magnitude of the left joystick, but depends what quadrant it's in
    //if the angle is from 0 to -pi, move backwards
    if (angleRad<0){
      frontLeft->setSpeed(-magnitude);
    frontRight->setSpeed(-magnitude);
    backLeft->setSpeed(-magnitude);
    backRight->setSpeed(-magnitude);
    }
    else{
    frontLeft->setSpeed(magnitude);
    frontRight->setSpeed(magnitude);
    backLeft->setSpeed(magnitude);
    backRight->setSpeed(magnitude);
    }
    */
  }
    
  void InitDefaultCommand() override;
};
