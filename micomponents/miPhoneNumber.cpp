#include "miPhoneNumber.h"

void micomponents::miPhoneNumber::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
	if(!_DisableInputs)
		_PhoneNumber = value.getValue<uint32_t>();

	_PhoneNumberChanged = true;
}

bool micomponents::miPhoneNumber::componentProcess(int rootInterval, long tick)
{
	if (!miComponentBase::componentProcess(rootInterval, tick))
	{
		return false;
	}
	if (_PhoneNumberChanged)
	{
		_PhoneNumberChanged = false;
		if (_Callback)
		{
			_Callback->PhoneNumberchanged(_PhoneNumber);
		}
	}
	return true;
}


