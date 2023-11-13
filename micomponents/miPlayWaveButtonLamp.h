#pragma once
#include "miButtonLamp.h"
#include <mi/misound/Wave.h>
#include <mi/miutils/Timer.h>

namespace micomponents
{
	class miPlayWaveButtonLamp : public micomponents::miButtonLamp, public miutils::EventListener, public miEmergenceStopInterface
	{
	private:
		misound::Wave _Wave;
		miutils::Timer _MonitoringTimer;
		bool _IsPlaying;
		
	public:
		miPlayWaveButtonLamp(
			LampType lampType,
			int32_t flashTime,
			mimodule::ModuleChannel* inputChannel,
			mimodule::ModuleChannel* outputChannel,
			const std::string& name,
			ButtonType buttonType,
			bool inverse,
			std::string wavePath,
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
			, _Wave(wavePath + std::string("/") + name + std::string(".wav"), name, waveloop)
			, _MonitoringTimer("Monitring",this )
			, _IsPlaying(false)
		{
			_MonitoringTimer.Start(20);
		};

		~miPlayWaveButtonLamp()
		{
			_MonitoringTimer.Stop();
		};
		

		void ButtonDown(const std::string& name) override;
		void ButtonUp(const std::string& name) override;
		void ButtonToggle(bool state, const std::string& name) override;
	
		// Geerbt über miEmergenceStopInterface
		virtual void emergencyStop(bool on) override;
		void eventOccured(void* sender, const std::string& name) override;

	};

}