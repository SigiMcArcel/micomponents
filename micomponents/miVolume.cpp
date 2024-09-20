#include "miVolume.h"

void micomponents::miVolume::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
	double potValue = 0;
	potValue << value;
	_Volume.setVolume(potValue);
}
