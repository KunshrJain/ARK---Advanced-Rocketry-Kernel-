#pragma once
#include "ARK/HAL/Adc/Adc.hpp"
#include "../../PinMap.hpp"
#include "ARK/HAL/Console/Console.hpp"
#include <iostream>

namespace ARK {
    namespace HAL {
        namespace SIL {
            class Adc : public ARK::HAL::Adc {
                uint8_t _pin = 0;
            public:
                bool Init(uint8_t pin) override {
                    _pin = pin;
                    SystemConsole.Print("[SIL_ADC] Init Pin %d", pin);
                    return true;
                }
                uint16_t ReadRaw() override {
                    return 2048; // Middleware value
                }
                float ReadVoltage(float ref_voltage) override {
                    return ref_voltage / 2.0f;
                }
            };
        }
    }
}
