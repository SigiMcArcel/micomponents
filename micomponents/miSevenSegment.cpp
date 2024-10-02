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
		setSegment(i + 1, val);

	}
}

