#pragma once
#include <string>
#include "Aegis/Core.h"

namespace Aegis {

    enum class EventType
    {
        None = 0, 
        WindowResize, WindowFocus, WindowLostFocus, WindowMoved, WindowClose,
        AppTick, AppUpdate, AppRender, 
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        EventFilterNone = 0,
        EventFilterApplication = 1 << 0,
        EventFilterMouse = 1 << 1,
        EventFilterKeyboard = 1 << 2,
        EventFilterInput = 1 << 3,
        EventFilterMouseButton = 1 << 4
    };

    class AEGIS_API Event {

    public:

        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); };

        bool IsInCategory(EventCategory filter) const { return GetCategoryFlags() & filter; };

        bool isHandled{ false };
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
}
