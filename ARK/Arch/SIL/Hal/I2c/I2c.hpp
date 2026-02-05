#pragma once
#include "ARK/HAL/I2c/I2c.hpp"

namespace ARK {
    namespace HAL {
        namespace SIL {
            class I2C : public ARK::HAL::I2C {
            public:
                void Init(uint8_t port_num, uint8_t sda_pin, uint8_t scl_pin, uint32_t baudrate) override;
                bool Write(uint8_t addr, uint8_t reg, uint8_t data) override;
                bool Write(uint8_t addr, uint8_t* data, size_t len) override;
                bool Read(uint8_t addr, uint8_t reg, uint8_t* buffer, size_t len) override;
                bool Read(uint8_t addr, uint8_t* buffer, size_t len) override;
            };
        }
    }
}
