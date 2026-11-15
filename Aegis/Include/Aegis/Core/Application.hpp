#pragma once

#include "Aegis/Export.hpp"

namespace Aegis
{
    class AG_EXPORT Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;

        virtual void Run() = 0;
    };

}  // namespace Aegis
