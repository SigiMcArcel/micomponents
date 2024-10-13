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

	class miButtonLamp 
		: public miComponentBase
		, public miButtonBase
		, public miLampBase
	{
	protected:
		bool _LockButton;
		ButtonType _Behaviour;
		bool _EmergencyStop;

	public:
		miButtonLamp(
			const std::string& name,
			int buttonHandleCyle,
			LampType lampType, 
			int flashTime, 
			mimodule::ModuleChannel* inputChannel, 
			mimodule::ModuleChannel* outputChannel,
			micomponents::miButtonEventInterface* buttonEvent, 
			ButtonType buttonType,
			bool inverse = false)
			: miComponentBase(name + "_Button", buttonHandleCyle)
			, miButtonBase(name + "_Button",inputChannel,buttonEvent, inverse) //name,channel,buttonEvent,inverse
			, miLampBase(flashTime,lampType, outputChannel)
			, _Behaviour(buttonType)
			, _EmergencyStop(false)
		{
			
		};

		virtual const std::string name() override;
		virtual void disableOutputs(bool disable) override;
		virtual void check(bool check) override;
		virtual bool componentProcess(int rootInterval, long tick) override;
		virtual void ButtonDown(const std::string& name) override;
		virtual void ButtonUp(const std::string& name) override;
		virtual void ButtonClick(const std::string& name) override;
		virtual void ButtonToggle(bool state, const std::string& name) override;
		virtual const std::string getValue(const std::string& name) override;
	};
}

