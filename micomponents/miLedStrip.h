#pragma once
#include <mi/miutils/Time.h>
#include "miComponentBase.h"

namespace micomponents
{
	typedef enum LEDStripMode_t
	{
		off,
		full,
		runningSingle,
		running,
		toggle,
		runningSingleInvert,
		filling

	}LedStripMode;

	class miLedStrip 
		: public micomponents::miComponentBase
	{
	private:
		bool _IsOpen;
		int _NumberOfLeds;
		int _NumberOfLedsPlaying;
		int _RunningLedCnt;
		int _ToggleLedState;

		int _StartRunningLED;
		bool _StartRunningLEDInvers;
		bool _StartFiilingLED;
		bool _StartToggleLED;
		int _StartSmoothingLED;
		bool _StartSmooth;

		LedStripMode _Mode;
		LedStripMode _LastMode;

		int _Fd;
		unsigned char* _LedState;
		std::string _SerialDevice;

		int _Intervall;
		unsigned char _SmoothCnt;
		bool _SmoothDir;
		bool _Running;
		miutils::Time _Time;

		bool serialOpen();
		bool serialClose();
		bool serialWrite(unsigned char* data, int count);

		bool runningLed(unsigned char r, unsigned char g, unsigned char b, int numberOfLed);
		bool runningSingleLed(unsigned char r, unsigned char g, unsigned char b, int dir);
		bool runningSingleLedInverted(unsigned char r, unsigned char g, unsigned char b, int numberOfLed);
		bool fillingLED(unsigned char r, unsigned char g, unsigned char b, int numberOfLed);
		bool toggleLED(unsigned char r, unsigned char g, unsigned char b, int numberOfLed);
		bool smoothLed();
		bool handleLeds();

	public:
		miLedStrip(const std::string name, int numberofLeds, int intervall, const std::string& serialDevice)
			: miComponentBase(name, intervall)
			, _IsOpen(false)
			, _NumberOfLeds(numberofLeds)
			, _NumberOfLedsPlaying(numberofLeds)
			, _RunningLedCnt(0)
			, _ToggleLedState(0)
			, _StartRunningLED(false)
			, _StartRunningLEDInvers(false)
			, _StartFiilingLED(false)
			, _StartToggleLED(false)
			, _StartSmoothingLED(0)
			, _StartSmooth(false)
			, _Mode(LedStripMode::off)
			, _LastMode(LedStripMode::off)
			, _Fd(-1)
			, _LedState(NULL)
			, _SerialDevice(serialDevice)
			, _Intervall(intervall)
			, _SmoothCnt(0)
			, _SmoothDir(0)
			, _Time()

		{
			if (serialOpen())
			{
				_IsOpen = true;
			}
			
			_LedState = (unsigned char*)malloc(numberofLeds * 3);
			if (_LedState == NULL)
			{
				return;
			}
			memset(_LedState, 0, numberofLeds * 3);
			showLed();

		}

		~miLedStrip()
		{
			serialClose();
			free(_LedState);
		}

		bool setLED(unsigned char r, unsigned char g, unsigned char b, int number);
		bool showLed();
		bool clearLeds(int cnt);
		bool setLeds(int cnt);
		bool smoothingLed(int number, bool start);

		void startLED();
		void stopLED();
		void setMode(LedStripMode mode)
		{
			if (_DisableOutputs)
				return;
			_Mode = mode;
		}
		micomponents::LedStripMode getMode()
		{
			return _Mode;
		}
		micomponents::LedStripMode stepMode()
		{
			if (_DisableOutputs)
				return micomponents::LedStripMode::off;

			
			_Mode = static_cast<micomponents::LedStripMode>(static_cast<int>(_Mode) + 1);
			if (_Mode == micomponents::LedStripMode::runningSingleInvert)
			{
				_Mode = micomponents::LedStripMode::full;
			}
			printf("micomponents::miLedStrip::stepMode() %s %d", _Name.c_str(), static_cast<int>(_Mode));
			return _Mode;
		}

		virtual bool componentProcess(int rootInterval, int tick) override;
		virtual void disableOutputs(bool disable) override
		{
			miComponentBase::disableOutputs(disable);
			if (_DisableOutputs)
			{
				setMode(micomponents::LedStripMode::off);
			}
			else
			{
				setMode(_Mode);
			}
		}

	};
}


