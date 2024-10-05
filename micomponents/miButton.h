#pragma once
#include <string>
#include <mi/mimodules/ModuleInterface.h>
#include <mi/mimodules/ModuleChannel.h>
#include "miButtonBase.h"
#include "miComponentBase.h"

namespace micomponents
{
	class miButton 
        :public miComponentBase
        ,public miButtonBase
	{
       
    public:
        miButton(const std::string& name,int intervall,mimodule::ModuleChannel* channel, miButtonEventInterface* buttonEvent, bool inverse)
            :miComponentBase(name, intervall)
            ,miButtonBase(name,channel,buttonEvent,inverse)
        {
         
        }

        virtual const std::string name() override;
        virtual bool componentProcess(int rootInterval, int tick) override;
	};
}


