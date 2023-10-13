#include <mi/micomponents/miButtonLamp.h>

void micomponents::miButtonLamp::ButtonOn()
{
	_Lamp.on();
	if (_ButtonEvent)
	{
		_ButtonEvent->ButtonOn();
	}
}

void micomponents::miButtonLamp::ButtonOff()
{
	_Lamp.off();
	if (_ButtonEvent)
	{
		_ButtonEvent->ButtonOff();
	}
}
