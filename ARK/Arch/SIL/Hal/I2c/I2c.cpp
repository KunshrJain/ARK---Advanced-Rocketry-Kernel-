#include "I2c.hpp"
#include <iostream>

namespace ARK {
    namespace HAL {
        namespace SIL {
            void I2C::Init(uint8_t port_num, uint8_t sda_pin, uint8_t scl_pin, uint32_t baudrate) {
                // std::cout << "[SIL] I2C Init Port " << (int)port_num << std::endl;
            }

            bool I2C::Write(uint8_t addr, uint8_t reg, uint8_t data) {
                return true;
            }

            bool I2C::Write(uint8_t addr, uint8_t* data, size_t len) {
                return true;
            }

            bool I2C::Read(uint8_t addr, uint8_t reg, uint8_t* buffer, size_t len) {
                return true;
            }

            bool I2C::Read(uint8_t addr, uint8_t* buffer, size_t len) {
                return true;
            }
        }
    }
}
