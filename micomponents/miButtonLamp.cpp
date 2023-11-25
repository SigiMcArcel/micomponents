#include "miButtonLamp.h"

void micomponents::miButtonLamp::LampHandler()
{
}

void micomponents::miButtonLamp::ButtonDown(const std::string& name)
{
	//printf("miButtonLamp::ButtonDown %s\n", name.c_str());
	_Lamp.on();
	if (_ButtonEvent)
	{
		_ButtonEvent->ButtonDown(_Name);
	}
}

void micomponents::miButtonLamp::ButtonUp(const std::string& name)
{
	if (_Behaviour == ButtonType::Switch)
	{
		_Lamp.off();
		if (_ButtonEvent)
		{
			_ButtonEvent->ButtonUp(_Name);
		}
	}
}

void micomponents::miButtonLamp::ButtonClick(const std::string& name)
{
	;
}
void micomponents::miButtonLamp::ButtonToggle(bool state, const std::string& name)
{
	//printf("miButtonLamp::ButtonTogglel %s = %d\n", name.c_str(), state);
	if (_Behaviour == ButtonType::PushButtonToggle)
	{
		if (state)
		{
			_Lamp.on();
		}
		else
		{
			_Lamp.off();
		}

		if (_ButtonEvent)
		{
			_ButtonEvent->ButtonToggle(state,_Name);
		}
	}
}

void micomponents::miButtonLamp::lampControl(bool on)
{
	_Lamp.lampControl(on);
}




