#include <cstdio>
#include <mi/micomponents/miButtonLamp.h>
#include <mi/mimodules/ModuleHoerterInput.h>
#include <mi/mimodules/ModuleHoerterOutput.h>
#include <mi/mimodules/ModuleManager.h>

class BEvent :public  micomponents::miButtonEventInterface
{
    // Geerbt über miButtonEventInterface
    virtual void ButtonOn() override
    {
    }
    virtual void ButtonOff() override
    {
    }
};

int main()
{
    mimodule::ModuleHoerterInput Module1(0x38, "Module1");
    mimodule::ModuleHoerterInput Module2(0x39, "Module2");
    mimodule::ModuleHoerterInput Module3(0x3A, "Module3");
    mimodule::ModuleHoerterOutput Module4(0x20, "Module4");
    mimodule::ModuleHoerterOutput Module5(0x21, "Module5");
    mimodule::ModuleHoerterOutput Module6(0x22, "Module6");






    micomponents::miButtonLamp lamp01(micomponents::LampType::Flash, 250,Module1.getChannel("E1"),Module4.getChannel("A1"),new BEvent(),"p1");
    micomponents::miButtonLamp lamp02(micomponents::LampType::Flash, 250,Module1.getChannel("E2"),Module4.getChannel("A2"), new BEvent(), "p2");
    micomponents::miButtonLamp lamp03(micomponents::LampType::Flash, 250,Module1.getChannel("E3"),Module4.getChannel("A3"), new BEvent(), "p3");
    micomponents::miButtonLamp lamp04(micomponents::LampType::Flash, 250,Module1.getChannel("E4"),Module4.getChannel("A4"), new BEvent(), "p4");
    micomponents::miButtonLamp lamp05(micomponents::LampType::Flash, 250,Module1.getChannel("E5"),Module6.getChannel("A5"), new BEvent(), "p5");
    micomponents::miButtonLamp lamp06(micomponents::LampType::Flash, 250,Module1.getChannel("E6"),Module4.getChannel("A6"), new BEvent(), "p6");
    micomponents::miButtonLamp lamp07(micomponents::LampType::Flash, 250,Module1.getChannel("E7"),Module4.getChannel("A7"), new BEvent(), "p7");
    micomponents::miButtonLamp lamp08(micomponents::LampType::Flash, 250,Module1.getChannel("E8"),Module4.getChannel("A8"), new BEvent(), "p8");
    micomponents::miButtonLamp lamp09(micomponents::LampType::Flash, 250,Module2.getChannel("E1"),Module6.getChannel("A6"), new BEvent(), "p9");
    micomponents::miButtonLamp lamp10(micomponents::LampType::Flash, 250,Module2.getChannel("E2"),Module5.getChannel("A2"), new BEvent(), "p10");
    micomponents::miButtonLamp lamp11(micomponents::LampType::Flash, 250,Module2.getChannel("E3"),Module5.getChannel("A3"), new BEvent(), "p11");
    micomponents::miButtonLamp lamp12(micomponents::LampType::Flash, 250,Module2.getChannel("E4"),Module5.getChannel("A4"), new BEvent(), "p12");
    micomponents::miButtonLamp lamp13(micomponents::LampType::Flash, 250,Module2.getChannel("E5"),Module5.getChannel("A5"), new BEvent(), "p13");
    micomponents::miButtonLamp lamp14(micomponents::LampType::Flash, 250,Module2.getChannel("E6"),Module5.getChannel("A6"), new BEvent(), "p14");
    micomponents::miButtonLamp lamp15(micomponents::LampType::Flash, 250,Module2.getChannel("E7"),Module5.getChannel("A7"), new BEvent(), "p15");
    micomponents::miButtonLamp lamp16(micomponents::LampType::Flash, 250,Module3.getChannel("E8"),Module5.getChannel("A8"), new BEvent(), "p16");
    micomponents::miButtonLamp lamp17(micomponents::LampType::Flash, 250,Module3.getChannel("E1"),Module6.getChannel("A1"), new BEvent(), "p17");
    micomponents::miButtonLamp lamp18(micomponents::LampType::Flash, 250,Module3.getChannel("E2"),Module6.getChannel("A2"), new BEvent(), "p18");
    micomponents::miButtonLamp lamp19(micomponents::LampType::Flash, 250,Module3.getChannel("E3"),Module6.getChannel("A3"), new BEvent(), "p19");
    micomponents::miButtonLamp lamp20(micomponents::LampType::Flash, 250,Module3.getChannel("E4"),Module6.getChannel("A4"), new BEvent(), "p20");
    /*micomponents::miButtonLamp lamp1(micomponents::LampType::Flash, 250, Module6.getChannel("A5"));
    micomponents::miButtonLamp lamp1(micomponents::LampType::Flash, 250, Module6.getChannel("A6"));*/

   



    mimodule::ModuleManager man(20);
    man.addModule(&Module1);
    man.addModule(&Module2);
    man.addModule(&Module3);
    man.addModule(&Module4);
    man.addModule(&Module5);
    man.addModule(&Module6);
    man.start();
    while (true)
    {
        usleep(100000);
    }
    return 0;
}