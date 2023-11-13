#include "miPlayWaveButtonLamp.h"

void micomponents::miPlayWaveButtonLamp::ButtonDown(const std::string& name)
{
	miButtonLamp::ButtonDown(name);
	if (_Behaviour == ButtonType::Switch)
	{
		_Wave.play();
	}
}

void micomponents::miPlayWaveButtonLamp::ButtonUp(const std::string& name)
{
	miButtonLamp::ButtonUp(name);
	if (_Behaviour == ButtonType::Switch)
	{
		_Wave.stop();
	}
}

void micomponents::miPlayWaveButtonLamp::ButtonToggle(bool state, const std::string& name)
{
	miButtonLamp::ButtonToggle(state,_Name);
	if (_Behaviour == ButtonType::PushButtonToggle)
	{
		_Wave.stop();
	}
}

void micomponents::miPlayWaveButtonLamp::emergencyStop(bool on)
{
	_EmergencyStop = on;
	if (_EmergencyStop)
	{
		_Lamp.off();
	}
	else
	{
		bool state = _Button.getState();
		ButtonToggle(state,_Name);
		miButtonLamp::ButtonToggle(state,_Name);
		if (state)
		{
			ButtonDown(_Name);
			miButtonLamp::ButtonDown(_Name);
		}
		else
		{
			ButtonUp(_Name);
			miButtonLamp::ButtonUp(_Name);
		}

	}
}

// Geerbt über EventListener
void micomponents::miPlayWaveButtonLamp::eventOccured(void* sender, const std::string& name)
{
	if (_IsPlaying && !_Wave.isPlaying())
	{
		_Lamp.off();
		_IsPlaying = false;
		return;
	}
	if (!_IsPlaying && _Wave.isPlaying())
	{
		_IsPlaying = true;
	}
}