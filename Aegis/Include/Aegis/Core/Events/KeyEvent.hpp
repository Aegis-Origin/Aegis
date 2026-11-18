

#pragma once

#include "Event.hpp"

#include <sstream>

namespace Aegis
{
    class KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return mKeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        explicit KeyEvent(int keyCode) : mKeyCode(keyCode) {}

        int mKeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        KeyPressedEvent(int keyCode, int repeatCount)
            : KeyEvent(keyCode), m_repeatCount(repeatCount)
        {
        }

        inline int GetRepeatCount() const { return m_repeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << mKeyCode << " (Repeat: " << m_repeatCount << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

        EVENT_CLASS_TYPE(KeyReleased)
    };
}  // namespace Aegis
