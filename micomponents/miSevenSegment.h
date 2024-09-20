#pragma once
#include <mi/mimodules/ModuleMiSevenSegment.h>

namespace micomponents
{
	class miSevenSegment
	{
	private:
		mimodule::ModuleMiSevenSegment _Module;

	public:
		miSevenSegment(mimodule::ModuleMiSevenSegment& module)
			: _Module(module)
		{
			
		}
		void setSegment(int segment, int value);
		void setValue(int value);
	};
}


