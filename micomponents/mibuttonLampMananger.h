#pragma once
#include <vector>
#include "miComponentInterface.h"

namespace micomponents
{
	class mibuttonLampMananger
	{
	private:
		std::vector<miLampInterface*> _LampControls;
		std::vector<miEmergenceStopInterface*> _EmergencyStops;

	public:
		bool registerLampControl(miLampInterface* interf)
		{
			if (interf == nullptr)
			{
				return false;
			}
			_LampControls.push_back(interf);
			return true;
		}
		bool registerEmergencyStop(miEmergenceStopInterface* interf)
		{
			if (interf == nullptr)
			{
				return false;
			}
			_EmergencyStops.push_back(interf);
			return true;
		}
		bool registerAll(miLampInterface* interfLc, miEmergenceStopInterface* interfEs)
		{
			if (!registerLampControl(interfLc))
			{
				return false;
			}
			return registerEmergencyStop(interfEs);
		}

		void emergencyStopAll(bool on)
		{
			std::vector<miEmergenceStopInterface*>::iterator iterEmerge;
			for (iterEmerge = _EmergencyStops.begin(); iterEmerge < _EmergencyStops.end(); ++iterEmerge)
			{
				
				(*iterEmerge)->emergencyStop(on);
			}
		}

		void lampControlAll(bool on)
		{
			std::vector<miLampInterface*>::iterator iterLampc;
			for (iterLampc = _LampControls.begin(); iterLampc < _LampControls.end(); ++iterLampc)
			{
				(*iterLampc)->lampControl(on);
			}
		}

		void LampOn(const std::string& name)
		{
			std::vector<miLampInterface*>::iterator iterLampc;
			for (iterLampc = _LampControls.begin(); iterLampc < _LampControls.end(); ++iterLampc)
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
			for (iterLampc = _LampControls.begin(); iterLampc < _LampControls.end(); ++iterLampc)
			{
				if ((*iterLampc)->name() == name)
				{
					(*iterLampc)->lampOff();
				}

			}
		}
	};
}

