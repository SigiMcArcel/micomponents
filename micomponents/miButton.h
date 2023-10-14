#pragma once
#include <string>
#include <mi/mimodules/ModuleInterface.h>
#include <mi/mimodules/ModuleChannel.h>
namespace micomponents
{
    enum class ButtonType
    {
        PushButton,
        PushButtonToggle,
        Switch,
    };

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
        ButtonType _ButtonType;
        bool _Toggle;


        void handleButton(bool val)
        {

            switch (_ButtonType)
            {
                case ButtonType::PushButton:
                case ButtonType::Switch:
                {
                    if (!val)
                    {
                        _ButtonEvent->ButtonOff();
                    }
                    else
                    {
                        _ButtonEvent->ButtonOn();
                    }
                    break;
                }
                case ButtonType::PushButtonToggle:
                {
                    if (val && !_Toggle)
                    {
                        _Toggle = true;
                        _ButtonEvent->ButtonOn();

                    }
                    if (val && _Toggle)
                    {
                        _Toggle = false;
                        _ButtonEvent->ButtonOff();
                    }
                    break;
                }

            }
        }

    public:
        miButton(mimodule::ModuleChannel* channel, miButtonEventInterface* buttonEvent, bool inverse, const std::string& name,ButtonType type)
            :_LastState(false)
            , _Channel(channel)
            , _ButtonEvent(buttonEvent)
            ,_Inverse(inverse)
            , _Name(name)
            , _ButtonType(type)
            , _Toggle(false)
        {
            if (_Channel != nullptr)
            {
                _Channel->registerChannelEvent(this);
            }
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
            if (_ButtonEvent != nullptr)
            {
                handleButton(val);
            }
           
        }
	};
}


