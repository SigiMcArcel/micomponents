#include "miButtonLamp.h"

void micomponents::miButtonLamp::ButtonOn()
{
	if (_LockButton)
	{
		return;
	}
	_Lamp.on();
	if (_ButtonEvent)
	{
		_ButtonEvent->ButtonOn();
	}
}

void micomponents::miButtonLamp::ButtonOff()
{
	if (_LockButton)
	{
		return;
	}
	_Lamp.off();
	if (_ButtonEvent)
	{
		_ButtonEvent->ButtonOff();
	}
}
