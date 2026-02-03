#include "Time.hpp"
#include "pico/stdlib.h"
#include "hardware/timer.h"

namespace ARK {
    namespace HAL {
        namespace Pico {
            uint64_t Time::GetMicros() {
                return time_us_64();
            }

            void Time::DelayUntil(uint64_t target_us) {
                while (GetMicros() < target_us) {
                    tight_loop_contents();
                }
            }

            void Time::SleepUs(uint64_t us) {
                sleep_us(us);
            }
        }
    }
}
