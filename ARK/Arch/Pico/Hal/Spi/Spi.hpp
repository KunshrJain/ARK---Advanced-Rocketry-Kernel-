#pragma once
#include "ARK/HAL/Spi/Spi.hpp"
#include "pico/stdlib.h"
#include "hardware/spi.h"

namespace ARK {
    namespace HAL {
        namespace Pico {
            class SPI : public ARK::HAL::SPI {
            public:
                void Init(uint8_t port_num, uint8_t miso_pin, uint8_t mosi_pin, uint8_t sck_pin, uint32_t baudrate) override {
                    _inst = (port_num == 0) ? spi0 : spi1;
                    spi_init(_inst, baudrate);
                    gpio_set_function(miso_pin, GPIO_FUNC_SPI);
                    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
                    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
                }

                void Transfer(uint8_t* tx, uint8_t* rx, size_t len) override {
                    spi_write_read_blocking(_inst, tx, rx, len);
                }

                void Write(uint8_t* data, size_t len) override {
                    spi_write_blocking(_inst, data, len);
                }

            private:
                spi_inst_t* _inst = nullptr;
            };
        }
    }
}
