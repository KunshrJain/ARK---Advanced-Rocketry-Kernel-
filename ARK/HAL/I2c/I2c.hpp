#pragma once
#include <cstdint>
#include <cstddef>

namespace ARK {
    namespace HAL {
        class I2C {
        public:
            virtual ~I2C() = default;

            // Initialize the I2C bus with specific pins and baudrate
            // port_num: The hardware port number (e.g., 0 or 1 for Pico/ESP32)
            // sda_pin: The GPIO pin for SDA
            // scl_pin: The GPIO pin for SCL
            // baudrate: Frequency in Hz
            virtual void Init(uint8_t port_num, uint8_t sda_pin, uint8_t scl_pin, uint32_t baudrate) = 0;

            virtual bool Write(uint8_t addr, uint8_t reg, uint8_t data) = 0;
            virtual bool Write(uint8_t addr, uint8_t* data, size_t len) = 0;
            virtual bool Read(uint8_t addr, uint8_t reg, uint8_t* buffer, size_t len) = 0;
            virtual bool Read(uint8_t addr, uint8_t* buffer, size_t len) = 0;
        };
    }
}
