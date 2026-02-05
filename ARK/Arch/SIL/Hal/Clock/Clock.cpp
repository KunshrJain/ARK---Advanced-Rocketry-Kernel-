#include "Clock.hpp"
#include "Config.hpp"

namespace ARK {
    namespace HAL {
        namespace SIL {
            void Clock::ApplyMcuFrequency() {
            }

            uint64_t Clock::GetTickPeriodUs() {
                return 1000000 / SYSTEM_FREQUENCY_HZ;
            }
        }
    }
}
