// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMVictorSPX.h>
#include <frc/motorcontrol/PWMSparkMax.h>

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with tank steering and an Xbox controller.
 */
class Robot : public frc::TimedRobot {
  frc::PWMVictorSPX m_rightMotor{0};
  frc::PWMVictorSPX m_leftMotor{1};
  frc::PWMSparkMax fireMotor{2};
  frc::PWMVictorSPX hopperMotor{3};
  frc::PWMSparkMax inTakeMotor{4};
  frc::PWMVictorSPX armMotor{5};
  frc::DifferentialDrive m_robotDrive{m_leftMotor, m_rightMotor};
  frc::XboxController m_driverController{0};

  double fireSetPoint = 0.3;
  double hopperSetPoint = 0.3;
  double inTakeSetPoint = 0.4;
  double armSetPoint = 0.3;

 public:
  void RobotInit() override {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    m_rightMotor.SetInverted(true);
    fireMotor.SetInverted(true);
    armMotor.SetInverted(true);
  }

  void TeleopPeriodic() override {
    m_robotDrive.TankDrive(-m_driverController.GetLeftY(),
                           -m_driverController.GetRightY());

    fireMotor.Set(fireSetPoint * m_driverController.GetAButton());
    hopperMotor.Set(hopperSetPoint * m_driverController.GetBButton());
    inTakeMotor.Set(inTakeSetPoint * m_driverController.GetXButton());
    armMotor.Set(armSetPoint * m_driverController.GetYButton());
  }

};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
