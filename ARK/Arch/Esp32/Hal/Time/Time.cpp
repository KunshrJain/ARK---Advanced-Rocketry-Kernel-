#include "Time.hpp"
#include "esp_timer.h"
<<<<<<< HEAD
#include "rom/ets_sys.h"
=======
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            uint64_t Time::GetMicros() {
                return (uint64_t)esp_timer_get_time();
            }

            void Time::DelayUntil(uint64_t target_us) {
<<<<<<< HEAD
=======
                uint64_t now = GetMicros();
                if (target_us <= now) return;

                uint64_t diff = target_us - now;
                
                // If more than 2ms, use FreeRTOS delay for efficiency
                if (diff > 2000) {
                    vTaskDelay((diff - 1000) / (portTICK_PERIOD_MS * 1000));
                }

                // Precision busy-wait for the remainder
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
                while (GetMicros() < target_us) {
                    asm volatile("nop");
                }
            }

            void Time::SleepUs(uint64_t us) {
<<<<<<< HEAD
                ets_delay_us(us);
=======
                if (us > 2000) {
                    vTaskDelay(us / (portTICK_PERIOD_MS * 1000));
                } else {
                    uint64_t start = GetMicros();
                    while (GetMicros() - start < us) {
                        asm volatile("nop");
                    }
                }
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
            }
        }
    }
}
