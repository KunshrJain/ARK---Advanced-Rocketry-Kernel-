#pragma once
#include "ARK/HAL/Pwm/Pwm.hpp"
// ESP-IDF headers

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            class Pwm : public ARK::HAL::Pwm {
            public:
                void Init(uint8_t pin, uint32_t frequency_hz) override {
                }
                void Write(uint8_t pin, float duty_cycle_percent) override {
                }
                void WriteUs(uint8_t pin, uint32_t microseconds) override {
                }
            };
        }
    }
}
