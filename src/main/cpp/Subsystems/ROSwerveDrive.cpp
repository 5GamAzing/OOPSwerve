/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/ROSwerveDrive.h"
#include "Subsystems/SwerveWheel.h"
#include "../Commands/RunSwerveRO.cpp"



ROSwerveDrive::ROSwerveDrive()  : Subsystem("ROSwerveDrive") {

  frontLeft = new SwerveWheel(0);
  frontRight = new SwerveWheel(1);
  backLeft = new SwerveWheel(2);
  backRight = new SwerveWheel(3);

  



}

void ROSwerveDrive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new RunSwerveRO());
}

void ROSwerveDrive::driveSwerve(frc::XboxController *driverJoystick){
    //The left joystick determines the speed and if the wheels 
    //  should move forward or backward.
    double xvalue = driverJoystick-> GetRawAxis(LEFT_X);
    double yvalue = driverJoystick-> GetRawAxis(LEFT_Y);    
    
    //first start moving the wheels either forward or backward
    //  depending on the magnitude & direction of the joystick
    double magnitude = sqrt(xvalue*xvalue + yvalue*yvalue);
    
    //speed is always the magnitude of the left joystick, but depends what quadrant it's in
    //if the angle is from 0 to -pi, move backwards
    double angleRad = atan2(yvalue, xvalue);
    
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

  
    //figure out the direction to spin the wheels using the 
    //  left joystick and use the right joystick to determine
    //  if the robot chassis should also spin 
 
    double angleDeg = angleRad* 180/3.14159265;
    double spinValue = driverJoystick->GetRawAxis(RIGHT_X); 
    double spinAngle = spinValue*90;
    /*the spinValue math determines how much to spin the robot proportional to the right joystick
    it is always a fraction of  degrees towards the turn for the front motors, away from the turn for the back
    this if statement is so that it is more efficient and the wheel never turns more than 180 degrees*/
    if(angleDeg<0){
      angleDeg= angleDeg+180;
    }
    else{
     angleDeg=angleDeg;
    }
    frontLeft->turnWheel(angleDeg+ spinAngle);
    frontRight->turnWheel(angleDeg + spinAngle);
    backLeft->turnWheel(angleDeg - spinAngle);
    backRight->turnWheel(angleDeg - spinAngle);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
