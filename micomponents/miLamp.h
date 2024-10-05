#pragma once
#include <stdint.h>
#include <string>
#include "miLampBase.h"
#include "miComponentBase.h"

namespace micomponents
{
	class miLamp 
		:public miLampBase 
		,public miComponentBase
	{
	private:

	public:
		miLamp(const std::string& name,LampType lampType, int intervall,int flashTime, mimodule::ModuleChannel* channel)
			: miLampBase(flashTime,lampType,channel)
			, miComponentBase(name, intervall)
		{
			
		};

		virtual void lampOn() override;
		virtual void lampOff() override;
		virtual const std::string name() override;
		virtual bool componentProcess(int rootInterval, int tick) override;
	};
}

