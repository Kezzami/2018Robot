#include "Robot.h"

void Robot::TestInit()
{
	SmartDashboard::PutBoolean("Reset Angle", 0);
	SmartDashboard::PutBoolean("Reset Encoders", 0);

	//Maintain Angle Test
	SmartDashboard::PutNumber("Test Maintain Output", 0);
	SmartDashboard::PutBoolean("Enable Test Distance Output", 0);
	SmartDashboard::PutBoolean("Enable Maintain Controller", 0);
	SmartDashboard::PutBoolean("Toggle Maintain Test", 0);

	MaintainHeadingTest();
}

void Robot::TestPeriodic()
{
	BackRightMotor.Set(-DriveController.GetY(GenericHID::kLeftHand));
//	SmartDashboard::PutNumber("R Trigger Val", DriveController.GetTriggerAxis(GenericHID::kRightHand));
//	SmartDashboard::PutNumber("Auto Pos Val", (int) AutoLocationChooser->GetSelected());
//	SmartDashboard::PutNumber("Auto Obj Val", (int) AutoObjectiveChooser->GetSelected());
//
//	//Display Data
//	SmartDashboard::PutNumber("Angle Sensor", AngleSensors.GetAngle());
//	SmartDashboard::PutNumber("Encoder", FrontLeftMotor.GetSelectedSensorPosition(0));
//
//	//Reset Angle Button
//	if(SmartDashboard::GetBoolean("Reset Angle", 0))
//	{
//		AngleSensors.Reset();
//		SmartDashboard::PutBoolean("Rest Angle", 0);
//	}
//	//Reset Encoder Button
//	if(SmartDashboard::GetBoolean("Reset Encoders", 0))
//	{
//		ResetEncoders();
//		SmartDashboard::PutBoolean("Reset Encoders", 0);
//	}
//
//	//Maintain Angle Test Buttons
//	if(SmartDashboard::GetBoolean("Toggle Maintain Test", 0))
//	{
//		//Toggle the two buttons
//		SmartDashboard::PutBoolean("Enable Test Distance Output",
//				SmartDashboard::GetBoolean("Enable Test Distance Output", 0) ^ 1);
//		SmartDashboard::PutBoolean("Enable Maintain Controller",
//				SmartDashboard::GetBoolean("Enable Maintain Controller", 0) ^ 1);
//
//		SmartDashboard::PutBoolean("Toggle Test", 0);
//	}
//	if(SmartDashboard::GetBoolean("Enable Test Distance Output", 0))
//	{
//		AnglePIDOut.SetTestDistOutput(SmartDashboard::GetNumber(
//				"Test Maintain Output", 0));
//	}
//	else
//	{
//		AnglePIDOut.SetTestDistOutput(0);
//	}
//	if(SmartDashboard::GetBoolean("Enable Maintain Controller", 0))
//	{
//		MaintainAngleController.Enable();
//	}
//	else
//	{
//		MaintainAngleController.Disable();
//	}
}

void Robot::MaintainHeadingTest()
{
	//Disable other controllers
	AngleController.Disable();
	DistanceController.Disable();

	//Zeroing the angle sensor
	AngleSensors.Reset();

	//Remove the pointers since only one PID is being used
	DistancePID.SetAnglePID(nullptr);
	AnglePIDOut.SetDistancePID(nullptr);

	//Configure the PID controller to make sure the robot drives straight with the NavX
	MaintainAngleController.Reset();
	MaintainAngleController.SetSetpoint(0);
	MaintainAngleController.SetAbsoluteTolerance(0.5);
	MaintainAngleController.SetOutputRange(-1.0, 1.0);

	MaintainAngleController.Enable();
}

void Robot::DriveDistanceTest(double distance)
{
	//Disable other controllers
	AngleController.Disable();

	//Zeroing the angle sensor and encoders
	ResetEncoders();
	AngleSensors.Reset();

	//Disable test dist output for angle
	AnglePIDOut.SetTestDistOutput(0);

	//Make sure the PID objects know about each other to avoid conflicts
	DistancePID.SetAnglePID(&AnglePIDOut);
	AnglePIDOut.SetDistancePID(&DistancePID);

	//Configure the PID controller to make sure the robot drives straight with the NavX
	MaintainAngleController.Reset();
	MaintainAngleController.SetSetpoint(0);
	MaintainAngleController.SetAbsoluteTolerance(0.5);
	MaintainAngleController.SetOutputRange(-1.0, 1.0);

	//Configure the robot to drive a given distance
	DistanceController.Reset();
	DistanceController.SetSetpoint(distance);
	DistanceController.SetAbsoluteTolerance(1);
	DistanceController.SetOutputRange(-1.0, 1.0);

	MaintainAngleController.Enable();
	DistanceController.Enable();

	SmartDashboard::PutNumber("Target Distance", distance);
}


void Robot::TurnAngleTest(double angle)
{
	//Disable other controllers
	DistanceController.Disable();
	MaintainAngleController.Disable();

	//Zeroing the angle sensor
	AngleSensors.Reset();

	//Disable test dist output for angle
	AnglePIDOut.SetTestDistOutput(0);

	//Remove the pointers since only one PID is being used
	DistancePID.SetAnglePID(nullptr);
	AnglePIDOut.SetDistancePID(nullptr);

	AngleController.Reset();
	AngleController.SetSetpoint(angle);
	AngleController.SetAbsoluteTolerance(0.5);
	AngleController.SetOutputRange(-1.0, 1.0);
	AngleController.Enable();

	SmartDashboard::PutNumber("Target Angle", angle);
}

