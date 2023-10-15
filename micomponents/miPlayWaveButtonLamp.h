#pragma once
#include "miButtonLamp.h"
#include <mi/misound/Wave.h>

namespace micomponents
{
	class miPlayWaveButtonLamp : public micomponents::miButtonLamp 
	{
	private:
		misound::Wave _Wave;
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
		{

		};

		virtual void ButtonOn() override;
		virtual void ButtonOff() override;

		
	};

}