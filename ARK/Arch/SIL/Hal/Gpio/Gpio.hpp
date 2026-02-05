#pragma once
#include "ARK/HAL/Gpio/Gpio.hpp"

namespace ARK {
    namespace HAL {
        namespace SIL {
            class GPIO : public ARK::HAL::GPIO {
            public:
                void Init(uint8_t pin, PinMode mode) override;
                void Set(uint8_t pin, bool high) override;
                bool Get(uint8_t pin) override;
                void Toggle(uint8_t pin) override;
            };
        }
    }
}
