#pragma once
#include <cstdint>
#include <cstddef>

namespace ARK {
    namespace HAL {
        class SPI {
        public:
            virtual ~SPI() = default;

            // Initialize the SPI bus
            // port_num: The hardware port number
            // miso_pin: RX pin
            // mosi_pin: TX pin
            // sck_pin: Clock pin
            // baudrate: Frequency in Hz
            virtual void Init(uint8_t port_num, uint8_t miso_pin, uint8_t mosi_pin, uint8_t sck_pin, uint32_t baudrate) = 0;

            // Transfer data (Full Duplex)
            // tx: buffer to transmit (can be nullptr)
            // rx: buffer to receive (can be nullptr)
            // len: number of bytes
            virtual void Transfer(uint8_t* tx, uint8_t* rx, size_t len) = 0;
            
            // Write data (Half Duplex / Simplex)
            virtual void Write(uint8_t* data, size_t len) = 0;
        };
    }
}
