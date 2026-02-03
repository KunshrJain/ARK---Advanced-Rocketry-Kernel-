#pragma once
#include <cstdint>

namespace ARK {
    class SPI {
    public:
        static void Setup(uint32_t baudrate);
        static void Transfer(uint8_t* tx, uint8_t* rx, uint16_t len);
    };
}