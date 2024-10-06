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
	if (number >= _MaxNumberOfLeds)
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
	serialWrite(_LedState, _MaxNumberOfLeds * 3);
	serialWrite(&cmd, 1);
	return true;
}

bool micomponents::miLedStrip::clearLeds(int cnt)
{
	int tmpLeds = 0;
	if (cnt == -1)
	{
		tmpLeds = _MaxNumberOfLeds;
	}
	else
	{
		if (cnt > _MaxNumberOfLeds)
		{
			return false;
		}
		tmpLeds = cnt;
	}
	for (int i = 0; i < tmpLeds;i++)
	{
		if(i == _SmoothingLEDNumber)
		{
			continue;
		}
		_LedState[(i * 3) + 0] = 0;
		_LedState[(i * 3) + 1] = 0;
		_LedState[(i * 3) + 2] = 0;
	}
	return false;
}

bool micomponents::miLedStrip::miLedStrip::setLeds(int cnt)
{
	int tmpLeds = 0;
	if (cnt == -1)
	{
		tmpLeds = _MaxNumberOfLeds;
	}
	else
	{
		if (cnt > _MaxNumberOfLeds)
		{
			return false;
		}
		tmpLeds = cnt;
	}
	for (int i = 0; i < tmpLeds; i++)
	{
		if (i == _SmoothingLEDNumber)
		{
			continue;
		}
		_LedState[(i * 3) + 0] = 254;
		_LedState[(i * 3) + 1] = 254;
		_LedState[(i * 3) + 2] = 254;
	}

	return false;
}

bool micomponents::miLedStrip::startSmoothingLed(bool start)
{
	if (_SmoothingLEDNumber == -1)
	{
		return false;
	}
	_StartSmooth = start;
	return true;
}

bool micomponents::miLedStrip::runningSingleLed(unsigned char r, unsigned char g, unsigned char b, int numberOfLed)
{
	if (_RunningLedCnt > 0)
	{
		setLedIntern(0, 0, 0, _RunningLedCnt - 1);
	}
	setLedIntern(r, g, b, _RunningLedCnt);
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
			setLedIntern(0, 0, 0, cnt);
			if ((cnt + 1) < numberOfLed)
			{
				setLedIntern(125, 125, 125, cnt + 1);
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
			setLedIntern(125, 125, 125, cnt);
			if ((cnt + 1) < numberOfLed)
			{
				setLedIntern(0, 0, 0, cnt + 1);
			}
			cnt += 2;
		} while (cnt <= numberOfLed);
	}
	return true;
}

bool micomponents::miLedStrip::runningSingleLedInverted(unsigned char r, unsigned char g, unsigned char b, int numberOfLed)
{
	memset(_LedState, 254, numberOfLed * 3);
	setLedIntern(0, 0, 0, _RunningLedCnt);
	_RunningLedCnt++;
	if (_RunningLedCnt > numberOfLed)
	{
		_RunningLedCnt = 0;
	}

	return true;
}

bool micomponents::miLedStrip::fillingLED(unsigned char r, unsigned char g, unsigned char b, int numberOfLed)
{
	setLedIntern(r, g, b, _RunningLedCnt);
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

bool micomponents::miLedStrip::handleLeds()
{
	if (_SmoothTime.elapsed(_SmoothingIntervall))
	{
		if (_StartSmooth)
		{

			setLED(_SmoothCnt, _SmoothCnt, _SmoothCnt, _SmoothingLEDNumber);

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
			setLED(0, 0, 0, _SmoothingLEDNumber);
		}
		showLed();
	}

	if (_Time.elapsed(_Intervall))
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
				break;
			}
			case LedStripMode::off:
			{
				clearLeds(_NumberOfLedsPlaying);
				break;
			}
			}
		}
		else
		{
			clearLeds(_NumberOfLedsPlaying);
		}
		showLed();
	}
	return true;
}

bool micomponents::miLedStrip::setLedIntern(unsigned char r, unsigned char g, unsigned char b, int number)
{
	if (number == _SmoothingLEDNumber)
	{
		return false;
	}
	return setLED(r, g, b, number);
}

bool micomponents::miLedStrip::serialOpen()
{
	struct termios tty;
	
	_Fd = open(_SerialDevice.c_str(), O_RDWR | O_NONBLOCK);
	if (_Fd == -1)
	{
		return false;
	}
	// Aktuelle Einstellungen der seriellen Schnittstelle abrufen
	if (tcgetattr(_Fd, &tty) != 0) {
		printf("Fehler beim Abrufen der Attribute");
		return false;
	}
	cfsetospeed(&tty, B115200);            // 115200 baud
	cfsetispeed(&tty, B115200);            // 115200 baud

	// 8 Datenbits, 1 Stoppbit, keine Parität
	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8 Datenbits
	tty.c_cflag &= ~PARENB;                      // Keine Parität
	tty.c_cflag &= ~CSTOPB;                      // 1 Stoppbit
	tty.c_cflag &= ~CRTSCTS;                     // Keine Hardware-Flow-Control
	tty.c_cflag |= CLOCAL | CREAD;               // Lokale Verbindung und Empfang aktivieren

	// Keine Software-Flow-Control (XON, XOFF)
	tty.c_iflag &= ~(IXON | IXOFF | IXANY);

	// Keine Echo-Optionen und keine Interpretation von Eingabezeichen
	tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	// Keine Ausgabeverarbeitung
	tty.c_oflag &= ~OPOST;

	// Minimal 1 Zeichen lesen und 1 Sekunde timeout
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 1;

	// Neue Einstellungen sofort übernehmen
	if (tcsetattr(_Fd, TCSANOW, &tty) != 0) {
		printf("Fehler beim Setzen der Attribute");
		return false;
	}
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

void micomponents::miLedStrip::startLED()
{
	if (_Mode == LedStripMode::runningSingleInvert)
	{
		setLeds(_NumberOfLedsPlaying);
	}
	_Running = true;
}

void micomponents::miLedStrip::stopLED()
{
	_Running = false;
}

void micomponents::miLedStrip::setMode(LedStripMode mode)
{

	_Mode = mode;
}

micomponents::LedStripMode micomponents::miLedStrip::getMode()
{
	return _Mode;
}

micomponents::LedStripMode micomponents::miLedStrip::stepMode()
{
	if (_Mode >= micomponents::LedStripMode::filling)
	{
		_Mode = micomponents::LedStripMode::full;
	}
	_Mode = static_cast<micomponents::LedStripMode>(static_cast<int>(_Mode) + 1);
	return _Mode;
}

void micomponents::miLedStrip::disableOutputs(bool disable) 
{
	miComponentBase::disableOutputs(disable);
	if (_DisableOutputs)
	{
		_LastMode = _Mode;
		setMode(micomponents::LedStripMode::off);
	}
	else
	{
		_Mode = _LastMode;
	}
}

void micomponents::miLedStrip::check(bool check)
{
	miComponentBase::check(check);
	if (_Check)
	{
		_LastMode = _Mode;
		setMode(micomponents::LedStripMode::full);
	}
	else
	{
		_Mode = _LastMode;
	}
}

bool micomponents::miLedStrip::componentProcess(int rootInterval, int tick)
{
	if (!miComponentBase::componentProcess(rootInterval, tick))
	{
		return false;
	}
	handleLeds();
	return true;
}

