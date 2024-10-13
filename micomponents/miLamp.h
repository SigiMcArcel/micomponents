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
		virtual void disableOutputs(bool disable) override;
		virtual void check(bool check) override;
		virtual const std::string name() override;
		virtual bool componentProcess(int rootInterval, long tick) override;
	};
}

