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
			miButtonEventInterface* buttonEvent,
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
				buttonEvent,
				buttonType,
				false)
			, _Audio(audio)
			, _IsPlaying(false)
			, _Loop(waveloop)
			, _WaveName(name)
		{
			_Audio.addWave(_WaveName, _Loop);
		};

		virtual void ButtonDown(const std::string& name) override;
		virtual void ButtonUp(const std::string& name) override;
		virtual void ButtonToggle(bool state, const std::string& name) override;
		virtual void disableOutputs(bool disable) override;
		virtual bool componentProcess(int rootInterval, long tick) override;
	};


}