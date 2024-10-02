#pragma once
#include <mi/mimodules/ModuleMiSevenSegment.h>
#include "miComponentBase.h"

namespace micomponents
{
	class miSevenSegment : public miComponentBase
	{
	private:
		mimodule::ModuleMiSevenSegment& _Module;

	public:
		miSevenSegment(const std::string name, int intervall, mimodule::ModuleMiSevenSegment& module)
			: miComponentBase(name,intervall)
			, _Module(module)
		{
			
		}
		void setSegment(int segment, int value);
		void setValue(int value);
		void setBlank()
		{
			uint8_t value = static_cast<uint8_t>(mimodule::ModuleMiSevenSegment::controlCommand::Blank);
			std::string channelName("Control");
			mimodule::ModuleChannel* channel = _Module.getChannel(channelName);

			if (channel == nullptr)
			{
				return;
			}
			value >> channel->value();
		}

		virtual void disableOutputs(bool disable) override
		{
			miComponentBase::disableOutputs(disable);
			if (_DisableOutputs)
			{
				setBlank();
			}
		}
	};
}


