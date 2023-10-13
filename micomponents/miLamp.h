#pragma once
#include <stdint.h>
#include <string>
#include <mi/miutils/Timer.h>
#include <mi/mimodules/ModuleChannel.h>

namespace micomponents
{
	enum class LampType
	{
		Flash,
		Fix
	};

	class miLamp : public miutils::EventListener
	{
		

	private:
		LampType _Type;
		int32_t _FlashTime;
		miutils::Timer _FlashTimer;
		bool _OutputState;
		bool _LampState;
		mimodule::ModuleChannel* _Channel;
		bool _Test;
		std::string _Name;

	public:
		miLamp(LampType lampType, int32_t flashTime, mimodule::ModuleChannel* channel,const std::string& name)
			:_Type(lampType)
			, _FlashTime(flashTime)
			, _FlashTimer("FlashTimer", this)
			, _OutputState(false)
			, _LampState(false)
			, _Channel(channel)
			, _Test(false)
			, _Name(name)
		{
			if (_Type == LampType::Flash)
			{
				_FlashTimer.Start(_FlashTime, nullptr, 10, miutils::Schedulers::Other);
			}
		};

		void Test(bool on)
		{
			_Test = on;
			_Test >> _Channel->value();
		}

		void on()
		{
			if (_Test)
			{
				return;
			}
			_LampState = true;
			if (_Type == LampType::Fix)
			{
				_LampState >> _Channel->value();
			}
		}
		void off()
		{
			if (_Test)
			{
				return;
			}
			_LampState = false;
			if (_Type == LampType::Fix)
			{
				_LampState >> _Channel->value();
			}
		}


		// Geerbt über EventListener
		virtual void eventOccured(void* sender, const std::string& name) override;

	};
}

