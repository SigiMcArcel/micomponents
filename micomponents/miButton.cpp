#include "miButton.h"

const std::string micomponents::miButton::name()
{
    return _Name;
}

bool micomponents::miButton::componentProcess(int rootInterval, int tick)
{
    if (!miComponentBase::componentProcess(rootInterval, tick))
    {
        return false;
    }
    handleButton(_Name);
    return true;
}