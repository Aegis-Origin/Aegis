#pragma once

#include "../../../Src/Aegis/Event.hpp"

#include <functional>
#include <string>
namespace Aegis
{

    struct WindwoProperties
    {
        std::string title;
        unsigned int width;
        unsigned int height;
        WindwoProperties(const std::string& title = "Aegis Engine", unsigned int width = 1280,
                         unsigned int height = 720)
            : title(title), width(width), height(height)
        {
        }
    };

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVsync(bool enabled) = 0;
        virtual bool IsVsync() const = 0;
        static Window* Create(const WindwoProperties& properties = WindwoProperties());
    };
}  // namespace Aegis
