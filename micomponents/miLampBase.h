#pragma once
#include <mi/miutils/Time.h>
#include <mi/mimodules/ModuleChannel.h>

namespace micomponents
{
	typedef enum class LampType_e
	{
		Flash,
		Fix
	}LampType;

	class miLampBase
	{
	protected:
		LampType _Type;
		bool _OutputState;
		bool _OutputStateLast;
		bool _LampState;
		bool _LampDisable;
		bool _Override;
		bool _OverrideState;
		mimodule::ModuleChannel* _Channel;
		bool _LampControl;
		bool _Toggle;
		int _FlashTime;
		miutils::Time _Time;

		void handleLamp();

	public:
		miLampBase(int flashTime, LampType lampType, mimodule::ModuleChannel* channel)
			: _Type(lampType)
			, _OutputState(false)
			, _OutputStateLast(false)
			, _LampState(false)
			, _LampDisable(false)
			, _Override(false)
			, _Channel(channel)
			, _LampControl(false)
			, _Toggle(false)
			, _FlashTime(flashTime)
			, _Time()
		{

		};
		virtual void on();
		virtual void off();
		virtual void overRide(bool override);
		virtual void lampOn();
		virtual void lampOff();
	};
}

