#pragma once
#include <mi/mimodules/ModuleMiSevenSegment.h>

namespace micomponents
{
	class miSevenSegment
	{
	private:
		mimodule::ModuleMiSevenSegment _Module;

	public:
		miSevenSegment(mimodule::ModuleMiSevenSegment& module, int intervall, double maxVolume)
			: _Module(module)
		{
			
		}
		void setSegment(int segment, int value);
		void setValue(int value);
	};
}


