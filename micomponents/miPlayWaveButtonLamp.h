#pragma once
#include "miButtonLamp.h"
#include <mi/misound/Audio.h>
#include <mi/miutils/Timer.h>

namespace micomponents
{
	class miPlayWaveButtonLamp : public micomponents::miButtonLamp
	{
	private:
		misound::Audio _Audio;
		miutils::Timer _MonitoringTimer;
		bool _IsPlaying;
		bool _Loop;
		
	public:
		miPlayWaveButtonLamp(
			LampType lampType,
			int32_t flashTime,
			mimodule::ModuleChannel* inputChannel,
			mimodule::ModuleChannel* outputChannel,
			const std::string& name,
			ButtonType buttonType,
			const misound::Audio& audio,
			bool inverse,
			bool waveloop
		)
			:miButtonLamp(
				lampType,
				flashTime,
				inputChannel,
				outputChannel,
				nullptr,
				name,
				buttonType,
				false)
			, _Audio(audio)
			, _MonitoringTimer("Monitoring",this )
			, _IsPlaying(false)
			, _Loop(waveloop)
		{
			_Audio.addWave(_Name,  _Loop);
			_MonitoringTimer.Start(20);
		};

		~miPlayWaveButtonLamp()
		{
			_MonitoringTimer.Stop();
		};
		

		void ButtonDown(const std::string& name) override;
		void ButtonUp(const std::string& name) override;
		void ButtonToggle(bool state, const std::string& name) override;
	
		void stopActivities() override
		{
			_Audio.stopWave(_Name);
		}
		void eventOccured(void* sender, const std::string& name) override;

	};


}