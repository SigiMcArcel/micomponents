#include "miLamp.h"

void micomponents::miLamp::disableOutputs(bool disable)
{
	bool val = false;
	miComponentBase::disableOutputs(disable);

	if (_DisableOutputs)
	{
		_LampDisable = true;
		if (_Channel == nullptr)
		{
			return;
		}
		_Channel->value().setValue(val);
	}
	else
	{
		_LampDisable = false;
		handleLamp();
	}
}

void micomponents::miLamp::check(bool check)
{
	bool val = true;
	miComponentBase::check(check);

	if (_Check)
	{
		_LampControl = true;
		if (_Channel == nullptr)
		{
			return;
		}
		_Channel->value().setValue(val);
	}
	else
	{
		_LampControl = false;
		handleLamp();
	}
}

const std::string micomponents::miLamp::name()
{
	return _Name;
}

bool micomponents::miLamp::componentProcess(int rootInterval, long tick)
{

	if (!miComponentBase::componentProcess(rootInterval, tick))
	{
		return false;
	}
	
	miLampBase::handleLamp();
	return true;
}