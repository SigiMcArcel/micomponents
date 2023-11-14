#include "miLamp.h"

void micomponents::miLamp::eventOccured(void* sender, const std::string& name)
{
	
	if ("FlashTimer" == name)
	{
		if(_Type == LampType::Flash)
		{
			if (_LampState)
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
			else
			{
				_OutputState = false;
				_Toggle = false;
				_TimerIntervalCounter = 0;
			}
			if (_LampControl)
			{
				_OutputState = true;
			}
			if (_Channel == nullptr)
			{
				printf("miLamp invalid channel\n");
			}
			_OutputState >> _Channel->value();	
		}
		
		
	}
}
