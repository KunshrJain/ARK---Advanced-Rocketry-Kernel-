#pragma once
#include "ARK/HAL/I2c/I2c.hpp"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

namespace ARK {
    namespace HAL {
        namespace Pico {
            class I2C : public ARK::HAL::I2C {
            public:
                void Init(uint8_t port_num, uint8_t sda_pin, uint8_t scl_pin, uint32_t baudrate) override {
                    _inst = (port_num == 0) ? i2c0 : i2c1;
                    i2c_init(_inst, baudrate);
                    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
                    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
                    gpio_pull_up(sda_pin);
                    gpio_pull_up(scl_pin);
                }

                bool Write(uint8_t addr, uint8_t reg, uint8_t data) override {
                    uint8_t buf[] = {reg, data};
                    return i2c_write_blocking(_inst, addr, buf, 2, false) == 2;
                }

                bool Write(uint8_t addr, uint8_t* data, size_t len) override {
                    return i2c_write_blocking(_inst, addr, data, len, false) == len;
                }

                bool Read(uint8_t addr, uint8_t reg, uint8_t* buffer, size_t len) override {
                    i2c_write_blocking(_inst, addr, &reg, 1, true);
                    return i2c_read_blocking(_inst, addr, buffer, len, false) == len;
                }

                bool Read(uint8_t addr, uint8_t* buffer, size_t len) override {
                    return i2c_read_blocking(_inst, addr, buffer, len, false) == len;
                }

            private:
                i2c_inst_t* _inst = nullptr;
            };
        }
    }
}
