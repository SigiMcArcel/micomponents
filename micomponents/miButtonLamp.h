#pragma once
#include <stdint.h>
#include <string>
#include "miLamp.h"
#include "miButton.h"
#include "miComponentInterface.h"
#include <mi/mimodules/ModuleBase.h>

namespace micomponents
{
	enum class ButtonType
	{
		PushButtonToggle, //click on, click off
		Switch,//button hold -> lamp on, button released lamp off
	};

	class miButtonLamp : public miButtonEventInterface, public miLampInterface
	{
	protected:
		miButton _Button;
		miLamp _Lamp;
		miButtonEventInterface* _ButtonEvent;
		std::string _Name;
		bool _LockButton;
		ButtonType _Behaviour;
		bool _EmergencyStop;

		void LampHandler();

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
			: _Button(inputChannel, this, inverse,name + "_Button")
			, _Lamp(lampType, flashTime, outputChannel, name + "_Lamp")
			, _ButtonEvent(buttonEvent)
			, _Name(name)
			, _Behaviour(buttonType)
			, _EmergencyStop(false)
		{
			
		};

		// Geerbt über miButtonEventInterface
		virtual void ButtonDown(const std::string& name) override;
		virtual void ButtonUp(const std::string& name) override;
		virtual void ButtonClick(const std::string& name) override;
		virtual void ButtonToggle(bool state, const std::string& name) override;

		// Geerbt über miLampControlInterface
		virtual void lampControl(bool on);
		virtual void lampOn() override
		{
			_Lamp.on();
		}
		virtual void lampOff()  override
		{
			_Lamp.off();
		}
		virtual const std::string name() override
		{
			return _Name;
		}
	};
}

