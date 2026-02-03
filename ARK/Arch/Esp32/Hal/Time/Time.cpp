#include "Time.hpp"
#include "esp_timer.h"
#include "rom/ets_sys.h"

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            uint64_t Time::GetMicros() {
                return (uint64_t)esp_timer_get_time();
            }

            void Time::DelayUntil(uint64_t target_us) {
                while (GetMicros() < target_us) {
                    asm volatile("nop");
                }
            }

            void Time::SleepUs(uint64_t us) {
                ets_delay_us(us);
            }
        }
    }
}
