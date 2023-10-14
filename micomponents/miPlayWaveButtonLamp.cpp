#include <mi/micomponents/miPlayWaveButtonLamp.h>

void micomponents::miPlayWaveButtonLamp::ButtonOn()
{
	_Lamp.on();
	_Wave.play();
}

void micomponents::miPlayWaveButtonLamp::ButtonOff()
{
	_Lamp.off();
	_Wave.stop();
}
