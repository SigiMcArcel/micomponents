#include "miButtonBase.h"

void micomponents::miButtonBase::handleButton(const std::string& name)
{
    bool buttonClicked = false;
    bool buttonToggeld = false;

    if (_LastButtonValue == _ButtonState)
    {
        return;
    }
    _LastButtonValue = _ButtonState;
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

    if (!_DisableButtonInput)
    {
        if (buttonClicked)
        {
            ButtonClick(name);
        }
        if (buttonToggeld)
        {
            ButtonToggle(_Toggle, name);
        }
        if (_ButtonState)
        {
            ButtonDown(name);
        }
        else
        {
            ButtonUp(name);
        }
    }
}

bool micomponents::miButtonBase::getState() const
{
    return _ButtonState;
}

// Geerbt über ModuleValueChangedEvent
void micomponents::miButtonBase::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
    _ButtonState = value.getValue<bool>();
    if (_Inverse)
    {
        _ButtonState = !_ButtonState;
    }
}

void micomponents::miButtonBase::ButtonDown(const std::string& name) 
{
    if (_ButtonEvent)
    {
        _ButtonEvent->ButtonDown(name);
    }
}

void micomponents::miButtonBase::ButtonUp(const std::string& name)
{
    if (_ButtonEvent)
    {
        _ButtonEvent->ButtonUp(name);
    }
}

void micomponents::miButtonBase::ButtonClick(const std::string& name)
{
    if (_ButtonEvent)
    {
        _ButtonEvent->ButtonClick(name);
    }
}

void micomponents::miButtonBase::ButtonToggle(bool state, const std::string& name)
{
    if (_ButtonEvent)
    {
        _ButtonEvent->ButtonToggle(state, name);
    }
}