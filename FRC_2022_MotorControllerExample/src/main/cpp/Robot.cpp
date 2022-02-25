// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/XboxController.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <time.h>

/**
 * This sample program shows how to control a motor using a joystick. In the
 * operator control part of the program, the joystick is read and the value is
 * written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as
 * range from -1 to 1 making it easy to work together.
 */
class Robot : public frc::TimedRobot {
 public:
  void TeleopPeriodic() override { 
    //left_motor.Set(m_controller.GetLeftY());
    right_motor.Set(m_controller.GetLeftX()); 
    }

  void AutonomousInit() override{
    autoTimeStamp = time(NULL);
  }

  void AutonomousPeriodic() override{
    if(autoTimeStamp + delay > time(NULL)){
      right_motor.Set(maxSpeed);
      left_motor.Set(-maxSpeed);
    }
    else if(autoTimeStamp + (delay * 2) > time(NULL)){
      right_motor.Set(-maxSpeed);
      left_motor.Set(maxSpeed);
    }else{
      right_motor.Set(0);
      left_motor.Set(0);
    }
  }

 private:
  //frc::Joystick m_stick{0};
  frc::XboxController m_controller{0};
  frc::PWMSparkMax left_motor{0};
  frc::PWMSparkMax right_motor{1};
  time_t autoTimeStamp;
  time_t delay = 2;
  double maxSpeed = 0.15;
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
