#include "miComponentBase.h"

const std::string micomponents::miComponentBase::name()
{
	return _Name;
}

bool micomponents::miComponentBase::componentProcess(int rootInterval, long tick)
{
	if (_Intervall <= 0)
	{
		return true;
	}
	if (_Start)
	{
		return _Time.elapsed(_Intervall);
	}
	return false;
}

void micomponents::miComponentBase::componentStart()
{
	_Time.reset();
	_Start = true;
}
void micomponents::miComponentBase::componentStop()
{
	_Start = false;
}

void micomponents::miComponentBase::disableInputs(bool disable)
{
	_DisableInputs = disable;
}

void micomponents::miComponentBase::disableOutputs(bool disable)
{
	_DisableOutputs = disable;
}

void micomponents::miComponentBase::check(bool check)
{
	_Check = check;
}

const std::string micomponents::miComponentBase::getValue(const std::string& name)
{
	return std::string();
}
