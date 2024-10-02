#if 1
#include <cstdio>
#include <mi/micomponents/miPlayWaveButtonLamp.h>
#include <mi/micomponents/miAudio.h>
#include <mi/micomponents/miSevenSegment.h>
#include <mi/micomponents/miLedStrip.h>
#include <mi/micomponents/miPhoneNumber.h>
#include <mi/micomponents/miComponentBase.h>
#include <mi/mimodules/ModuleGecon32Input.h>
#include <mi/mimodules/ModuleGecon32Output.h>
#include <mi/mimodules/ModuleMiPotentiometerADS115.h>
#include <mi/mimodules/ModuleMiRpiGpio.h>
#include <mi/misound/Audio.h>
#include <mi/mimodules/ModuleManager.h>
#include <mi/micomponents/miComponentManager.h>
#include <memory>
#include "main.h"

#define MAX_LED_RED 129
#define SMOOTHED_LED 129
#define MAX_LED_YELLOW 132
#define MAX_LED_BLUE 148

class ButtonInput :public micomponents::miButtonEventInterface
{
    std::shared_ptr < micomponents::miLamp> _Lamp;
public:

    ButtonInput(std::shared_ptr < micomponents::miLamp> lamp)
        :_Lamp(lamp)
    {

    }
    // Geerbt über miButtonEventInterface
    virtual void ButtonDown(const std::string& name) override
    {
        printf("Event 1 Button Down %s\n", name.c_str());
       _Lamp->lampOn();
    }
    virtual void ButtonUp(const std::string& name) override
    {
        printf("Event 1 Button Up %s\n", name.c_str());
        _Lamp->lampOff();
    }
    virtual void ButtonClick(const std::string& name) override
    {
        printf("Event 1 Button Click %s\n", name.c_str());
    }
    virtual void ButtonToggle(bool state, const std::string& name) override
    {
        printf("Event 1 Button Toggle %s\n", name.c_str());
    }
};

class ButtonLampInput :public micomponents::miButtonEventInterface
{
public:

    ButtonLampInput()
    {

    }
    // Geerbt über miButtonEventInterface
    virtual void ButtonDown(const std::string& name) override
    {
        printf("Event2 : Button Down %s\n", name.c_str());
    }
    virtual void ButtonUp(const std::string& name) override
    {
        printf("Event2 : Button Up %s\n", name.c_str());
    }
    virtual void ButtonClick(const std::string& name) override
    {
        printf("Event2 : Button Click %s\n", name.c_str());
    }
    virtual void ButtonToggle(bool state, const std::string& name) override
    {
        printf("Event2 : Button Toggle %s\n", name.c_str());
    }
};


class Dial : public micomponents::miPhoneNumberInterface
{
    micomponents::miSevenSegment* _MiSevenSegment;
    int _SegmentNumber;
public:

    Dial(micomponents::miSevenSegment* s)
        :_MiSevenSegment(s)
        , _SegmentNumber(0)
    {

    }

    virtual void PhoneNumberchanged(int number)
    {
        printf("PhoneNumberchanged\n");
        _SegmentNumber++;
        _MiSevenSegment->setSegment(_SegmentNumber, number);
        if (_SegmentNumber > 9)
        {
            _SegmentNumber = 0;
        }
    }
   
};


int main()
{
    
    mimodule::ModuleManager _ModuleManager(10);
    mimodule::ModuleGecon32Input _GeconIn1("/dev/ttyUSB0", 1, "geconIn1");
    mimodule::ModuleGecon32Output _GeconOut3("/dev/ttyUSB0", 3, "geconOut3");
    mimodule::ModuleMiPotentiometerADS1115 _ModulVolume(0x48, 0.1, "Volume");
    mimodule::ModuleMiRpiGpio _PhoneJack("PhoneJack",
        std::vector<mimodule::ModuleMiRpiGpioConfiguration>
    {
        {
            sizeof(mimodule::ModuleMiRpiGpioConfiguration),
                mimodule::ModuleMiRpiGpioState::Active,
                mimodule::ModulChannelDirection::Input,
                5
        }
    });
    mimodule::ModuleMiPhoneNumber _PhoneNumber(5,"dialmodul",17,27);
    mimodule::ModuleMiSevenSegment _Sevenofnine("/dev/spidev0.0", "sevenofnine");

   
    micomponents::miComponentManager man(5);
    man.registerComponent<micomponents::miSevenSegment>("seven", 20, _Sevenofnine);
    auto ptr = man.getComponent<micomponents::miSevenSegment>("seven");

    Dial p(ptr.get());
    ;
    std::shared_ptr<micomponents::miPhoneNumber> _MiPhoneNumber = std::make_shared<micomponents::miPhoneNumber>("dial",5,_PhoneNumber.getChannel("PhoneNumber"), &p);
    auto phonePtr = std::dynamic_pointer_cast<micomponents::miComponentBase>(_MiPhoneNumber);
    man.registerComponent(phonePtr);
   
    man.registerComponent<micomponents::miLedStrip>("LedstripYellow", MAX_LED_YELLOW, 100, "/dev/ttyACM1");
    auto ptrStrip = man.getComponent<micomponents::miLedStrip>("LedstripYellow");

    std::string _WavePath("/home/root/sounds");
    misound::Audio  _Audio(std::string("plug:dmix0"), _WavePath);
  
    std::shared_ptr<micomponents::miAudio> audio = std::make_shared<micomponents::miAudio>(
        "miAudio",
        10,
        _ModulVolume.getChannel("Potentiometer"),
        _PhoneJack.getChannel("GPIO5"),
        _Audio,
        100.0,
        "plug:dmix0",
        "plug:dmix1");

    auto audioPtr = std::dynamic_pointer_cast<micomponents::miAudio>(audio);
    man.registerComponent(audioPtr);


    

    _ModuleManager.addModule(&_GeconIn1);
    _ModuleManager.addModule(&_GeconOut3);
    _ModuleManager.addModule(&_PhoneJack);
    _ModuleManager.addModule(&_ModulVolume);
    _ModuleManager.addModule(&_PhoneNumber);
    _ModuleManager.addModule(&_Sevenofnine);

    std::shared_ptr<micomponents::miLamp> lamp = std::make_shared<micomponents::miLamp>(
        "LampTest",
        micomponents::LampType::Flash,
        5,
        250,
        _GeconOut3.getChannel("A3.0"));


    auto lampPtr = std::dynamic_pointer_cast<micomponents::miComponentBase>(lamp);
    man.registerComponent(lampPtr);
    ButtonInput _Event(lamp);
   

    std::shared_ptr<micomponents::miButton> button = std::make_shared<micomponents::miButton>(
        "ButtonTest",
        10,
        _GeconIn1.getChannel("E1.0"),
        &_Event,
        false);


    auto buttonPtr = std::dynamic_pointer_cast<micomponents::miComponentBase>(button);
    man.registerComponent(buttonPtr);

    ButtonLampInput Event2;

    std::shared_ptr<micomponents::miButtonLamp> buttonLamp = std::make_shared<micomponents::miButtonLamp>(
        "ButtonLampTest",
        10,
        micomponents::LampType::Flash,
        250,
        _GeconIn1.getChannel("E1.1"),
        _GeconOut3.getChannel("A3.1"),
        &Event2,
        micomponents::ButtonType::PushButtonToggle,
        false);


    auto buttonLampPtr = std::dynamic_pointer_cast<micomponents::miComponentBase>(buttonLamp);
    man.registerComponent(buttonLampPtr);


    std::shared_ptr<micomponents::miPlayWaveButtonLamp> wbuttonLamp = std::make_shared<micomponents::miPlayWaveButtonLamp>(
        "s1p1",
        10,
        micomponents::LampType::Flash,
        250,
        _GeconIn1.getChannel("E1.2"),
        _GeconOut3.getChannel("A3.2"),
        micomponents::ButtonType::Switch,
        _Audio,
        false,
        true);


    auto wbuttonLampPtr = std::dynamic_pointer_cast<micomponents::miComponentBase>(wbuttonLamp);
    man.registerComponent(wbuttonLampPtr);


    std::shared_ptr<micomponents::miPlayWaveButtonLamp> wbuttonLamp1 = std::make_shared<micomponents::miPlayWaveButtonLamp>(
        "s2p2",
        10,
        micomponents::LampType::Fix,
        250,
        _GeconIn1.getChannel("E1.4"),
        _GeconOut3.getChannel("A3.4"),
        micomponents::ButtonType::PushButtonToggle,
        _Audio,
        false,
        true);


    auto wbuttonLampPtr1 = std::dynamic_pointer_cast<micomponents::miComponentBase>(wbuttonLamp1);
    man.registerComponent(wbuttonLampPtr1);

   
    _ModuleManager.start();
    man.start();

    ptrStrip->setMode(micomponents::LedStripMode::running);
    ptrStrip->startLED();

    while (true)
    {
        
        usleep(100000);
    }
    return 0;
}
#endif

