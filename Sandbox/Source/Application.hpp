#include <Aegis/Core/Application.hpp>

namespace Sandbox
{
    class Application final : public Aegis::Application
    {
    public:
        Application() = default;
        ~Application() override = default;

        Application(const Application&) = default;
        Application& operator=(const Application&) = default;
        Application(Application&&) noexcept = default;
        Application& operator=(Application&&) = default;

        void Run() override {}
    };

}  // namespace Sandbox
