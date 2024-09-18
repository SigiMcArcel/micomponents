#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include "miLedStrip.h"


bool micomponents::miLedStrip::setLED(unsigned char r, unsigned char g, unsigned char b, int number)
{
	if ((_LedState == NULL || _Fd == -1))
	{
		return false;
	}
	if (number > _NumberOfLeds)
	{
		return false;
	}
	_LedState[(number * 3) + 0] = r;
	_LedState[(number * 3) + 1] = g;
	_LedState[(number * 3) + 2] = b;

	return true;
}

bool micomponents::miLedStrip::showLed()
{
	unsigned char cmd = 0xff;
	if ((_LedState == NULL || _Fd == -1))
	{
		return false;
	}
	serialWrite(_LedState, _NumberOfLeds * 3);
	serialWrite(&cmd, 1);
	return true;
}

bool micomponents::miLedStrip::clearLeds(int cnt)
{
	int tmpLeds = 0;
	if (cnt == -1)
	{
		tmpLeds = _NumberOfLeds * 3;
	}
	else
	{
		if (cnt > _NumberOfLeds)
		{
			return false;
		}
		tmpLeds = cnt * 3;
	}
	memset(_LedState, 0, tmpLeds);

	return false;
}

bool micomponents::miLedStrip::miLedStrip::setLeds(int cnt)
{
	int tmpLeds = 0;
	if (cnt == -1)
	{
		tmpLeds = _NumberOfLeds * 3;
	}
	else
	{
		if (cnt > _NumberOfLeds)
		{
			return false;
		}
		tmpLeds = cnt * 3;
	}
	memset(_LedState, 254, tmpLeds);

	return false;
}

bool micomponents::miLedStrip::smoothingLed(int number, bool start)
{
	_StartSmooth = start;

	_StartSmoothingLED = number;
	return false;
}

bool micomponents::miLedStrip::runningSingleLed(unsigned char r, unsigned char g, unsigned char b, int numberOfLed)
{
	if (_RunningLedCnt > 0)
	{
		setLED(0, 0, 0, _RunningLedCnt - 1);
	}
	setLED(r, g, b, _RunningLedCnt);
	_RunningLedCnt++;
	if (_RunningLedCnt > numberOfLed)
	{
		_RunningLedCnt = 0;
	}

	return true;
}

bool micomponents::miLedStrip::runningLed(unsigned char r, unsigned char g, unsigned char b, int numberOfLed)
{
	if (!_ToggleLedState)
	{
		int cnt = 0;
		_ToggleLedState = true;

		do
		{
			setLED(0, 0, 0, cnt);
			if ((cnt + 1) < numberOfLed)
			{
				setLED(125, 125, 125, cnt + 1);
			}
			cnt += 2;
		} while (cnt <= numberOfLed);

	}
	else
	{
		int cnt = 0;
		_ToggleLedState = false;
		do
		{
			setLED(125, 125, 125, cnt);
			if ((cnt + 1) < numberOfLed)
			{
				setLED(0, 0, 0, cnt + 1);
			}
			cnt += 2;
		} while (cnt <= numberOfLed);
	}


	return true;

}
bool micomponents::miLedStrip::runningSingleLedInverted(unsigned char r, unsigned char g, unsigned char b, int numberOfLed)
{
	memset(_LedState, 254, numberOfLed * 3);
	setLED(0, 0, 0, _RunningLedCnt);
	_RunningLedCnt++;
	if (_RunningLedCnt > numberOfLed)
	{
		_RunningLedCnt = 0;
	}

	return true;
}

bool micomponents::miLedStrip::fillingLED(unsigned char r, unsigned char g, unsigned char b, int numberOfLed)
{
	setLED(r, g, b, _RunningLedCnt);
	_RunningLedCnt++;
	if (_RunningLedCnt > numberOfLed)
	{
		_RunningLedCnt = 0;
		clearLeds(numberOfLed);
	}

	return true;
}

bool micomponents::miLedStrip::toggleLED(unsigned char r, unsigned char g, unsigned char b, int numberOfLed)
{
	if (!_ToggleLedState)
	{
		_ToggleLedState = true;
		clearLeds(numberOfLed);
	}
	else
	{
		_ToggleLedState = false;
		setLeds(numberOfLed);
	}

	return true;
}

bool micomponents::miLedStrip::smoothLed()
{
	return false;
}

bool micomponents::miLedStrip::serialOpen()
{
	struct termios tio;
	struct termios stdio;
	struct termios old_stdio;


	tcgetattr(STDOUT_FILENO, &old_stdio);

	memset(&stdio, 0, sizeof(stdio));
	stdio.c_iflag = 0;
	stdio.c_oflag = 0;
	stdio.c_cflag = 0;
	stdio.c_lflag = 0;
	stdio.c_cc[VMIN] = 1;
	stdio.c_cc[VTIME] = 0;
	tcsetattr(STDOUT_FILENO, TCSANOW, &stdio);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &stdio);
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

	memset(&tio, 0, sizeof(tio));
	tio.c_iflag = 0;
	tio.c_oflag = 0;
	tio.c_cflag = CS8 | CREAD | CLOCAL;           // 8n1, see termios.h for more information
	tio.c_lflag = 0;
	tio.c_cc[VMIN] = 1;
	tio.c_cc[VTIME] = 5;

	_Fd = open(_SerialDevice.c_str(), O_RDWR | O_NONBLOCK);
	if (_Fd == -1)
	{
		return false;
	}
	cfsetospeed(&tio, B115200);            // 115200 baud
	cfsetispeed(&tio, B115200);            // 115200 baud

	tcsetattr(_Fd, TCSANOW, &tio);
	return true;
}

bool micomponents::miLedStrip::serialClose()
{
	close(_Fd);
	_Fd = -1;
	return true;
}

bool micomponents::miLedStrip::serialWrite(unsigned char* data, int count)
{
	if (_Fd == -1)
	{
		return false;
	}
	write(_Fd, data, count);
	return true;
}


void micomponents::miLedStrip::startLED(LedStripMode mode, int intervalDivisor, int maxLed)
{
	_Mode = mode;

	_IntervalDivisor = intervalDivisor;

	_NumberOfLedsPlaying = maxLed;
	if (_IntervalDivisor == 0)
	{
		_IntervalDivisor = _TimerIntervall;
	}

	if (mode == LedStripMode::runningSingleInvert)
	{
		setLeds(_NumberOfLedsPlaying);
	}
	_Running = true;
}

void micomponents::miLedStrip::stopLED()
{
	_Mode = LedStripMode::off;
}

void micomponents::miLedStrip::eventOccured(void* sender, const std::string& name)
{
	if (_StartSmooth)
	{
		setLED(_SmoothCnt, _SmoothCnt, _SmoothCnt, _StartSmoothingLED);

		if (!_SmoothDir)
		{
			_SmoothCnt++;
			if (_SmoothCnt >= 240)
			{
				_SmoothDir = true;
			}
		}
		else
		{
			_SmoothCnt--;
			if (_SmoothCnt <= 10)
			{
				_SmoothDir = false;
			}
		}

	}
	else
	{
		if (_StartSmoothingLED > 0)
		{
			setLED(0, 0, 0, _StartSmoothingLED);
		}
	}
	if ((_IntervalCnt % _IntervalDivisor) == 0)
	{

		if (_Running)
		{
			switch (_Mode)
			{
			case LedStripMode::running:
			{
				runningLed(254, 254, 254, _NumberOfLedsPlaying);
				break;
			}
			case LedStripMode::runningSingle:
			{
				runningSingleLed(254, 254, 254, _NumberOfLedsPlaying);
				break;
			}
			case LedStripMode::runningSingleInvert:
			{
				runningSingleLedInverted(254, 254, 254, _NumberOfLedsPlaying);
				break;
			}
			case LedStripMode::filling:
			{
				fillingLED(254, 254, 254, _NumberOfLedsPlaying);
				break;
			}
			case LedStripMode::toggle:
			{
				toggleLED(254, 254, 254, _NumberOfLedsPlaying);
				break;
			}
			case LedStripMode::full:
			{
				setLeds(_NumberOfLedsPlaying);
				/*if (_LastMode != LedMode::full)
				{
					showLed();
				}*/
				break;
			}
			case LedStripMode::off:
			{
				clearLeds(_NumberOfLedsPlaying);
				/*if (_LastMode != LedMode::off)
				{
					showLed();
				}*/
				break;
			}
			}
			_LastMode = _Mode;
		}
	}
	if ((_Mode != LedStripMode::off) && (_Mode != LedStripMode::full))
	{

	}
	showLed();
	_IntervalCnt++;
}
