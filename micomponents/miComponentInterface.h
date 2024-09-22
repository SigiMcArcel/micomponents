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

	class miButtonInterface
	{
	public:
		virtual void disableButtonEvent(bool on) = 0;
		virtual void stopActivities() = 0;
		virtual const std::string name() = 0;
	};

	class miPhoneNumberInterface
	{
	public:
		virtual void PhoneNumberchanged(int number) = 0;
	};

}

