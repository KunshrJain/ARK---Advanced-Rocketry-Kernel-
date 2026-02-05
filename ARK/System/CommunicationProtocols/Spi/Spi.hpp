#pragma once
#include <cstdint>
<<<<<<< HEAD
=======
#include <cstddef>
#include "ARK/HAL/Spi/Spi.hpp"
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)

namespace ARK {
    class SPI {
    public:
<<<<<<< HEAD
        static void Setup(uint32_t baudrate);
        static void Transfer(uint8_t* tx, uint8_t* rx, uint16_t len);
=======
        SPI(uint8_t port_num, uint8_t miso_pin, uint8_t mosi_pin, uint8_t sck_pin);
        ~SPI();

        void Begin(uint32_t baudrate);
        void Transfer(uint8_t* tx, uint8_t* rx, size_t len);
        void Write(uint8_t* data, size_t len);

    private:
        uint8_t _port_num;
        uint8_t _miso_pin;
        uint8_t _mosi_pin;
        uint8_t _sck_pin;
        HAL::SPI* _hal = nullptr;
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
    };
}