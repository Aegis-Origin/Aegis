#include "Application.hpp"

#include <Aegis/Core/Log.hpp>

int main()
{
    Aegis::Log::Init();
    AG_CORE_INFO("Initialized log");

    Sandbox::Application app;
    app.Run();
}
