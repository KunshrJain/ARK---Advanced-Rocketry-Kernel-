#pragma once
#include "ARK/HAL/Pwm/Pwm.hpp"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

namespace ARK {
    namespace HAL {
        namespace Pico {
            class Pwm : public ARK::HAL::Pwm {
            public:
                void Init(uint8_t pin, uint32_t frequency_hz) override {
                    gpio_set_function(pin, GPIO_FUNC_PWM);
                    uint slice_num = pwm_gpio_to_slice_num(pin);
                    
                    // Simple logic suitable for servos (50Hz) or generic use
                    // This is a naive implementation; proper PWM needs clock division calc
                    pwm_config config = pwm_get_default_config();
                    float div = (float)clock_get_hz(clk_sys) / (frequency_hz * 65535); 
                    if (div < 1.0f) div = 1.0f;
                    pwm_config_set_clkdiv(&config, div);
                    pwm_config_set_wrap(&config, 65535);
                    pwm_init(slice_num, &config, true);
                }

                void Write(uint8_t pin, float duty_cycle_percent) override {
                    uint slice_num = pwm_gpio_to_slice_num(pin);
                    uint16_t level = (uint16_t)((duty_cycle_percent / 100.0f) * 65535);
                    pwm_set_gpio_level(pin, level);
                }

                void WriteUs(uint8_t pin, uint32_t microseconds) override {
                     // Requires known wrap/freq to calculate level from us
                     // Placeholder
                }
            };
        }
    }
}
