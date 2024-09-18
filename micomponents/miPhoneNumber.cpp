#include "miPhoneNumber.h"

void micomponents::miPhoneNumber::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
	if (_Callback)
	{
		int number = 0;
		number << value;
		_Callback->PhoneNumberchanged(number);
	}
}


