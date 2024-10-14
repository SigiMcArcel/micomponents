#pragma once
#include <mi/mimodules/ModuleMiPotentiometer.h>
#include <mi/misound/Audio.h>
#include "miComponentBase.h"

namespace micomponents
{
	class miAudio 
		: public mimodule::ModuleValueChangedEvent
		, public micomponents::miComponentBase
	{

	private:
		misound::Audio& _Audio;
		mimodule::ModuleChannel* _VolumeChannel;
		mimodule::ModuleChannel* _PhoneJackChannel;
		std::string _Soundcard1;
		std::string _Soundcard2;
		double _PotentiometerValue;
		bool _PotentiometerValueChanged;
		bool _PhoneJackState;
		bool _PhoneJackStateChanged;

	public:
		miAudio(
			const std::string name,
			int intervall,
			mimodule::ModuleChannel* volumeChannel,
			mimodule::ModuleChannel* phoneJackChannel,
			misound::Audio& audio,
			double maxVolume,
			const std::string& soundCard1,
			const std::string& soundCard2)
			: miComponentBase(name,intervall)
			, _Audio(audio)
			, _VolumeChannel(volumeChannel)
			, _PhoneJackChannel(phoneJackChannel)
			, _Soundcard1(soundCard1)
			, _Soundcard2(soundCard2)
			, _PotentiometerValue(0.0)
			, _PhoneJackState(false)
		{
			
			_VolumeChannel->registerChannelEvent(this,true);
			_PhoneJackChannel->registerChannelEvent(this,true);
			
		}

		virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override;
		virtual bool componentProcess(int rootInterval, long tick) override;
		virtual const std::string getValue(const std::string& name) override;
	};
}


