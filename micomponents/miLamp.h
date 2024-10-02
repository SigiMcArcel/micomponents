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

		~miLamp()
		{
			
		}

		

		
		void lampOn()
		{
			on();
		}

		void lampOff()
		{
			off();
		}

		virtual const std::string name()
		{
			return _Name;
		}

		virtual bool componentProcess(int rootInterval,int tick) override
		{
			
			if (!miComponentBase::componentProcess(rootInterval, tick))
			{
				return false;
			}
			_LampDisable = _DisableOutputs;
			miLampBase::handleLamp();
			return true;
		}

		


	};
}

