#pragma once
#include <mi/miutils/Time.h>
#include "miComponentBase.h"

namespace micomponents
{
	typedef enum LEDStripMode_t
	{
		off = 0,
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
		int _MaxNumberOfLeds;
		int _NumberOfLedsPlaying;
		int _RunningLedCnt;
		int _ToggleLedState;

		int _StartRunningLED;
		bool _StartRunningLEDInvers;
		bool _StartFiilingLED;
		bool _StartToggleLED;
		int _SmoothingLEDNumber;
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
		bool setLedIntern(unsigned char r, unsigned char g, unsigned char b, int number);

	public:
		miLedStrip(const std::string name, int maxNumberOfLeds, int intervall, int smoothingLed, const std::string& serialDevice)
			: miComponentBase(name, intervall)
			, _IsOpen(false)
			, _MaxNumberOfLeds(maxNumberOfLeds)
			, _NumberOfLedsPlaying(maxNumberOfLeds)
			, _RunningLedCnt(0)
			, _ToggleLedState(0)
			, _StartRunningLED(false)
			, _StartRunningLEDInvers(false)
			, _StartFiilingLED(false)
			, _StartToggleLED(false)
			, _SmoothingLEDNumber(smoothingLed)
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
			if (_SmoothingLEDNumber >= _MaxNumberOfLeds)
			{
				_SmoothingLEDNumber = -1;
			}
			_LedState = (unsigned char*)malloc(_MaxNumberOfLeds * 3);
			if (_LedState == NULL)
			{
				return;
			}
			memset(_LedState, 0, _MaxNumberOfLeds * 3);
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
		bool startSmoothingLed(bool start);
		void startLED();
		void stopLED();
		void setMode(LedStripMode mode);
		micomponents::LedStripMode getMode();
		micomponents::LedStripMode stepMode();

		virtual bool componentProcess(int rootInterval, int tick) override;
		virtual void disableOutputs(bool disable) override;
		virtual void check(bool check) override;
	};
}


