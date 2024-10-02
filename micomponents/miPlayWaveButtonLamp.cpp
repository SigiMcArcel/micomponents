#include "miPlayWaveButtonLamp.h"

void micomponents::miPlayWaveButtonLamp::ButtonDown(const std::string& name)
{
	printf("micomponents::miPlayWaveButtonLamp::ButtonDown %s\n", name.c_str());
	on();
	_Audio.playWave(_WaveName,false, _Loop);
	miButtonLamp::ButtonDown(name);
}

void micomponents::miPlayWaveButtonLamp::ButtonUp(const std::string& name)
{
	printf("micomponents::miPlayWaveButtonLamp::ButtonUp %s\n", name.c_str());
	
	miButtonLamp::ButtonUp(name);
	if (_Behaviour == ButtonType::Switch)
	{
		off();
		_Audio.stopWave(_WaveName);
	}
}

void micomponents::miPlayWaveButtonLamp::ButtonToggle(bool state, const std::string& name)
{
	//miButtonLamp::ButtonToggle(state,_Name);

}

