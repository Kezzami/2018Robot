#ifndef CONSTANTS
#define CONSTANTS

namespace consts
{
	enum class AutoPosition
	{
		LEFT_START,
		MIDDLE_START,
		RIGHT_START
	};

	enum class AutoObjective
	{
		SWITCH,
		SCALE,
		BASELINE,
		DEFAULT
	};

	enum class MiddleApproach
	{
		FRONT,
		SIDE
	};

	constexpr int PIDLoopIdx = 0;
	constexpr int timeoutMs = 10;

	constexpr double PI = 3.1416;
	constexpr double WHEEL_DIAMETER = 6;
	constexpr double PULSES_PER_REV = 4096;

	constexpr double GAME_DATA_TIMOUT_S = 1;
}

#endif
