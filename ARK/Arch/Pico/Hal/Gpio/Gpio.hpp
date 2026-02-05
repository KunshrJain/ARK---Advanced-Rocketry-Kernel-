#pragma once
#include "ARK/HAL/Gpio/Gpio.hpp"
#include "pico/stdlib.h"

namespace ARK {
    namespace HAL {
        namespace Pico {
            class GPIO : public ARK::HAL::GPIO {
            public:
                void Init(uint8_t pin, PinMode mode) override {
                    gpio_init(pin);
                    switch (mode) {
                        case PinMode::INPUT:
                            gpio_set_dir(pin, GPIO_IN);
                            break;
                        case PinMode::OUTPUT:
                            gpio_set_dir(pin, GPIO_OUT);
                            break;
                        case PinMode::INPUT_PULLUP:
                            gpio_set_dir(pin, GPIO_IN);
                            gpio_pull_up(pin);
                            break;
                        case PinMode::INPUT_PULLDOWN:
                            gpio_set_dir(pin, GPIO_IN);
                            gpio_pull_down(pin);
                            break;
                    }
                }

                void Set(uint8_t pin, bool high) override {
                    gpio_put(pin, high);
                }

                bool Get(uint8_t pin) override {
                    return gpio_get(pin);
                }

                void Toggle(uint8_t pin) override {
                    gpio_xor_mask(1u << pin);
                }
            };
        }
    }
}
