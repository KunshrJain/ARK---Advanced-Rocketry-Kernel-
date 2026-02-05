#pragma once
#include "ARK/HAL/Spi/Spi.hpp"

namespace ARK {
    namespace HAL {
        namespace SIL {
            class SPI : public ARK::HAL::SPI {
            public:
                void Init(uint8_t port_num, uint8_t miso_pin, uint8_t mosi_pin, uint8_t sck_pin, uint32_t baudrate) override;
                void Transfer(uint8_t* tx, uint8_t* rx, size_t len) override;
                void Write(uint8_t* data, size_t len) override;
            };
        }
    }
}
