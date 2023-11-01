#pragma once
#include <mi/mimodules/ModuleMiPotentiometer.h>
#include <mi/misound/Alsa.h>

namespace micomponents
{
	class miVolume : public mimodule::ModuleValueChangedEvent
	{
	private:
		misound::AlsaVolume _Volume;
		mimodule::ModuleChannel* _Channel;
		double _MaxVolume;
		

	public:
		miVolume(mimodule::ModuleChannel* channel, int intervall, double maxVolume)
			: _Volume(intervall)
			, _Channel(channel)
			, _MaxVolume(maxVolume)
		{
			if (_Channel != nullptr)
			{
				_Channel->registerChannelEvent(this);
			}
		}

		// Geerbt über ModuleValueChangedEvent
		virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override;
	};
}


