#include "Pwm.hpp"
#include "ARK/HAL/Console/Console.hpp"
#include <iostream>

namespace ARK {
    namespace HAL {
        namespace SIL {
            void Pwm::Init(uint8_t pin, uint32_t frequency_hz) {
                SystemConsole.Print("[SIL_PWM] Init Pin %d at %d Hz", pin, frequency_hz);
            }

            void Pwm::Write(uint8_t pin, float duty_cycle_percent) {
                // SystemConsole.Print("[SIL_PWM] Pin %d Duty: %.2f%%", pin, duty_cycle_percent);
            }

            void Pwm::WriteUs(uint8_t pin, uint32_t microseconds) {
                // SystemConsole.Print("[SIL_PWM] Pin %d Pulse: %d us", pin, microseconds);
            }
        }
    }
}
