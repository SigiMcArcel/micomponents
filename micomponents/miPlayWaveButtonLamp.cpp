#include "miPlayWaveButtonLamp.h"

void micomponents::miPlayWaveButtonLamp::ButtonDown(const std::string& name)
{
	miButtonLamp::ButtonDown(name);
	on();
	_Audio.playWave(_WaveName,false, _Loop);
}

void micomponents::miPlayWaveButtonLamp::ButtonUp(const std::string& name)
{
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

void micomponents::miPlayWaveButtonLamp::disableOutputs(bool disable)
{
	miComponentBase::disableOutputs(disable);
	if (miComponentBase::_DisableOutputs)
	{
		_Audio.stopWave(_WaveName);
	}
	else
	{
		if (_ButtonState)
		{
			_Audio.playWave(_WaveName, false, _Loop);
		}
	}
}

bool micomponents::miPlayWaveButtonLamp::componentProcess(int rootInterval, int tick)
{
	if (!miButtonLamp::componentProcess(rootInterval, tick))
	{
		return false;
	}
	if (_Behaviour == ButtonType::PushButtonToggle)
	{
		if (_IsPlaying && !_Audio.isPlaying(_WaveName))
		{
			off();
			_IsPlaying = false;
		}
		else
		{
			if (!_IsPlaying && _Audio.isPlaying(_WaveName))
			{
				_IsPlaying = true;
			}
		}
	}
	return true;
}

