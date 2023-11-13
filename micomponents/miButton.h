#pragma once
#include <string>
#include <mi/mimodules/ModuleInterface.h>
#include <mi/mimodules/ModuleChannel.h>
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

	class miButton :public mimodule::ModuleValueChangedEvent
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
       
        void handleButton()
        {
            if (!_ButtonState && _ButtonStateLast)
            {
                _ButtonEvent->ButtonClick(_Name);
            }

            if (_ButtonState)
            {
                _ButtonEvent->ButtonDown(_Name);
            }
            else
            {
                _ButtonEvent->ButtonUp(_Name);
            }

            if (_ButtonEvent && !_Toggle)
            {
                _Toggle = true;
                _ButtonEvent->ButtonToggle(_Toggle, _Name);

            }
            if (_ButtonEvent && _Toggle)
            {
                _Toggle = false;
                _ButtonEvent->ButtonToggle(_Toggle,_Name);
            }


            //switch (_ButtonType)
            //{
            //    case ButtonType::PushButton:
            //    case ButtonType::Switch:
            //    {
            //        if (!val)
            //        {
            //            _ButtonEvent->ButtonOff();
            //        }
            //        else
            //        {
            //            _ButtonEvent->ButtonOn();
            //        }
            //        break;
            //    }
            //    case ButtonType::PushButtonToggle:
            //    {
            //        if (val && !_Toggle)
            //        {
            //            _Toggle = true;
            //            _ButtonEvent->ButtonOn();

            //        }
            //        if (val && _Toggle)
            //        {
            //            _Toggle = false;
            //            _ButtonEvent->ButtonOff();
            //        }
            //        break;
            //    }

            //}
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
        {
            if (_Channel != nullptr)
            {
                _Channel->registerChannelEvent(this);
            }
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


