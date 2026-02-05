#include "Spi.hpp"
#include <iostream>

namespace ARK {
    namespace HAL {
        namespace SIL {
            void SPI::Init(uint8_t port_num, uint8_t miso_pin, uint8_t mosi_pin, uint8_t sck_pin, uint32_t baudrate) {
                // std::cout << "[SIL] SPI Init Port " << (int)port_num << std::endl;
            }

            void SPI::Transfer(uint8_t* tx, uint8_t* rx, size_t len) {
                // Echo back if rx is present?
            }

            void SPI::Write(uint8_t* data, size_t len) {
            }
        }
    }
}
