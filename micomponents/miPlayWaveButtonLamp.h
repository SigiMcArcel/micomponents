#pragma once
#include <mi/micomponents/miButtonLamp.h>

namespace micomponents
{

	class miPlayWaveButtonLamp : public micomponents::miButtonLamp 
	{
	public:
		virtual void ButtonOn() override;
		virtual void ButtonOff() override;
	};

}