#include "miLamp.h"

void micomponents::miLamp::lampOn()
{
	on();
}

void micomponents::miLamp::lampOff()
{
	off();
}

const std::string micomponents::miLamp::name()
{
	return _Name;
}

bool micomponents::miLamp::componentProcess(int rootInterval, int tick)
{

	if (!miComponentBase::componentProcess(rootInterval, tick))
	{
		return false;
	}
	_LampDisable = _DisableOutputs;
	_LampControl = _Check;
	miLampBase::handleLamp();
	return true;
}