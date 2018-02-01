#include "Robot.h"

void Robot::AutonomousInit()
{
	SmartDashboard::PutBoolean("Robot at Left Position",  false);
	SmartDashboard::PutBoolean("Robot at Middle Position", false);
	SmartDashboard::PutBoolean("Robot at Right Position", false);
	SmartDashboard::PutNumber("Delay", 0);

	std::string gameData;
	DriverStation::GetInstance().WaitForData();
	gameData = DriverStation::GetInstance().GetGameSpecificMessage();

	double delayTime = SmartDashboard::GetNumber("Delay", 0);
//	Wait(delayTime);

	if(gameData[0] == 'L') // if left side switch
	{
		if(SmartDashboard::GetBoolean("Robot at Left Position", false)) // if robot on left side
		{

		}
		else if(SmartDashboard::GetBoolean("Robot at Middle Position", false)) // if robot on middle side
		{

		}
		else if(SmartDashboard::GetBoolean("Robot at Right Position", false)) // if robot on right side
		{

		}
	}
	else if(gameData[0] == 'R')  // if right side switch
	{
		if(SmartDashboard::GetBoolean("Robot at Left Position", false)) // if robot on left side
		{

		}
		else if(SmartDashboard::GetBoolean("Robot at Middle Position", false)) // if robot on middle side
		{

		}
		else if(SmartDashboard::GetBoolean("Robot at Right Position", false)) // if robot on right side
		{

		}
	}

	SmartDashboard::PutNumber("Gyro", Gyro.GetAngle());
	SmartDashboard::PutNumber("Encoder", PulsesToInches(FrontLeftMotor.GetSelectedSensorPosition(0)));

	DriveForward(36);
}


void Robot::AutonomousPeriodic()
{
	SmartDashboard::PutNumber("Gyro", Gyro.GetAngle());
	SmartDashboard::PutNumber("Encoder", PulsesToInches(FrontLeftMotor.GetSelectedSensorPosition(0)));
}

void Robot::DriveForward(double distance)
{
	// Zeroing the gyros and encoders
	FrontLeftMotor.SetSelectedSensorPosition(0, 0, 10);
	Gyro.Reset();

	//Make sure the PID objects know about each other to avoid conflicts
	DistancePID.SetAnglePID(&AnglePIDOut);
	AnglePIDOut.SetDistancePID(&DistancePID);

	//Configure the PID controller to make sure the robot drives straight with the Gyro
	MaintainAngleController.Reset();
	MaintainAngleController.SetSetpoint(0);
	MaintainAngleController.SetPercentTolerance(1);

	//Configure the robot to drive a given distance
	DistanceController.Reset();
	DistanceController.SetSetpoint(distance);
	DistanceController.SetPercentTolerance(1);

	MaintainAngleController.Enable();
	DistanceController.Enable();

	SmartDashboard::PutNumber("Target Distance", distance);
	SmartDashboard::PutNumber("Encoder", PulsesToInches(FrontLeftMotor.GetSelectedSensorPosition(0)));
}

void Robot::TurnAngle(double angle)
{
	Gyro.Reset();

	//Remove the pointers since only one PID is being used
	DistancePID.SetAnglePID(nullptr);
	AnglePIDOut.SetDistancePID(nullptr);

	AngleController.Reset();
	AngleController.SetSetpoint(angle);
	AngleController.SetPercentTolerance(1);

	AngleController.Enable();

	SmartDashboard::PutNumber("Target Angle", angle);
	SmartDashboard::PutNumber("Angle", Gyro.GetAngle());
}

void Robot::DriveFor(double seconds, double speed = 0.5)
{
	DriveTrain.ArcadeDrive(speed, 0);
	Wait(seconds);
	DriveTrain.ArcadeDrive(0, 0);
}

