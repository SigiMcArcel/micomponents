#pragma once
#include <stdint.h>
#include <string>
#include <mi/miutils/Timer.h>
#include <mi/mimodules/ModuleChannel.h>
#include "miComponentInterface.h"

namespace micomponents
{
	enum class LampType
	{
		Flash,
		Fix
	};

	class miLamp : public miutils::EventListener,public miLampInterface
	{
	private:

		const int32_t _TimerInterval = 10;
		LampType _Type;
		int32_t _FlashTime;
		int32_t _TimerIntervalCounter;
		miutils::Timer _FlashTimer;
		bool _OutputState;
		bool _LampState;
		mimodule::ModuleChannel* _Channel;
		bool _LampControl;
		bool _Toggle;
		std::string _Name;

	public:
		miLamp(LampType lampType, int32_t flashTime, mimodule::ModuleChannel* channel, const std::string& name)
			:_Type(lampType)
			, _FlashTime(flashTime)
			, _FlashTimer("FlashTimer", this)
			, _OutputState(false)
			, _LampState(false)
			, _Channel(channel)
			, _LampControl(false)
			, _Toggle(false)
			, _Name(name)
		{
			_FlashTimer.Start(_TimerInterval, nullptr, 10, miutils::Schedulers::Other);
		};

		~miLamp()
		{
			_FlashTimer.Stop();
		}

		virtual void lampControl(bool on)
		{
			_LampControl = on;
		}

		
		virtual void lampOn()
		{
			on();
		}
		virtual void lampOff()
		{
			off();
		}
		virtual const std::string name()
		{
			return _Name;
		}

		void on()
		{	
			_LampState = true;
		}

		void off()
		{
			_LampState = false;
		}

		


		// Geerbt �ber EventListener
		virtual void eventOccured(void* sender, const std::string& name) override;

	};
}

