#pragma once
#include <stdint.h>
#include <string>
#include "miLamp.h"
#include "miButton.h"
#include <mi/mimodules/ModuleBase.h>

namespace micomponents
{
	enum class ButtonType
	{
		PushButtonToggle, //click on, click off
		Switch,//button hold -> lamp on, button released lamp off
	};

	class miButtonLamp : public miButtonEventInterface, public miButton,public miLamp
	{
	protected:
		miButtonEventInterface* _ButtonEvent;
		std::string _Name;
		bool _LockButton;
		ButtonType _Behaviour;
		bool _EmergencyStop;

		// Geerbt über miButtonEventInterface
		virtual void ButtonDown(const std::string& name) override;
		virtual void ButtonUp(const std::string& name) override;
		virtual void ButtonClick(const std::string& name) override;
		virtual void ButtonToggle(bool state, const std::string& name) override;

		virtual void stopActivities() override
		{

		}

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
			: miButton(inputChannel, this, inverse,name + "_Button")
			, miLamp(lampType, flashTime, outputChannel, name + "_Lamp")
			, _ButtonEvent(buttonEvent)
			, _Name(name)
			, _Behaviour(buttonType)
			, _EmergencyStop(false)
		{
			
		};

		

		
	};
}

