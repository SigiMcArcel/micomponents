#pragma once
#include <mi/miutils/Timer.h>

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

	class miLedStrip : public miutils::EventListener
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
		miutils::Timer _Timer;
		std::string _SerialDevice;

		int _IntervalDivisor;
		int _TimerIntervall;
		int _IntervalCnt;
		unsigned char _SmoothCnt;
		bool _SmoothDir;
		bool _Running;

		bool serialOpen();
		bool serialClose();
		bool serialWrite(unsigned char* data, int count);

		bool runningLed(unsigned char r, unsigned char g, unsigned char b, int numberOfLed);
		bool runningSingleLed(unsigned char r, unsigned char g, unsigned char b, int dir);
		bool runningSingleLedInverted(unsigned char r, unsigned char g, unsigned char b, int numberOfLed);
		bool fillingLED(unsigned char r, unsigned char g, unsigned char b, int numberOfLed);
		bool toggleLED(unsigned char r, unsigned char g, unsigned char b, int numberOfLed);
		bool smoothLed();

		// Geerbt über iEventListener
		virtual void eventOccured(void* sender, const std::string& name) override;

	

	public:
		miLedStrip(int numberofLeds, int intervall, const std::string& serialDevice)
			:_IsOpen(false)
			, _NumberOfLeds(numberofLeds)
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
			, _Timer("LEDStrip", this)
			, _SerialDevice(serialDevice)
			, _IntervalDivisor(intervall)
			, _TimerIntervall(intervall)
			, _IntervalCnt(0)
			, _SmoothCnt(0)
			, _SmoothDir(0)

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
			_Timer.Start(_TimerIntervall);

		}

		~miLedStrip()
		{
			_Timer.Stop();
			serialClose();
			free(_LedState);
		}

		bool setLED(unsigned char r, unsigned char g, unsigned char b, int number);
		bool showLed();
		bool clearLeds(int cnt);
		bool setLeds(int cnt);
		bool smoothingLed(int number, bool start);

		void startLED(LedStripMode mode, int intervalDivisor, int maxLed);
		void stopLED();
		void setMode(LedStripMode mode)
		{
			_Mode = mode;
		}
	};
}


