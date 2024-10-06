#include "miButtonLamp.h"

const std::string micomponents::miButtonLamp::name()
{
	return _Name;
}

bool micomponents::miButtonLamp::componentProcess(int rootInterval, int tick)
{
	if (!miComponentBase::componentProcess(rootInterval, tick))
	{
		return false;
	}
	_LampDisable = _DisableOutputs;
	_LampControl = _Check;
	miButtonBase::handleButton(_Name);
	miLampBase::handleLamp();
	return true;
}

void micomponents::miButtonLamp::ButtonDown(const std::string& name)
{
	if (_Behaviour == ButtonType::Switch)
	{
		on();
		if (_ButtonEvent)
		{
			_ButtonEvent->ButtonDown(_Name);
		}
	}
}

void micomponents::miButtonLamp::ButtonUp(const std::string& name)
{
	if (_Behaviour == ButtonType::Switch)
	{
		off();
		if (_ButtonEvent)
		{
			_ButtonEvent->ButtonUp(_Name);
		}
	}
}

void micomponents::miButtonLamp::ButtonClick(const std::string& name)
{
	
}

void micomponents::miButtonLamp::ButtonToggle(bool state, const std::string& name)
{
	if (_Behaviour == ButtonType::PushButtonToggle)
	{
		if (state)
		{
			on();
		}
		else
		{
			off();
		}

		if (_ButtonEvent)
		{
			_ButtonEvent->ButtonToggle(state,_Name);
		}
	}
}




