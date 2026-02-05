#include "I2c.hpp"
#include "Config.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/I2c/I2c.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/I2c/I2c.hpp"
#elif defined(ARK_ARCH_SIL)
#include "ARK/Arch/SIL/Hal/I2c/I2c.hpp"
#endif

namespace ARK {

    I2C::I2C(uint8_t port_num, uint8_t sda_pin, uint8_t scl_pin) 
        : _port_num(port_num), _sda_pin(sda_pin), _scl_pin(scl_pin) {
        #ifdef ARK_ARCH_PICO
            _hal = new HAL::Pico::I2C();
        #elif defined(ARK_ARCH_ESP32)
            _hal = new HAL::Esp32::I2C();
        #elif defined(ARK_ARCH_SIL)
            _hal = new HAL::SIL::I2C();
        #endif
    }

    I2C::~I2C() {
        if (_hal) delete _hal;
    }

    void I2C::Begin(uint32_t baudrate) {
        if (_hal) _hal->Init(_port_num, _sda_pin, _scl_pin, baudrate);
    }

    bool I2C::Write(uint8_t addr, uint8_t reg, uint8_t data) {
        if (_hal) return _hal->Write(addr, reg, data);
        return false;
    }

    bool I2C::Write(uint8_t addr, uint8_t* data, size_t len) {
        if (_hal) return _hal->Write(addr, data, len);
        return false;
    }

    bool I2C::Read(uint8_t addr, uint8_t reg, uint8_t* buffer, size_t len) {
        if (_hal) return _hal->Read(addr, reg, buffer, len);
        return false;
    }

    bool I2C::Read(uint8_t addr, uint8_t* buffer, size_t len) {
        if (_hal) return _hal->Read(addr, buffer, len);
        return false;
    }
}
