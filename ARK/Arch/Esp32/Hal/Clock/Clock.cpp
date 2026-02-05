#include "Clock.hpp"
#include "Config.hpp"
#include "esp_pm.h"
#include "esp_private/esp_clk.h"
<<<<<<< HEAD
=======
#include "soc/rtc.h"
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            void Clock::ApplyMcuFrequency() {
                rtc_cpu_freq_config_t config;
                rtc_clk_cpu_freq_mhz_to_config(MCU_FREQUENCY_MHZ, &config);
                rtc_clk_cpu_freq_set_config(&config);
            }

            uint64_t Clock::GetTickPeriodUs() {
                return 1000000 / SYSTEM_FREQUENCY_HZ;
            }
        }
    }
}
