#pragma once
#include "ARK/HAL/Adc/Adc.hpp"
#include "ARK/Arch/Pico/PinMap.hpp"
#include "ARK/HAL/Console/Console.hpp"
#include "hardware/adc.h"
#include <string>

namespace ARK {
    namespace HAL {
        namespace Pico {
            class Adc : public ARK::HAL::Adc {
                uint8_t _pin = 0;
            public:
                bool Init(uint8_t pin) override {
                    if (!ARK::Arch::Pico::PinCheck::IsValidADC(pin)) {
                        SystemConsole.Error("Fatal: Pin " + std::to_string(pin) + " is not a valid ADC pin on Pico (Use 26-29).");
                        return false;
                    }
                    _pin = pin;
                    adc_init();
                    adc_gpio_init(pin);
                    return true;
                }
                uint16_t ReadRaw() override {
                    if (_pin < 26) return 0;
                    adc_select_input(_pin - 26);
                    return adc_read();
                }
                float ReadVoltage(float ref_voltage) override {
                    uint16_t raw = ReadRaw();
                    return raw * (ref_voltage / 4095.0f);
                }
            };
        }
    }
}
