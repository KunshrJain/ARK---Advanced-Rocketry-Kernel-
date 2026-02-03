#pragma once
#include <cstdint>

namespace ARK {
    namespace HAL {
        class Time {
        public:
            virtual ~Time() = default;
            virtual uint64_t GetMicros() = 0;
            virtual void DelayUntil(uint64_t target_us) = 0;
            virtual void SleepUs(uint64_t us) = 0;
        };
    }
    extern HAL::Time& SystemTime;
}
