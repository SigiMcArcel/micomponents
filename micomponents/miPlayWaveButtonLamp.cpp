#include "miPlayWaveButtonLamp.h"

void micomponents::miPlayWaveButtonLamp::ButtonDown(const std::string& name)
{
	printf("micomponents::miPlayWaveButtonLamp::ButtonDown %s\n", name.c_str());
	_Audio.playWave(_Name,false, _Loop);
	miButtonLamp::ButtonDown(name);
}

void micomponents::miPlayWaveButtonLamp::ButtonUp(const std::string& name)
{
	printf("micomponents::miPlayWaveButtonLamp::ButtonUp %s\n", name.c_str());
	miButtonLamp::ButtonUp(name);
	if (_Behaviour == ButtonType::Switch)
	{
		_Audio.stopWave(_Name);
	}
}

void micomponents::miPlayWaveButtonLamp::ButtonToggle(bool state, const std::string& name)
{
	//miButtonLamp::ButtonToggle(state,_Name);

}

// Geerbt über EventListener
void micomponents::miPlayWaveButtonLamp::eventOccured(void* sender, const std::string& name)
{
	if (_Behaviour == ButtonType::PushButtonToggle)
	{
		if (_IsPlaying && !_Audio.isPlaying(_Name))
		{
			off();
			_IsPlaying = false;
			return;
		}
		if (!_IsPlaying && _Audio.isPlaying(_Name))
		{
			_IsPlaying = true;
		}
	}
}