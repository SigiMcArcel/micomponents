#pragma once
#include <string>
#include <mi/mimodules/ModuleInterface.h>
#include <mi/mimodules/ModuleChannel.h>
namespace micomponents
{
    class miButtonEventInterface
    {
    public:
        virtual void ButtonOn() = 0;
        virtual void ButtonOff() = 0;
    };

	class miButton :public mimodule::ModuleValueChangedEvent
	{
        enum class ButtonState
        {
            On,
            Off
        };
    private:
        bool _LastState;
        mimodule::ModuleChannel* _Channel;
        miButtonEventInterface* _ButtonEvent;
        bool _Inverse;
        std::string _Name;

    public:
        miButton(mimodule::ModuleChannel* channel, miButtonEventInterface* buttonEvent, bool inverse, const std::string& name)
            :_LastState(false)
            , _Channel(channel)
            , _ButtonEvent(buttonEvent)
            ,_Inverse(inverse)
            , _Name(name)
        {
            _Channel->registerChannelEvent(this);
        }
        // Geerbt über ModuleValueChangedEvent
        virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
        {
            bool val = false;
            val << value;
            if (_Inverse)
            {
                val = !val;
            }
            if (!val)
            {
                if (_ButtonEvent != nullptr)
                {
                    _ButtonEvent->ButtonOff();
                }
            }
            else
            {
                if (_ButtonEvent != nullptr)
                {
                    _ButtonEvent->ButtonOn();
                }
            }
        }
	};
}


