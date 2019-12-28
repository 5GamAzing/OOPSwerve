/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/SwerveDrive.h"
#include "Subsystems/SwerveWheel.h"
#include <math.h>
#include "../../include/Commands/RunSwerve.h"


SwerveDrive::SwerveDrive()  : Subsystem("SwerveDrive") {

    frontLeft = new SwerveWheel(0);
    AddChild("front left", frontLeft);
    frontRight = new SwerveWheel(1);
    AddChild("front right", frontRight);
    backLeft = new SwerveWheel(2);
    AddChild("back left", backLeft);
    backRight = new SwerveWheel(3);
    AddChild("back right", backRight);

    serial = new frc::SerialPort(GYRO_SERIAL_BAUDRATE, GYRO_SERIAL_PORT);
    serial->EnableTermination();
    serial->Write("Start\n");
}

float SwerveDrive::distCalc(float x, float y) {
  return sqrt(pow(x, 2) + pow(y, 2));
}

float SwerveDrive::angleCalc(float x, float y) {
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

void SwerveDrive::driveSwerveFO(frc::XboxController *driverJoystick, int mode) {
    //Define variables
    int targetEncoder[4];
    float targetSpeed[4], turnMagnitude[4];
    float vector1[2], vector2[4][2], finalVector[4][2];
    char rawOffset[10] = {0};
    int offset;
    bool negativeOffset = false;
    frc::Vector2d *driveVector = new frc::Vector2d;
    frc::Vector2d *turnVector = new frc::Vector2d;
    frc::Vector2d *sumVector = new frc::Vector2d;

    //Convert offset from string to float
    serial->Read(rawOffset, 10);
    for (int i = 0; i < 10; i++) {
        if (rawOffset[i] == '.') {
            break;
        }
        else if (rawOffset[i] == '-') {
            negativeOffset = true;
        }
        else {
            offset *= 10;
            offset += rawOffset[i] - '0';
        }
    }

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
      driveVector->Rotate(360-offset); //Factor in gyroscope value (subtract from 360 to go from counterclockwise to clockwise)
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
    frontLeft->turnWheel(targetEncoder[0]);
    frontRight->turnWheel(targetEncoder[1]);
    backRight->turnWheel(targetEncoder[2]);
    backLeft->turnWheel(targetEncoder[3]);
    frontLeft->setSpeed(targetSpeed[0]);
    frontRight->setSpeed(targetSpeed[1]);
    backRight->setSpeed(targetSpeed[2]);
    backLeft->setSpeed(targetSpeed[3]);
    printf("Running!\n");
    printf("%f\n", lAngle);
    printf("%d %d %d %d\n", targetEncoder[0], targetEncoder[1], targetEncoder[2], targetEncoder[3]);
}

void SwerveDrive::driveSwerveRO(frc::XboxController *driverJoystick) {
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
    //the spinValue math determines how much to spin the robot proportional to the right joystick
    //it is always a fraction of  degrees towards the turn for the front motors, away from the turn for the back
    //this if statement is so that it is more efficient and the wheel never turns more than 180 degrees
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


void SwerveDrive::testHall(frc::XboxController *driverJoystick) {
  if ((*driverJoystick).GetAButton() == 1) {
    frontLeft->turnWheel360(90);
  }
  if ((*driverJoystick).GetBButton() == 1) {
    frontLeft->turnWheel360(-90);
  }
  if ((*driverJoystick).GetXButton() == 1) {
    frontRight->setSpeed(0.5);
  }
  else if ((*driverJoystick).GetYButton() == 1) {
    frontRight->setSpeed(-0.5);
  }
  else {
    frontRight->setSpeed(0);
  }
  //(*flTurn).Set(0.2*20000/25849);
  //(*frTurn).Set(0.2*20000/9635);
  //(*brTurn).Set(0.2*20000/19622);
  //(*blTurn).Set(0.2*20000/27311);
  //printf("%d %d %d %d\n", (*flHall).Get(), (*frHall).Get(), (*brHall).Get(), (*blHall).Get());
}

void SwerveDrive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
    SetDefaultCommand(new RunSwerve());
}
