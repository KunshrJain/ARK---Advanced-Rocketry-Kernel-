#pragma once
#include "ARK/HAL/Clock/Clock.hpp"

namespace ARK {
    namespace HAL {
        namespace SIL {
            class Clock final : public HAL::Clock {
            public:
                void ApplyMcuFrequency() override;
                uint64_t GetTickPeriodUs() override;
            };
        }
    }
}
