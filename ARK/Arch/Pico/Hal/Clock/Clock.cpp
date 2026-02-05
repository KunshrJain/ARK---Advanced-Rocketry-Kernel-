#include "Clock.hpp"
#include "Config.hpp"
#include "hardware/clocks.h"
#include "hardware/vreg.h"

namespace ARK {
    namespace HAL {
        namespace Pico {
            void Clock::ApplyMcuFrequency() {
                if (MCU_FREQUENCY_MHZ > 133) vreg_set_voltage(VREG_VOLTAGE_1_20);
                set_sys_clock_khz(MCU_FREQUENCY_MHZ * 1000, true);
            }

            uint64_t Clock::GetTickPeriodUs() {
                return 1000000 / SYSTEM_FREQUENCY_HZ;
            }
        }
    }
}
