#pragma once

#include "Aegis/Export.hpp"

#include <spdlog/spdlog.h>

#include <memory>

namespace Aegis
{
    class AG_EXPORT Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_coreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_clientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> m_coreLogger;
        static std::shared_ptr<spdlog::logger> m_clientLogger;
    };
}  // namespace Aegis

// Core log macros
#define AG_CORE_WARN(...)  ::Aegis::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define AG_CORE_INFO(...)  ::Aegis::Log::GetCoreLogger()->info(__VA_ARGS__);
#define AG_CORE_ERROR(...) ::Aegis::Log::GetCoreLogger()->error(__VA_ARGS__);
#define AG_CORE_TRACE(...) ::Aegis::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define AG_CORE_FATAL(...) ::Aegis::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// Client log macros
#define AG_WARN(...)  ::Aegis::Log::GetClientLogger()->warn(__VA_ARGS__);
#define AG_INFO(...)  ::Aegis::Log::GetClientLogger()->info(__VA_ARGS__);
#define AG_ERROR(...) ::Aegis::Log::GetClientLogger()->error(__VA_ARGS__);
#define AG_TRACE(...) ::Aegis::Log::GetClientLogger()->trace(__VA_ARGS__);
#define AG_FATAL(...) ::Aegis::Log::GetClientLogger()->fatal(__VA_ARGS__);
