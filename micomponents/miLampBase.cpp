#include "miLampBase.h"

void micomponents::miLampBase::handleLamp()
{
	if (!_Time.elapsed(_FlashTime))
	{
		return;
	}

	if (_Channel == nullptr)
	{
		return;
	}

	if (_Type == LampType::Flash)
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
		}
	}
	else if (_Type == LampType::Fix)
	{
		_OutputState = _LampState;
	}

	if (!_Override && !_LampControl && !_LampDisable)
	{
		_Channel->value().setValue(_OutputState);
	}
}

void micomponents::miLampBase::on()
{
	_LampState = true;
}

void micomponents::miLampBase::off()
{
	_LampState = false;
}

void micomponents::miLampBase::overRide(bool overRide)
{
	_Override = overRide;
	if (!_Override)
	{
		handleLamp();
	}
}

void micomponents::miLampBase::lampOn()
{
	bool val = true;
	if (_Override)
	{
		if (_Channel == nullptr)
		{
			return;
		}
		_Channel->value().setValue(val);
	}
	else
	{
		on();
	}
}

void micomponents::miLampBase::lampOff()
{
	bool val = false;
	if (_Override)
	{
		if (_Channel == nullptr)
		{
			return;
		}
		_Channel->value().setValue(val);
	}
	else
	{
		off();
	}
}
