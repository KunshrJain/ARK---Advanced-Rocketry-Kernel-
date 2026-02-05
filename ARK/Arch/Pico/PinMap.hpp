#pragma once
#include <cstdint>

namespace ARK {
    namespace Arch {
        namespace Pico {
            class PinCheck {
            public:
                static bool IsValidADC(uint8_t pin) {
                    // Pico/RP2040 Standard: GP26, 27, 28 are ADC 0, 1, 2
                    // GP29 is typically VSYS on boards like Pico, but accessible
                    return (pin >= 26 && pin <= 29);
                }

                static bool IsValidPWM(uint8_t pin) {
                    // Almost all GPIOs on RP2040 support PWM
                    return (pin <= 29); 
                }
            };
        }
    }
}
