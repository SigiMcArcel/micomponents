#include <cstdio>
#include <mi/micomponents/miPlayWaveButtonLamp.h>
#include <mi/mimodules/ModuleHoerterInput.h>
#include <mi/mimodules/ModuleHoerterOutput.h>
#include <mi/mimodules/ModuleMiPotentiometer.h>
#include <mi/micomponents/miVolume.h>
#include <mi/mimodules/ModuleManager.h>
#include <mi/misound/Alsa.h>
#include <mi/micomponents/miLedStrip.h>

#define MAX_LED_RED 129
#define SMOOTHED_LED 129
#define MAX_LED_YELLOW 132
#define MAX_LED_BLUE 148

int main()
{
    micomponents::miLedStrip led1(MAX_LED_RED + 1, 10, "/dev/ttyACM0");
    micomponents::miLedStrip led2(MAX_LED_YELLOW + 1, 10, "/dev/ttyACM1");
    micomponents::miLedStrip led3(MAX_LED_BLUE + 1, 10, "/dev/ttyACM2");

    led1.startLED(micomponents::LedStripMode::running, 20, MAX_LED_RED);
    led2.startLED(micomponents::LedStripMode::filling, 20, MAX_LED_YELLOW);
    led3.startLED(micomponents::LedStripMode::toggle, 20, MAX_LED_BLUE);



    while (true)
    {
        
        usleep(100000);
    }
    return 0;
}