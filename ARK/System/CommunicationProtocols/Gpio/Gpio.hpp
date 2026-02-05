#pragma once
<<<<<<< HEAD
#include <stdint.h>

namespace ARK {
    namespace GPIO {
        void Setup(uint8_t pin, bool isOutput);
        void Write(uint8_t pin, bool value);
        bool Read(uint8_t pin);
    }
=======
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
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
}