#pragma once
#include <cstdint>

namespace ARK {
    namespace Arch {
        namespace Esp32 {
            class PinCheck {
            public:
                static bool IsValidADC(uint8_t pin) {
                    // ADC1: GPIO 32-39
                    // ADC2: GPIO 0, 2, 4, 12-15, 25-27 (Often restricted by WiFi)
                    // Simplified check for safe ADC1 pins often used
                    return (pin >= 32 && pin <= 39);
                }

                static bool IsValidPWM(uint8_t pin) {
                    // ESP32 supports PWM on any output capable pin (roughly 0-33, excluding inputs only 34-39)
                    // Input only: 34, 35, 36, 37, 38, 39
                    return (pin <= 33);
                }
            };
        }
    }
}
