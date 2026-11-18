#pragma once

#include <cstdint>
#include <functional>
#include <ostream>
#include <string>

namespace Aegis
{
    enum class EventType : uint8_t
    {
        None = 0,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        WindowClose,
        AppTick,
        AppUpdate,
        AppRender,
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    enum EventCategory : uint8_t
    {
        EventCategoryNone = 0,
        EventCategoryApplication = 1 << 0,
        EventCategoryMouse = 1 << 1,
        EventCategoryKeyboard = 1 << 2,
        EventCategoryInput = 1 << 3,
        EventCategoryMouseButton = 1 << 4
    };

    class Event
    {
    public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); };

        bool IsInCategory(EventCategory filter) const
        {
            return (GetCategoryFlags() & filter) != 0;
        };

        bool mIshandled{false};
    };

#define EVENT_CLASS_TYPE(type)                      \
    static EventType GetStaticType()                \
    {                                               \
        return EventType::type;                     \
    }                                               \
    virtual EventType GetEventType() const override \
    {                                               \
        return GetStaticType();                     \
    }                                               \
    virtual const char* GetName() const override    \
    {                                               \
        return #type;                               \
    }

#define EVENT_CLASS_CATEGORY(category)            \
    virtual int GetCategoryFlags() const override \
    {                                             \
        return category;                          \
    }

    class EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& event) : m_event(event) {}

        template <typename T, typename F>
        bool Dispatch(F&& func)
        {
            if (m_event.GetEventType() != T::GetStaticType())
                return false;

            m_event.mIshandled = std::invoke(std::forward<F>(func), static_cast<T&>(m_event));

            return true;
        }

    private:
        Event& m_event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

};  // namespace Aegis
