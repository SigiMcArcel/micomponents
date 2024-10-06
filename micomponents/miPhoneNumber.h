#pragma once
#include <mi/mimodules/ModuleMiPhoneNumber.h>
#include "miComponentBase.h"

namespace micomponents
{
	class miPhoneNumberInterface
	{
	public:
		virtual void PhoneNumberchanged(int number) = 0;
	};

	typedef std::shared_ptr<miPhoneNumberInterface> miPhoneNumberShared;

	class miPhoneNumber 
		: public mimodule::ModuleValueChangedEvent
		, public miComponentBase
	{
	private:
		mimodule::ModuleChannel* _Channel;
		micomponents::miPhoneNumberInterface *_Callback;
		int _PhoneNumber;
		bool _PhoneNumberChanged;

	public:
		miPhoneNumber(const std::string name, int intervall, mimodule::ModuleChannel* channel, micomponents::miPhoneNumberInterface* callback)
			: miComponentBase(name,intervall)
			,_Channel(channel)
			, _Callback(callback)
			,_PhoneNumber(0)
			,_PhoneNumberChanged(false)
		{
			if (_Channel != nullptr)
			{
				_Channel->registerChannelEvent(this,false);
			}
		}

		// Geerbt über ModuleValueChangedEvent
		virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override;
		virtual bool componentProcess(int rootInterval, int tick) override;
	};
}


