#pragma once
#include <cstdint>

namespace ARK {
    namespace HAL {
        class Pwm {
        public:
            virtual ~Pwm() = default;
            // Generalized PWM: Init with microsecond range for Servos
            virtual void Init(uint8_t pin, uint32_t frequency_hz) = 0;
            virtual void Write(uint8_t pin, float duty_cycle_percent) = 0; // 0.0 to 100.0
            virtual void WriteUs(uint8_t pin, uint32_t microseconds) = 0; // For Servos
        };
    }
}
