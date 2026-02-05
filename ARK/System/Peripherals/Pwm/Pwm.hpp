#pragma once
#include <cstdint>
#include "ARK/HAL/Pwm/Pwm.hpp"

namespace ARK {
    class PWM {
    public:
        PWM(uint8_t pin);
        ~PWM();

        void Init(uint32_t frequency_hz);
        void Write(float duty_cycle_percent);
        void WriteUs(uint32_t microseconds);

    private:
        uint8_t _pin;
        HAL::Pwm* _hal = nullptr;
    };
}
