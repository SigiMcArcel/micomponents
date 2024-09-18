#pragma once
#include <mi/mimodules/ModuleMiPhoneNumber.h>
#include "miComponentInterface.h"

namespace micomponents
{
	class miPhoneNumber : public mimodule::ModuleValueChangedEvent
	{
	private:
		mimodule::ModuleChannel* _Channel;
		micomponents::miPhoneNumberInterface *_Callback;

	public:
		miPhoneNumber(mimodule::ModuleChannel* channel, int intervall, micomponents::miPhoneNumberInterface* callback)
			:_Channel(channel)
			, _Callback(callback)
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


