#include "miComponentManager.h"

void micomponents::miComponentManager::setRequest(const std::function<void()>& func) 
{
	_CriticalSection.EnterCriticalSection();
	_Requests.push(func);
	_CriticalSection.LeaveCriticalSection();
}

bool micomponents::miComponentManager::registerComponent(const micomponents::miComponentBaseShared& component)
{
	_ComponentList.push_back(component);
	return true;
}

void micomponents::miComponentManager::disableOutputsIntern(const std::string& name, bool on)
{
	for (const auto& element : _ComponentList) 
	{
		if (element->name() == name)
		{
			element->disableOutputs(on);
		}
	}
}

void micomponents::miComponentManager::disableOutputsAllIntern(bool on)
{
	for (const auto& element : _ComponentList) 
	{
		element->disableOutputs(on);
	}
}

void micomponents::miComponentManager::disableInputsIntern(const std::string& name, bool on)
{
	for (const auto& element : _ComponentList) 
	{
		if (element->name() == name)
		{
			element->disableInputs(on);
		}
	}
}

void micomponents::miComponentManager::disableInputsAllIntern(bool on)
{
	for (const auto& element : _ComponentList) 
	{
		element->disableInputs(on);
	}
}

void micomponents::miComponentManager::checkNumberIntern(int number, bool on)
{
	int count = 0;
	for (const auto& element : _ComponentList) {
		if (auto ptr = std::dynamic_pointer_cast<miComponentBase>(element)) 
		{
			if (number == count)
			{
				ptr->check(on);
			}
		}
		count++;
	}
}

void micomponents::miComponentManager::checkIntern(const std::string& name, bool on)
{
	for (const auto& element : _ComponentList) {
		if (auto ptrLamp = std::dynamic_pointer_cast<miComponentBase>(element)) 
		{
			if (element->name() == name)
			{
				ptrLamp->check(on);
			}
		}
	}
}

void micomponents::miComponentManager::checkAllIntern(bool on)
{
	for (const auto& element : _ComponentList)
	{
		if (auto ptr = std::dynamic_pointer_cast<miComponentBase>(element)) 
		{
			ptr->check(on);
		}
	}
}

void micomponents::miComponentManager::LampOnIntern(const std::string& name)
{
	for (const auto& element : _ComponentList) {
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element)) 
		{
			if (element->name() == name)
			{
				ptrLamp->lampOn();
			}
		}
	}
}

void micomponents::miComponentManager::LampOnNumberIntern(int number)
{
	int count = 0;
	for (const auto& element : _ComponentList) {
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element)) 
		{
			if (number == count)
			{
				ptrLamp->lampOn();
				return;
			}
			count++;
		}
	}
}

void micomponents::miComponentManager::LampOnAllIntern()
{
	for (const auto& element : _ComponentList)
	{
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element)) 
		{
			ptrLamp->lampOn();
		}
	}
}

void micomponents::miComponentManager::LampOffIntern(const std::string& name)
{
	for (const auto& element : _ComponentList) 
	{
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element)) 
		{
			if (element->name() == name)
			{
				ptrLamp->lampOff();
			}
		}
	}
}

void micomponents::miComponentManager::LampOffNumberIntern(int number)
{
	int count = 0;
	for (const auto& element : _ComponentList) 
	{
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element)) 
		{
			if (number == count)
			{
				ptrLamp->lampOff();
				return;
			}
			count++;
		}
	}
}

void micomponents::miComponentManager::LampOffAllIntern()
{
	for (const auto& element : _ComponentList) 
	{
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element))
		{
			ptrLamp->lampOff();
		}
	}
}

void micomponents::miComponentManager::LampOverrideIntern(const std::string& name,bool overRide)
{
	for (const auto& element : _ComponentList)
	{
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element)) 
		{
			if (element->name() == name)
			{
				ptrLamp->overRide(overRide);
			}
		}
	}
}

void micomponents::miComponentManager::LampOverrideNumberIntern(int number, bool overRide)
{
	int count = 0;
	for (const auto& element : _ComponentList)
	{
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element)) 
		{
			if (number == count)
			{
				ptrLamp->overRide(overRide);
				return;
			}
			count++;
		}
	}
}

void micomponents::miComponentManager::LampOverrideAllIntern(bool overRide)
{
	for (const auto& element : _ComponentList)
	{
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element))
		{
			ptrLamp->overRide(overRide);
		}
	}
}

int micomponents::miComponentManager::getLampCount()
{
	int count = 0;
	for (const auto& element : _ComponentList) {
		if (auto ptrLamp = std::dynamic_pointer_cast<miLampBase>(element)) 
		{
			count++;
		}
	}
	return count;
}

void micomponents::miComponentManager::disableOutputs(const std::string& name, bool on)
{
	setRequest(std::bind(&micomponents::miComponentManager::disableOutputsIntern, this, name, on));
}

void micomponents::miComponentManager::disableOutputsAll(bool on)
{
	setRequest(std::bind(&micomponents::miComponentManager::disableOutputsAllIntern, this,on));
}

void micomponents::miComponentManager::disableInputs(const std::string& name, bool on)
{
	setRequest(std::bind(&micomponents::miComponentManager::disableInputsIntern, this, name, on));
}

void micomponents::miComponentManager::disableInputsAll(bool on)
{
	setRequest(std::bind(&micomponents::miComponentManager::disableInputsAllIntern, this,  on));
}

void micomponents::miComponentManager::check(int number, bool on)
{
	setRequest(std::bind(&micomponents::miComponentManager::checkNumberIntern, this, number, on));
}

void micomponents::miComponentManager::check(const std::string& name, bool on)
{
	setRequest(std::bind(&micomponents::miComponentManager::checkIntern, this, name, on));
}

void micomponents::miComponentManager::checkAll(bool on)
{
	setRequest(std::bind(&micomponents::miComponentManager::checkAllIntern, this,  on));
}

void micomponents::miComponentManager::LampOn(const std::string& name)
{
	setRequest(std::bind(&micomponents::miComponentManager::LampOnIntern, this, name));
}

void micomponents::miComponentManager::LampOn(int number)
{
	setRequest(std::bind(&micomponents::miComponentManager::LampOnNumberIntern, this, number));
}

void micomponents::miComponentManager::LampOnAll()
{
	setRequest(std::bind(&micomponents::miComponentManager::LampOnAllIntern, this));
}

void micomponents::miComponentManager::LampOff(const std::string& name)
{
	setRequest(std::bind(&micomponents::miComponentManager::LampOffIntern, this, name));
}

void micomponents::miComponentManager::LampOff(int number)
{
	setRequest(std::bind(&micomponents::miComponentManager::LampOffNumberIntern, this, number));
}

void micomponents::miComponentManager::LampOffAll()
{
	setRequest(std::bind(&micomponents::miComponentManager::LampOffAllIntern, this));
}

void micomponents::miComponentManager::LampOverride(const std::string& name, bool overRide)
{
	setRequest(std::bind(&micomponents::miComponentManager::LampOverrideIntern, this, name, overRide));
}

void micomponents::miComponentManager::LampOverride(int number, bool overRide)
{
	setRequest(std::bind(&micomponents::miComponentManager::LampOverrideNumberIntern, this, number, overRide));
}

void micomponents::miComponentManager::LampOverrideAll(bool overRide)
{
	setRequest(std::bind(&micomponents::miComponentManager::LampOverrideAllIntern, this, overRide));
}

void micomponents::miComponentManager::start()
{
	for (const auto& element : _ComponentList) 
	{
		element->componentStart();
	}
}

void micomponents::miComponentManager::stop()
{
	for (const auto& element : _ComponentList)
	{
		element->componentStop();
	}
}

const std::string micomponents::miComponentManager::getComponentValue(const std::string& componentName, const std::string& valueName)
{
	for (const auto& element : _ComponentList) {
		if (componentName == element->name())
		{
			return element->getValue(valueName);
		}
	}
	return std::string();
}

bool micomponents::miComponentManager::componentProcess(int rootInterval, long tick)
{
	_CriticalSection.EnterCriticalSection();
	while (!_Requests.empty()) {
		_Requests.front()();
		_Requests.pop(); // Entfernt das Element an der Front
	}
	_CriticalSection.LeaveCriticalSection();
	return true;
}
