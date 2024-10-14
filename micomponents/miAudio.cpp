#include "miAudio.h"

void micomponents::miAudio::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
	if (id == "Potentiometer")
	{
		_PotentiometerValue =  value.getValue<double>();
		_PotentiometerValueChanged = true;
		
	}
	if (id == "GPIO5")
	{
		_PhoneJackState = value.getValue<bool>();
		_PhoneJackStateChanged = true;
	}
}

bool micomponents::miAudio::componentProcess(int rootInterval, long tick)
{
	if (!miComponentBase::componentProcess(rootInterval, tick))
	{
		return false;
	}
	if (_PhoneJackStateChanged)
	{
		_PhoneJackStateChanged = false;
		if (_PhoneJackState)
		{
			_Audio.changeSoundcard(_Soundcard1);
		}
		else
		{
			_Audio.changeSoundcard(_Soundcard2);
		}
	}

	if (_PotentiometerValueChanged)
	{
		_PotentiometerValueChanged = false;
		_Audio.setVolume(_PotentiometerValue);
	}
	return true;
}

const std::string micomponents::miAudio::getValue(const std::string& name)
{
	if (name == "Potentiometer")
	{
		return std::to_string(_PotentiometerValue);
	}
	else if (name == "PhoneJackState")
	{
		return std::to_string(_PhoneJackState);
	}
	return std::string();
}
