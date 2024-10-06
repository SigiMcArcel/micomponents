#include <cmath>
#include "miSevenSegment.h"

void micomponents::miSevenSegment::setSegment(int segment, int value,bool direct)
{
	std::string channelName("Segment");
	channelName.append(std::to_string(segment));
	mimodule::ModuleChannel* channel = _Module.getChannel(channelName);

	if (channel == nullptr)
	{
		return;
	}
	if(!direct)
		_Number[segment - 1] = value;

	uint8_t val8 = static_cast<uint8_t>(value);
	channel->value().setValue<uint8_t>(val8);
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

void micomponents::miSevenSegment::reset()
{
	for (int i = 0; i < 8; i++)
	{
		setSegment(i + 1, 15);
	}
}

void micomponents::miSevenSegment::setBlank()
{
	uint32_t value = static_cast<uint8_t>(mimodule::ModuleMiSevenSegment::ControlCommand::Blank);
	std::string channelName("Control");
	mimodule::ModuleChannel* channel = _Module.getChannel(channelName);

	if (channel == nullptr)
	{
		return;
	}
	channel->value().setValue<uint32_t>(value);
}

void micomponents::miSevenSegment::disableOutputs(bool disable) 
{
	miComponentBase::disableOutputs(disable);
	if (_DisableOutputs)
	{
		setBlank();
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			setSegment(i + 1, _Number[i]);
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
			setSegment(i + 1, 8,true);
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			setSegment(i + 1, _Number[i]);
		}
	}
}

