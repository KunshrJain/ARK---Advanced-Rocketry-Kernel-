#pragma once
#include "ARK/HAL/Gpio/Gpio.hpp"
#include "driver/gpio.h"

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            class GPIO : public ARK::HAL::GPIO {
            public:
                void Init(uint8_t pin, PinMode mode) override {
                    gpio_num_t gpio_pin = (gpio_num_t)pin;
                    switch (mode) {
                        case PinMode::INPUT:
                            gpio_set_direction(gpio_pin, GPIO_MODE_INPUT);
                            break;
                        case PinMode::OUTPUT:
                            gpio_set_direction(gpio_pin, GPIO_MODE_OUTPUT);
                            break;
                        case PinMode::INPUT_PULLUP:
                            gpio_set_direction(gpio_pin, GPIO_MODE_INPUT);
                            gpio_set_pull_mode(gpio_pin, GPIO_PULLUP_ONLY);
                            break;
                        case PinMode::INPUT_PULLDOWN:
                            gpio_set_direction(gpio_pin, GPIO_MODE_INPUT);
                            gpio_set_pull_mode(gpio_pin, GPIO_PULLDOWN_ONLY);
                            break;
                    }
                }

                void Set(uint8_t pin, bool high) override {
                    gpio_set_level((gpio_num_t)pin, high);
                }

                bool Get(uint8_t pin) override {
                    return gpio_get_level((gpio_num_t)pin);
                }

                void Toggle(uint8_t pin) override {
                    bool current = gpio_get_level((gpio_num_t)pin);
                    gpio_set_level((gpio_num_t)pin, !current);
                }
            };
        }
    }
}
