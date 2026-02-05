#pragma once
#include <cstdint>
<<<<<<< HEAD
#include <vector>
=======
#include <cstddef>
#include "ARK/HAL/I2c/I2c.hpp"
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)

namespace ARK {
    class I2C {
    public:
<<<<<<< HEAD
        static void Setup(uint32_t baudrate);
        static bool Write(uint8_t addr, uint8_t reg, uint8_t data);
        static bool Read(uint8_t addr, uint8_t reg, uint8_t* buffer, uint16_t len);
=======
        I2C(uint8_t port_num, uint8_t sda_pin, uint8_t scl_pin);
        ~I2C();

        void Begin(uint32_t baudrate);
        bool Write(uint8_t addr, uint8_t reg, uint8_t data);
        bool Write(uint8_t addr, uint8_t* data, size_t len);
        bool Read(uint8_t addr, uint8_t reg, uint8_t* buffer, size_t len);
        bool Read(uint8_t addr, uint8_t* buffer, size_t len);

    private:
        uint8_t _port_num;
        uint8_t _sda_pin;
        uint8_t _scl_pin;
        HAL::I2C* _hal = nullptr;
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
    };
}