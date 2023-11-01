#include "miLamp.h"

void micomponents::miLamp::eventOccured(void* sender, const std::string& name)
{
	if (_Override)
	{
		return;
	}
	if ("FlashTimer" == name)
	{
		if (_LampState)
		{
			if (_OutputState)
			{
				_OutputState = false;
			}
			else
			{
				_OutputState = true;
			}
		}
		else
		{
			_OutputState = false;
		}

	}
	_OutputState >> _Channel->value();
}
