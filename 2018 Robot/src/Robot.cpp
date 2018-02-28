#include "Robot.h"

Robot::Robot() :
	BackRightMotor(2),
	FrontRightMotor(1),
	FrontLeftMotor(0),
	BackLeftMotor(1),
//	LinkageMotor(5),
	RightIntakeMotor(6),
//	ClimbMotor(7),
	ElevatorMotor(8),
	LeftIntakeMotor(9),
	LeftMotors(FrontRightMotor, BackLeftMotor),
	RightMotors(FrontRightMotor, BackRightMotor),
	DriveController(0),
	DriveTrain(LeftMotors, RightMotors),
	AngleSensors(SPI::Port::kMXP, SPI::kOnboardCS0),

	AnglePIDOut(DriveTrain),
	DistancePID(BackRightMotor, DriveTrain),
	AngleController(0.02525, 0, 0.025, AngleSensors, AnglePIDOut), // (0.02525, 0, 0.025)
	MaintainAngleController(0.03, 0.0015, 0.05, AngleSensors, AnglePIDOut), // (0.03, 0.0025, 0)
	DistanceController(0.0225, 0, 0.005, DistancePID, DistancePID), // ()

	ElevatorPID(&ElevatorMotor),
	ElevatorPIDController(0.25, 0, 0, ElevatorPID, ElevatorPID)
{
	AutoLocationChooser = new SendableChooser<consts::AutoPosition>();
	AutoObjectiveChooser = new SendableChooser<consts::AutoObjective>();
	SwitchApproachChooser = new SendableChooser<consts::SwitchApproach>();
}

Robot::~Robot()
{
	delete AutoLocationChooser;
	delete AutoObjectiveChooser;
	delete SwitchApproachChooser;
}

void Robot::RobotInit()
{
	// Configuring the Talon Drive Encoders
	BackRightMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, consts::PID_LOOP_ID, consts::TALON_TIMEOUT_MS);
	BackRightMotor.SetSensorPhase(true);
	BackLeftMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, consts::PID_LOOP_ID, consts::TALON_TIMEOUT_MS);
	BackLeftMotor.SetSensorPhase(true);

	// Adding PID Controllers to LiveWindow
	LiveWindow::GetInstance()->Add(&AngleController);
	LiveWindow::GetInstance()->Add(&MaintainAngleController);
	LiveWindow::GetInstance()->Add(&DistanceController);

	// Configuring Angle PID Controller
	AngleController.SetAbsoluteTolerance(1);
	AngleController.SetOutputRange(-1.0, 1.0);

	// Configuring Maintain Angle PID Controller
	MaintainAngleController.SetAbsoluteTolerance(0.5);
	MaintainAngleController.SetOutputRange(-1.0, 1.0);

	// Configuring Distance PID Controller
	DistanceController.SetPercentTolerance(3);
	DistanceController.SetOutputRange(-0.80, 0.80);
}

void Robot::ResetEncoders()
{
	BackLeftMotor.SetSelectedSensorPosition(0, consts::PID_LOOP_ID, consts::TALON_TIMEOUT_MS);
	BackRightMotor.SetSelectedSensorPosition(0, consts::PID_LOOP_ID, consts::TALON_TIMEOUT_MS);
}


START_ROBOT_CLASS(Robot)
