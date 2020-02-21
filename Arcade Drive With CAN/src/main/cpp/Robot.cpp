/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include "rev/CANSparkMax.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <math.h>

#include <fstream>

class Robot : public frc::TimedRobot {
  /*
   * SPARK MAX controllers are intialized over CAN by constructing a CANSparkMax object
   * 
   * The CAN ID, which can be configured using the SPARK MAX Client, is passed as the
   * first parameter
   * 
   * The motor type is passed as the second parameter. Motor type can either be:
   *  rev::CANSparkMax::MotorType::kBrushless
   *  rev::CANSparkMax::MotorType::kBrushed
   * 
   * The example below initializes four brushless motors with CAN IDs 1, 2, 3 and 4. Change
   * these parameters to match your setup
   */
  static const int leftLeadDeviceID = 14, rightLeadDeviceID = 15; // leftFollowDeviceID = 13, rightFollowDeviceID = 12;
  rev::CANSparkMax* m_leftLeadMotor = new rev::CANSparkMax(leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless); // m_leftLeadMotor{leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax* m_rightLeadMotor = new rev::CANSparkMax(rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless); // rev::CANSparkMax m_rightLeadMotor{rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  //rev::CANSparkMax m_leftFollowMotor{leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  //rev::CANSparkMax m_rightFollowMotor{rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};

  /**
   * In RobotInit() below, we will configure m_leftFollowMotor and m_rightFollowMotor to follow 
   * m_leftLeadMotor and m_rightLeadMotor, respectively. 
   * 
   * Because of this, we only need to pass the lead motors to m_robotDrive. Whatever commands are 
   * sent to them will automatically be copied by the follower motors
   */

  rev::CANEncoder m_encoder_left_motor = m_leftLeadMotor->GetEncoder();
  rev::CANEncoder m_encoder_right_motor = m_rightLeadMotor->GetEncoder();
  

  // frc::DifferentialDrive m_robotDrive = new frc::DifferentialDrive(m_leftLeadMotor, m_rightLeadMotor);


  frc::Joystick m_stick{0};

  double joystickX, joystickY;
  int exponent = 2;
  int coefficient = 1;
  int currentLimit = 40;


 /* std::ifstream joystickValues("joystickvalues.json", std::ifstream::binary);*/
  
 public:

  void RobotInit() {

    m_leftLeadMotor->SetSmartCurrentLimit(40);
    m_rightLeadMotor->SetSmartCurrentLimit(40);

    m_leftLeadMotor->SetSecondaryCurrentLimit(60, 50);
    m_rightLeadMotor->SetSecondaryCurrentLimit(60, 50);

    // m_LeftLeadMotor->SetInverted(true);
    // m_RightLeadMotor->SetInverted(true);
    
    /**
     * The RestoreFactoryDefaults method can be used to reset the configuration parameters
     * in the SPARK MAX to their factory default state. If no argument is passed, these
     * parameters will not persist between power cycles
     */
    //m_leftLeadMotor.RestoreFactoryDefaults();
    //m_rightLeadMotor.RestoreFactoryDefaults();
    //m_leftFollowMotor.RestoreFactoryDefaults();
    //m_rightFollowMotor.RestoreFactoryDefaults();
    
    /**
     * In CAN mode, one SPARK MAX can be configured to follow another. This is done by calling
     * the Follow() method on the SPARK MAX you want to configure as a follower, and by passing
     * as a parameter the SPARK MAX you want to configure as a leader.
     * 
     * This is shown in the example below, where one motor on each side of our drive train is
     * configured to follow a lead motor.
     */
    //m_leftFollowMotor.Follow(m_leftLeadMotor);
    //m_rightFollowMotor.Follow(m_rightLeadMotor);
    
  }

  void TeleopPeriodic() {
    // Drive with arcade style//
    

    joystickX = m_stick.GetX();
    joystickY = m_stick.GetY();

    int exponent = 2;
    int coefficient = 1;

    double squareX = pow(joystickX, exponent);
    double squareY = pow(joystickY, exponent);

    double leftMotorOutput = coefficient * squareX;
    double rightMotorOutput = coefficient * squareY;

    // not taking care of negative numbers -- fix that


    frc::DifferentialDrive SetDeadband();

    m_leftLeadMotor->Set(leftMotorOutput);
    m_rightLeadMotor->Set(rightMotorOutput);

    double leftMotorVelocity = m_encoder_left_motor.GetVelocity();
    double rightMotorVelocty = m_encoder_right_motor.GetVelocity();

    frc::SmartDashboard::PutNumber("Joystick X value", leftMotorVelocity);
    frc::SmartDashboard::PutNumber("Joystick Y value", rightMotorVelocty);




   

  }

};




#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif