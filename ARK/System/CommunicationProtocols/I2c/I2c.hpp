#pragma once
#include <cstdint>
#include <vector>

namespace ARK {
    class I2C {
    public:
        static void Setup(uint32_t baudrate);
        static bool Write(uint8_t addr, uint8_t reg, uint8_t data);
        static bool Read(uint8_t addr, uint8_t reg, uint8_t* buffer, uint16_t len);
    };
}