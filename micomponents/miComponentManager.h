#pragma once
#include <queue>
#include <mi/mitasks/miTaskBase.h>
#include <memory>  // für std::shared_ptr
#include "miLampBase.h"
#include "miLamp.h"
#include <functional>
#include <mi/miutils/CriticalSection.h>

namespace micomponents
{
	class miComponentManager : public miComponentBase
	{
		typedef std::vector<micomponents::miComponentBaseShared> ComponentList;
		
	private:
		
		std::queue<std::function<void()>> _Requests;
		miutils::CriticalSection _CriticalSection;

		ComponentList _ComponentList;
		int _Tick;

		


	public:
		miComponentManager()
			:miComponentBase("miComponentManager",0)
			,_CriticalSection()
			,_ComponentList(ComponentList())
		{
		}

		bool registerComponent(const micomponents::miComponentBaseShared& component);

		//Templates can not implemented in cpp file
		template <typename T, typename... Args>
		std::shared_ptr<T> registerComponent(Args&&... args)
		{
			std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
			auto basePtr = std::dynamic_pointer_cast<miComponentBase>(component);
			if (basePtr) {
				registerComponent(basePtr);
				return std::dynamic_pointer_cast<T>(component);
			}
			return nullptr;
		}

		template <typename T>
		std::shared_ptr<T> getComponent(const std::string& name)
		{
			for (const auto& element : _ComponentList) {
				if (element->name() == name) {
					return std::dynamic_pointer_cast<T>(element);  // Cast in den gewünschten Typ
				}
			}
			return nullptr;  // Falls nicht gefunden, nullptr zurückgeben
		}

		void disableOutputs(const std::string& name, bool on);
		void disableOutputsAll(bool on);
		void disableInputs(const std::string& name, bool on);
		void disableInputsAll(bool on);
		void check(int number, bool on);
		void check(const std::string& name, bool on);
		void checkAll(bool on);
		void LampOn(const std::string& name);
		void LampOn(int number);
		void LampOnAll();
		void LampOff(const std::string& name);
		void LampOff(int number);
		void LampOffAll();
		void LampOverride(const std::string& name, bool overRide);
		void LampOverride(int number, bool overRide);
		void LampOverrideAll(bool overRide);
		void setRequest(const std::function<void()>& func);
		void disableOutputsIntern(const std::string& name, bool on);
		void disableOutputsAllIntern(bool on);
		void disableInputsIntern(const std::string& name, bool on);
		void disableInputsAllIntern(bool on);
		void checkNumberIntern(int number, bool on);
		void checkIntern(const std::string& name, bool on);
		void checkAllIntern(bool on);
		void LampOnIntern(const std::string& name);
		void LampOnNumberIntern(int number);
		void LampOnAllIntern();
		void LampOffIntern(const std::string& name);
		void LampOffNumberIntern(int number);
		void LampOffAllIntern();
		void LampOverrideIntern(const std::string& name, bool overRide);
		void LampOverrideNumberIntern(int number, bool overRide);
		void LampOverrideAllIntern(bool overRide);
		int getLampCount();
		void start();
		void stop();
		const std::string getComponentValue(const std::string& componentName, const std::string& valueName);

		// Geerbt über EventListener
		virtual bool componentProcess(int rootInterval, long tick) override;
};
}

