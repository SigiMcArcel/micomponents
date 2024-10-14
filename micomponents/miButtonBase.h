#pragma once
#include <string>
#include <mi/mimodules/ModuleInterface.h>
#include <mi/mimodules/ModuleChannel.h>
#include "miComponentBase.h"

namespace micomponents
{
    enum class miButtonState
    {
        On,
        Off
    };

    class miButtonEventInterface
    {
    public:
        virtual void ButtonDown(const std::string& name) = 0;
        virtual void ButtonUp(const std::string& name) = 0;
        virtual void ButtonClick(const std::string& name) = 0;
        virtual void ButtonToggle(bool state, const std::string& name) = 0;
    };

    class miButtonBase
        :public mimodule::ModuleValueChangedEvent
        , public miButtonEventInterface
    {
   
    protected:
        std::string _ButtonName;
        bool _LastState;
        mimodule::ModuleChannel* _Channel;
        miButtonEventInterface* _ButtonEvent;
        bool _Inverse;
        bool _Toggle;
        bool _LastButtonValue;
        bool _ButtonState;
        bool _ButtonStateLast;
        bool _DisableButtonInput;

        void handleButton(const std::string& name);

    public:
        miButtonBase(const std::string name, mimodule::ModuleChannel* channel, miButtonEventInterface* buttonEvent, bool inverse)
            : _ButtonName(name)
            , _LastState(false)
            , _Channel(channel)
            , _ButtonEvent(buttonEvent)
            , _Inverse(inverse)
            , _Toggle(false)
            , _LastButtonValue(false)
            , _ButtonState(false)
            , _DisableButtonInput(false)
        {
            if (_Channel != nullptr)
            {
                _Channel->registerChannelEvent(this,true);
            }
            else
            {
                printf("miButton invalid channel\n");
            }
        }

        bool getState() const;
        virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override;
        virtual void ButtonDown(const std::string& name) override;
        virtual void ButtonUp(const std::string& name) override;
        virtual void ButtonClick(const std::string& name) override;
        virtual void ButtonToggle(bool state, const std::string& name) override;
    };
}

