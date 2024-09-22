#pragma once
#include <vector>
#include "miComponentInterface.h"

namespace micomponents
{
	class mibuttonLampMananger
	{
	private:
		std::vector<miLampInterface*> _Lamps;
		std::vector<miButtonInterface*> _Buttons;

	public:
		bool registerLamp(miLampInterface* lampInterface)
		{
			if (lampInterface == nullptr)
			{
				return false;
			}
			_Lamps.push_back(lampInterface);
			return true;
		}

		bool registerButtons(miButtonInterface* buttonInterface)
		{
			if (buttonInterface == nullptr)
			{
				return false;
			}
			_Buttons.push_back(buttonInterface);
			return true;
		}
		
		bool registerAll(miLampInterface* lampInterface, miButtonInterface* buttonInterface)
		{
			if (!registerLamp(lampInterface))
			{
				return false;
			}
			return registerButtons(buttonInterface);
		}

		void emergencyStopAll(bool on)
		{
			disableButtonEventAll(on);
			stopActivitiesAll();
			LampOffAll();
		}

		void lampControlAll(bool on)
		{
			std::vector<miLampInterface*>::iterator iterLampc;
			for (iterLampc = _Lamps.begin(); iterLampc < _Lamps.end(); ++iterLampc)
			{
				(*iterLampc)->lampControl(on);
			}
		}

		void disableButtonEvent(const std::string& name,bool on)
		{
			std::vector<miButtonInterface*>::iterator iterButtons;
			for (iterButtons = _Buttons.begin(); iterButtons < _Buttons.end(); ++iterButtons)
			{
				if ((*iterButtons)->name() == name)
				{
					(*iterButtons)->disableButtonEvent(on);
				}
			}
		}

		void disableButtonEventAll(bool on)
		{
			std::vector<miButtonInterface*>::iterator iterButtons;
			for (iterButtons = _Buttons.begin(); iterButtons < _Buttons.end(); ++iterButtons)
			{
				(*iterButtons)->disableButtonEvent(on);
			}
		}

		void stopActivitiesAll()
		{
			std::vector<miButtonInterface*>::iterator iterButtons;
			for (iterButtons = _Buttons.begin(); iterButtons < _Buttons.end(); ++iterButtons)
			{
				(*iterButtons)->stopActivities();
			}
		}

	
		void LampOn(const std::string& name)
		{
			std::vector<miLampInterface*>::iterator iterLampc;
			for (iterLampc = _Lamps.begin(); iterLampc < _Lamps.end(); ++iterLampc)
			{
				if ((*iterLampc)->name() == name)
				{
					(*iterLampc)->lampOn();
				}
				
			}
		}
		void LampOff(const std::string& name)
		{
			std::vector<miLampInterface*>::iterator iterLampc;
			for (iterLampc = _Lamps.begin(); iterLampc < _Lamps.end(); ++iterLampc)
			{
				if ((*iterLampc)->name() == name)
				{
					(*iterLampc)->lampOff();
				}

			}
		}

		void LampOnAll()
		{
			std::vector<miLampInterface*>::iterator iterLampc;
			for (iterLampc = _Lamps.begin(); iterLampc < _Lamps.end(); ++iterLampc)
			{
				(*iterLampc)->lampOn();
			}
		}

		void LampOffAll()
		{
			std::vector<miLampInterface*>::iterator iterLampc;
			for (iterLampc = _Lamps.begin(); iterLampc < _Lamps.end(); ++iterLampc)
			{
				(*iterLampc)->lampOff();
			}
		}
		
	};
}

