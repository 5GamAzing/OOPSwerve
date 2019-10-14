
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Subsystems/SwerveWheel.h>
#include <frc/XboxController.h>
#include <frc/commands/Subsystem.h>
#include <frc/drive/Vector2d.h>
#include <math.h>
#include "RobotMap.h"


class FOSwerveDrive : public frc::Subsystem {
 private:
  float SPEED = 0.5;
  int ENCODERS = 360;
  
  SwerveWheel *frontLeft;
  SwerveWheel *frontRight;
  SwerveWheel *backLeft;
  SwerveWheel *backRight;

  float angleCalc(float x, float y) {
    float angle;
    if (x == 0 && y == 0)
        return -1;
    if (y == 0)
        angle = 90.0;
    else
        angle = atanf(abs(x)/abs(y)) * 57.2958; //may be asinf, not quite sure yet
    if (x < 0 && y < 0) {
        angle += 180;
    }
    else if (x < 0) {
        angle += 180 + (2 * (90 - angle));
        if (y < 0)
            angle -= 2 * (90 - angle);
    }
    else if (y < 0)
        angle += 2 * (90 - angle);
    return angle;
  }

  float distCalc(float x, float y) {
    return sqrt(pow(x, 2) + pow(y, 2));
  }


  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities


 public:
  FOSwerveDrive();

  
//takes joystick values and determines what angle you want the wheels to be turned
  void driveSwerve(frc::XboxController *driverJoystick, int mode = 0) {
    //Define variables
    int targetEncoder[4];
    float targetSpeed[4], turnMagnitude[4];
    float vector1[2], vector2[4][2], finalVector[4][2];
    frc::Vector2d *driveVector = new frc::Vector2d;
    frc::Vector2d *turnVector = new frc::Vector2d;
    frc::Vector2d *sumVector = new frc::Vector2d;

    //Calculate joystick angles
    float lAngle = angleCalc(driverJoystick->GetX(LHAND), 0-driverJoystick->GetY(LHAND));
    float rAngle = angleCalc(driverJoystick->GetX(RHAND), 0-driverJoystick->GetY(RHAND));

    //Mode 0 drive
    if (mode == 0) {
        //Scale the joystick angle into encoder angle
        targetEncoder[0] = (int)(lAngle / 360 * ENCODERS);
        targetEncoder[1] = targetEncoder[0];
        targetEncoder[2] = targetEncoder[0];
        targetEncoder[3] = targetEncoder[0];
        //Find target speed
        targetSpeed[0] = SPEED * ((driverJoystick->GetTriggerAxis(RHAND) - driverJoystick->GetTriggerAxis(LHAND)));
        if (targetSpeed[0] < 0.2 && targetSpeed[0] > -0.2) //Stop range
            targetSpeed[0] = 0;
        targetSpeed[1] = targetSpeed[0];
        targetSpeed[2] = targetSpeed[0];
        targetSpeed[3] = targetSpeed[0];
    }
    
    //Mode 1 drive (same as 0 but with joystick to calculate speed)
    if (mode == 1) {
        //Scale joystick angle into encoder angle
        targetEncoder[0] = (int)(rAngle / 360 * ENCODERS);
        targetEncoder[1] = targetEncoder[0];
        targetEncoder[2] = targetEncoder[0];
        targetEncoder[3] = targetEncoder[0];
        //Calculate the target speed
        targetSpeed[0] = (distCalc(driverJoystick->GetX(RHAND), 0-driverJoystick->GetY(RHAND))) * SPEED;
        targetSpeed[1] = targetSpeed[0];
        targetSpeed[2] = targetSpeed[0];
        targetSpeed[3] = targetSpeed[0];
    }

    //Mode 2 angle calculation (test 90 degree turning)
    if (mode == 2) {
        turnMagnitude[0] = 45;
        turnMagnitude[1] = turnMagnitude[0] + 90;
        turnMagnitude[2] = turnMagnitude[1] + 90;
        turnMagnitude[3] = turnMagnitude[2] + 90;
    }

    //Mode 3/4 angle calculation
    if (mode == 3 || mode == 4) {
        //Scale from (-1)-1 onto 0-90, then rotate 90 for each motor
        turnMagnitude[0] = ((driverJoystick->GetX(LHAND)) * 45) + 45;
        turnMagnitude[1] = turnMagnitude[0] + 90;
        turnMagnitude[2] = turnMagnitude[1] + 90;
        turnMagnitude[3] = turnMagnitude[2] + 90;
    }
    
    //Mode 2/3 scaling and speed
    if (mode == 2 || mode == 3) {
        //Scale from degrees onto encoder angle
        targetEncoder[0] = (int)(turnMagnitude[0] / 360 * ENCODERS);
        targetEncoder[1] = (int)((turnMagnitude[1]) / 360 * ENCODERS);
        targetEncoder[2] = (int)((turnMagnitude[2]) / 360 * ENCODERS);
        targetEncoder[3] = (int)((turnMagnitude[3]) / 360 * ENCODERS) % ENCODERS; // "% ENCODERS" to loop ENCODERS back to 0
        //Set each motor to move at SPEED constantly
        targetSpeed[0] = SPEED;
        targetSpeed[1] = targetSpeed[0];
        targetSpeed[2] = targetSpeed[0];
        targetSpeed[3] = targetSpeed[0];
    }

    //Mode 4 vector math (inefficient coding but soon to be replaced hopefully by mode 5)
    if (mode == 4) {
        //Yes this could be better done with loops but it's probably gonna get deleted anyways
        //Find yaw vector to move robot without spinning for each wheel
        vector1[0] = driverJoystick->GetX(RHAND);
        vector1[1] = 0-driverJoystick->GetY(RHAND);
        //Scale from degrees to x and y values ranging 0-1 (reverse angleCalc basically)
        vector2[0][0] = cosf(turnMagnitude[0]) * 57.2958;
        vector2[0][1] = sinf(turnMagnitude[0]) * 57.2958;
        vector2[1][0] = cosf(turnMagnitude[1]) * 57.2958;
        vector2[1][1] = sinf(turnMagnitude[1]) * 57.2958;
        vector2[2][0] = cosf(turnMagnitude[2]) * 57.2958;
        vector2[2][1] = sinf(turnMagnitude[2]) * 57.2958;
        vector2[3][0] = cosf(turnMagnitude[3]) * 57.2958;
        vector2[3][1] = sinf(turnMagnitude[3]) * 57.2958;
        //Add the two vectors for each wheel
        finalVector[0][0] = vector1[0] + vector2[0][0];
        finalVector[0][1] = vector1[1] + vector2[0][1];
        finalVector[1][0] = vector1[0] + vector2[1][0];
        finalVector[1][1] = vector1[1] + vector2[1][1];
        finalVector[2][0] = vector1[0] + vector2[2][0];
        finalVector[2][1] = vector1[1] + vector2[2][1];
        finalVector[3][0] = vector1[0] + vector2[3][0];
        finalVector[3][1] = vector1[1] + vector2[3][1];

        //vectors --> angles & speeds
        targetEncoder[0] = angleCalc(finalVector[0][0], finalVector[0][1]);
        targetEncoder[1] = angleCalc(finalVector[1][0], finalVector[1][1]);
        targetEncoder[2] = angleCalc(finalVector[2][0], finalVector[2][1]);
        targetEncoder[3] = angleCalc(finalVector[3][0], finalVector[3][1]);
        targetSpeed[0] = distCalc(finalVector[0][0], finalVector[0][1]) / 2 * SPEED;
        targetSpeed[1] = distCalc(finalVector[1][0], finalVector[1][1]) / 2 * SPEED;
        targetSpeed[2] = distCalc(finalVector[2][0], finalVector[2][1]) / 2 * SPEED;
        targetSpeed[3] = distCalc(finalVector[3][0], finalVector[3][1]) / 2 * SPEED;
    }

    //Mode 5 vector math (WPILib vectors)
    if (mode == 5) {
      driveVector->x = driverJoystick->GetX(RHAND);
      driveVector->y = 0 - driverJoystick->GetY(RHAND);
      turnVector->x = cosf((driverJoystick->GetX(LHAND) * 45) + 45) * 57.2958;
      turnVector->y = sinf((driverJoystick->GetX(LHAND) * 45) + 45) * 57.2958;
      for (int i = 0; i < 4; i++) { //For each wheel:
        sumVector->x = (driveVector->x + turnVector->x) / 2; //Add the two vectors to get one final vector
        sumVector->y = (driveVector->y + turnVector->y) / 2;
        targetEncoder[i] = angleCalc(driveVector->x, driveVector->y); //Calculate the angle of this vector
        targetSpeed[i] = driveVector->Magnitude() * SPEED; //Scale the speed of 
        turnVector->Rotate(-90.0); //Rotate the vector clockwise 90 degrees
      }
    }
    frontLeft->turnWheel360(targetEncoder[0]);
    frontRight->turnWheel360(targetEncoder[1]);
    backRight->turnWheel360(targetEncoder[2]);
    backLeft->turnWheel360(targetEncoder[3]);
    frontLeft->setSpeed(targetSpeed[0]);
    frontRight->setSpeed(targetSpeed[1]);
    backRight->setSpeed(targetSpeed[2]);
    backLeft->setSpeed(targetSpeed[3]);
  }
    
  void InitDefaultCommand() override;

  FOSwerveDrive* get() { return this; }
};
