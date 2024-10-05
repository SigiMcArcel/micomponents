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
		int _LastNumber[8];

	public:
		miSevenSegment(const std::string name, int intervall, mimodule::ModuleMiSevenSegment& module)
			: miComponentBase(name, intervall)
			, _Module(module)
			, _Number{ - 1, -1, -1, -1, -1, -1, -1, -1}
			, _LastNumber{-1, -1, -1, -1, -1, -1, -1, -1}
		{
			
		}

		void setSegment(int segment, int value);
		void setValue(int value);
		void setBlank();

		virtual void disableOutputs(bool disable) override;
		virtual void check(bool check) override;
	};
}


