#pragma once
#include <cstdint>
#include "ARK/HAL/Gpio/Gpio.hpp"

namespace ARK {
    class GPIO {
    public:
        GPIO(uint8_t pin);
        ~GPIO();

        void Mode(HAL::PinMode mode);
        void Set(bool high);
        bool Get();
        void Toggle();

    private:
        uint8_t _pin;
        HAL::GPIO* _hal = nullptr;
    };
}