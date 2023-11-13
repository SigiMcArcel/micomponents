#include "miLamp.h"

void micomponents::miLamp::eventOccured(void* sender, const std::string& name)
{
	
	if ("FlashTimer" == name)
	{
		if(_Type == LampType::Flash)
		{
			if (_LampState)
			{
				if ((_TimerIntervalCounter / 10) > _FlashTime)
				{
					if (_Toggle)
					{
						_Toggle = false;
					}
					else
					{
						_Toggle = true;
					}
					_OutputState = _Toggle;
				}
			}
			else
			{
				_OutputState = false;
				_Toggle = false;
			}
		}
		else if (_Type == LampType::Fix)
		{
			_OutputState = _LampState;
		}
		if (_LampControl)
		{
			_OutputState = true;
		}
		_OutputState >> _Channel->value();
	}
}
