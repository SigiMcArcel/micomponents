#pragma once
#include <string>

namespace micomponents
{
	class miLampInterface
	{
	public:
		virtual void lampControl(bool on) = 0;
		virtual void lampOn() = 0;
		virtual void lampOff() = 0;
		virtual const std::string name() = 0;
	};

	class miEmergenceStopInterface
	{
	public:
		virtual void emergencyStop(bool on) = 0;
	};

}

