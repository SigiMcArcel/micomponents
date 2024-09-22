#pragma once
#include <string>
#include <mi/mimodules/ModuleInterface.h>
#include <mi/mimodules/ModuleChannel.h>
#include "miComponentInterface.h"

namespace micomponents
{
    class miButtonEventInterface
    {
    public:
        virtual void ButtonDown(const std::string& name) = 0;
        virtual void ButtonUp(const std::string& name) = 0;
        virtual void ButtonClick(const std::string& name) = 0;
        virtual void ButtonToggle(bool state, const std::string& name) = 0;
    };

	class miButton 
        :public mimodule::ModuleValueChangedEvent
        ,public micomponents::miButtonInterface
       
	{
        enum class ButtonState
        {
            On,
            Off
        };
    protected:
        bool _LastState;
        mimodule::ModuleChannel* _Channel;
        miButtonEventInterface* _ButtonEvent;
        bool _Inverse;
        std::string _Name;
        bool _Toggle;
        bool _ButtonState;
        bool _ButtonStateLast;
        bool _DisableButtonEvent;
       
        void handleButton()
        {
            bool buttonClicked = false;
            bool buttonToggeld = false;
            if (!_ButtonState && _ButtonStateLast)
            {
                buttonClicked = true;
            }
            _ButtonStateLast = _ButtonState;
            if (_ButtonState && !_Toggle)
            {
                _Toggle = true;
                buttonToggeld = true;
            }
            else if (_ButtonState && _Toggle)
            {
                _Toggle = false;
                buttonToggeld = true;
            }

            if (!_DisableButtonEvent)
            {
                if (buttonClicked)
                {
                    _ButtonEvent->ButtonClick(_Name);
                }
                if (buttonToggeld)
                {
                    _ButtonEvent->ButtonToggle(_Toggle, _Name);
                }
                if (_ButtonState)
                {
                    _ButtonEvent->ButtonDown(_Name);
                }
                else
                {
                    _ButtonEvent->ButtonUp(_Name);
                }
            }
        }

    public:
        miButton(mimodule::ModuleChannel* channel, miButtonEventInterface* buttonEvent, bool inverse, const std::string& name)
            :_LastState(false)
            , _Channel(channel)
            , _ButtonEvent(buttonEvent)
            , _Inverse(inverse)
            , _Name(name)
            , _Toggle(false)
            , _ButtonState(false)
            , _DisableButtonEvent(false)
        {
            if (_Channel != nullptr)
            {
                _Channel->registerChannelEvent(this);
            }
            else
            {
                printf("miButton invalid channel\n");
            }
        }

        virtual void stopActivities()
        {

        }

        virtual void disableButtonEvent(bool on)
        {
            _DisableButtonEvent = on;
        }

        virtual const std::string name()
        {
            return _Name;
        }

        bool getState() const
        {
            return _ButtonState;
        }
        // Geerbt über ModuleValueChangedEvent
        virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
        {
            _ButtonState << value;
            if (_Inverse)
            {
                _ButtonState = !_ButtonState;
            }
            if (_ButtonEvent != nullptr)
            {
                handleButton();
            }
           
        }
	};
}


