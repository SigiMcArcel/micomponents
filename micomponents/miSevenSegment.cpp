#include <cmath>
#include "miSevenSegment.h"

void micomponents::miSevenSegment::setSegment(int segment, int value)
{
	std::string channelName("Segment");
	channelName.append(std::to_string(segment));
	mimodule::ModuleChannel* channel = _Module.getChannel(channelName);

	if (value > 9)
	{
		return;
	}

	if (channel == nullptr)
	{
		return;
	}
	_Number[segment - 1] = value;;
	value >> channel->value();
}

void micomponents::miSevenSegment::setValue(int value)
{
	int max = 99999999;
	if (value > max)
	{
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		int div = static_cast<int>(std::pow(10, static_cast<double>(i)));  // 10 hoch 2
		int val = max - (value / div);
		_Number[i] = val;
		setSegment(i + 1, val);

	}
}

void micomponents::miSevenSegment::setBlank()
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

void micomponents::miSevenSegment::disableOutputs(bool disable) 
{
	miComponentBase::disableOutputs(disable);
	if (_DisableOutputs)
	{
		for (int i = 0; i < 8; i++)
		{
			_LastNumber[i] = _Number[i];
		}
		setBlank();
	}
	else
	{
		setBlank();
		for (int i = 0; i < 8; i++)
		{
			if (_LastNumber[i] != -1)
				setSegment(i + 1, _LastNumber[i]);

			_LastNumber[i] = -1;
		}
		
	}
}

void micomponents::miSevenSegment::check(bool check) 
{
	miComponentBase::check(check);
	if (_Check)
	{
		for (int i = 0; i < 8; i++)
		{
			_LastNumber[i] = _Number[i];
		}
		for (int i = 0; i < 8; i++)
		{
			setSegment(i + 1, 8);
		}
	}
	else
	{
		setBlank();
		for (int i = 0; i < 8; i++)
		{
			if (_LastNumber[i] != -1)
				setSegment(i + 1, _LastNumber[i]);

			_LastNumber[i] = -1;
		}
	}
}

