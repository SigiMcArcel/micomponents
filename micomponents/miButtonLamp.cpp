#include "miButtonLamp.h"

const std::string micomponents::miButtonLamp::name()
{
	return _Name;
}

bool micomponents::miButtonLamp::componentProcess(int rootInterval, long tick)
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

const std::string micomponents::miButtonLamp::getValue(const std::string& name)
{
	if (name == "ButtonState")
	{
		return std::to_string(_ButtonState);
	}
	return std::string();
}

void micomponents::miButtonLamp::disableOutputs(bool disable)
{
	bool val = false;
	miComponentBase::disableOutputs(disable);

	if (_DisableOutputs)
	{
		_LampDisable = true;
		if (miLampBase::_Channel == nullptr)
		{
			return;
		}
		miLampBase::_Channel->value().setValue(val);
	}
	else
	{
		_LampDisable = false;
		handleLamp();
	}
}

void micomponents::miButtonLamp::check(bool check)
{
	bool val = true;
	miComponentBase::check(check);
	
	if (_Check)
	{
		_LampControl = true;
		if (miLampBase::_Channel == nullptr)
		{
			return;
		}
		miLampBase::_Channel->value().setValue(val);
	}
	else
	{
		_LampControl = false;
		handleLamp();
	}
}




