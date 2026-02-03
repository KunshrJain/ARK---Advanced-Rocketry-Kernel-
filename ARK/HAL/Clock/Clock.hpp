#pragma once
#include <cstdint>

namespace ARK {
    namespace HAL {
        class Clock {
        public:
            virtual ~Clock() = default;
            virtual void ApplyMcuFrequency() = 0;
            virtual uint64_t GetTickPeriodUs() = 0;
        };
    }
    extern HAL::Clock& SystemClock;
}
