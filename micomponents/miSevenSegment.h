#pragma once
#include <mi/mimodules/ModuleMiSevenSegment.h>
#include "miComponentBase.h"

namespace micomponents
{
	class miSevenSegment : public miComponentBase
	{
	private:
		mimodule::ModuleMiSevenSegment& _Module;
		int _Number[8];

	public:
		miSevenSegment(const std::string name, int intervall, mimodule::ModuleMiSevenSegment& module)
			: miComponentBase(name, intervall)
			, _Module(module)
			, _Number{0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f }
		{
			
		}

		void setSegment(int segment, int value,bool direct = false);
		void setValue(int value);
		void reset();
		void setBlank();

		virtual void disableOutputs(bool disable) override;
		virtual void check(bool check) override;
	};
}


