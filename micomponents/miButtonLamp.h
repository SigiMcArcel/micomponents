#pragma once
#include <stdint.h>
#include <string>
#include <mi/miutils/Timer.h>
#include "miLamp.h"
#include "miButton.h"
#include <mi/mimodules/ModuleBase.h>

namespace micomponents
{
	class miButtonLamp : public miButton, public micomponents::miButtonEventInterface
	{
		

	protected:
		miLamp _Lamp;
		miButtonEventInterface* _ButtonEvent;
		std::string _Name;
		bool _LockButton;

	public:
		miButtonLamp(
			LampType lampType, 
			int32_t flashTime, 
			mimodule::ModuleChannel* inputChannel, 
			mimodule::ModuleChannel* outputChannel,
			micomponents::miButtonEventInterface* buttonEvent, 
			const std::string& name, 
			ButtonType buttonType,
			bool inverse = false)
			:miButton(inputChannel, this, inverse,name + "_Button",buttonType)
			, _Lamp(lampType, flashTime, outputChannel, name + "_Lamp")
			, _ButtonEvent(buttonEvent)
			, _Name(name)
		{
			
		};

		virtual void Lock(bool lock)
		{
			_LockButton = lock;
		}

		void LampOn()
		{
			_Lamp.on();
		}

		void LampOff()
		{
			_Lamp.on();
		}


		// Geerbt über miButtonEventInterface

		virtual void ButtonOn() override;

		virtual void ButtonOff() override;

	};
}

