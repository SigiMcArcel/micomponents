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
		

	private:
		miLamp _Lamp;
		miButtonEventInterface* _ButtonEvent;
		std::string _Name;

	public:
		miButtonLamp(LampType lampType, 
			int32_t flashTime, 
			mimodule::ModuleChannel* inputChannel, 
			mimodule::ModuleChannel* outputChannel,
			micomponents::miButtonEventInterface* buttonEvent, 
			const std::string& name, 
			bool inverse = false)
			:miButton(inputChannel, this, inverse,name + "_Button")
			, _Lamp(lampType, flashTime, outputChannel, name + "_Lamp")
			, _ButtonEvent(buttonEvent)
			, _Name(name)
		{
			
		};



		// Geerbt über miButtonEventInterface

		virtual void ButtonOn() override;

		virtual void ButtonOff() override;

	};
}

