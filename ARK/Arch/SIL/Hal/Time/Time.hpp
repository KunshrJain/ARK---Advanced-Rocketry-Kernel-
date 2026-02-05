#pragma once
#include "ARK/HAL/Time/Time.hpp"
#include <chrono>

namespace ARK {
    namespace HAL {
        namespace SIL {
            class Time final : public HAL::Time {
            public:
                Time();
                uint64_t GetMicros() override;
                void DelayUntil(uint64_t target_us) override;
                void SleepUs(uint64_t us) override;
            private:
                std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
            };
        }
    }
}
