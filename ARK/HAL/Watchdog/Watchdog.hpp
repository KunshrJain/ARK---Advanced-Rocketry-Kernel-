#pragma once
#include <cstdint>

namespace ARK {
    namespace HAL {
        class Watchdog {
        public:
            virtual ~Watchdog() = default;
            virtual void Enable(uint32_t timeout_ms) = 0;
            virtual void Feed() = 0;
            virtual void Disable() = 0;
        };
    }
    extern HAL::Watchdog& SystemWatchdog;
}
