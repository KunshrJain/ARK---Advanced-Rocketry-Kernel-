#include "Spi.hpp"
#include "Config.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Spi/Spi.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Spi/Spi.hpp"
#endif

namespace ARK {

    SPI::SPI(uint8_t port_num, uint8_t miso_pin, uint8_t mosi_pin, uint8_t sck_pin)
        : _port_num(port_num), _miso_pin(miso_pin), _mosi_pin(mosi_pin), _sck_pin(sck_pin) {
        #ifdef ARK_ARCH_PICO
            _hal = new HAL::Pico::SPI();
        #elif defined(ARK_ARCH_ESP32)
            _hal = new HAL::Esp32::SPI();
        #endif
    }

    SPI::~SPI() {
        if (_hal) delete _hal;
    }

    void SPI::Begin(uint32_t baudrate) {
        if (_hal) _hal->Init(_port_num, _miso_pin, _mosi_pin, _sck_pin, baudrate);
    }

    void SPI::Transfer(uint8_t* tx, uint8_t* rx, size_t len) {
        if (_hal) _hal->Transfer(tx, rx, len);
    }

    void SPI::Write(uint8_t* data, size_t len) {
        if (_hal) _hal->Write(data, len);
    }
}