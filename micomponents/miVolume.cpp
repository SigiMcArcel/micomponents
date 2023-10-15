#include "miVolume.h"

void micomponents::miVolume::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
	uint16_t potValue = 0;
	potValue << value;
	float volume = (float)potValue / (float)1023 * (float)100;
	_Volume.setVolume((int)volume);
}
