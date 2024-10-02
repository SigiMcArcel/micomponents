#pragma once
#include "miButtonLamp.h"
#include <mi/misound/Audio.h>

namespace micomponents
{
	class miPlayWaveButtonLamp
		: public micomponents::miButtonLamp
	{
	private:
		misound::AudioInterface& _Audio;
		bool _IsPlaying;
		bool _Loop;
		std::string _WaveName;

	public:
		miPlayWaveButtonLamp(
			const std::string& name,
			int buttonHandleCyle,
			LampType lampType,
			int flashTime,
			mimodule::ModuleChannel* inputChannel,
			mimodule::ModuleChannel* outputChannel,
			ButtonType buttonType,
			misound::AudioInterface& audio,
			bool inverse,
			bool waveloop
		)
			:miButtonLamp(
				name,
				buttonHandleCyle,
				lampType,
				flashTime,
				inputChannel,
				outputChannel,
				nullptr,
				buttonType,
				false)
			, _Audio(audio)
			, _IsPlaying(false)
			, _Loop(waveloop)
			, _WaveName(name)
		{
			_Audio.addWave(_WaveName, _Loop);
		};

		~miPlayWaveButtonLamp()
		{

		};


		virtual void ButtonDown(const std::string& name) override;
		virtual void ButtonUp(const std::string& name) override;
		virtual void ButtonToggle(bool state, const std::string& name) override;

		virtual void disableOutputs(bool disable) override
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

		virtual bool componentProcess(int rootInterval, int tick) override
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

	};


}