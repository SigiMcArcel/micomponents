#include <mi/micomponents/miVolume.h>

void micomponents::miVolume::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
	uint16_t potValue = 0;
	potValue << value;
	double volume = (double)potValue / (double)1023 * (double)_MaxVolume;
	_Volume.setVolume(volume);
}
