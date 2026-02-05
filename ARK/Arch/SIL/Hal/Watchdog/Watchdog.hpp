#pragma once
#include "ARK/HAL/Watchdog/Watchdog.hpp"

namespace ARK {
    namespace HAL {
        namespace SIL {
            class Watchdog : public ARK::HAL::Watchdog {
            public:
                void Enable(uint32_t timeout_ms) override;
                void Feed() override;
                void Disable() override;
            };
        }
    }
}
