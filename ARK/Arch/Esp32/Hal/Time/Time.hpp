#pragma once
#include "ARK/HAL/Time/Time.hpp"

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            class Time final : public HAL::Time {
            public:
                uint64_t GetMicros() override;
                void DelayUntil(uint64_t target_us) override;
                void SleepUs(uint64_t us) override;
            };
        }
    }
}
