#include "Uart.hpp"
#include "Config.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Uart/Uart.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Uart/Uart.hpp"
#elif defined(ARK_ARCH_SIL)
#include "ARK/Arch/SIL/Hal/Uart/Uart.hpp"
#endif

namespace ARK {

    UART::UART(uint8_t port_num, uint8_t tx_pin, uint8_t rx_pin)
        : _port_num(port_num), _tx_pin(tx_pin), _rx_pin(rx_pin) {
        #ifdef ARK_ARCH_PICO
            _hal = new HAL::Pico::UART();
        #elif defined(ARK_ARCH_ESP32)
            _hal = new HAL::Esp32::UART();
        #elif defined(ARK_ARCH_SIL)
            _hal = new HAL::SIL::UART();
        #endif
    }

    UART::~UART() {
        if (_hal) delete _hal;
    }

    void UART::Begin(uint32_t baudrate) {
        if (_hal) _hal->Init(_port_num, _tx_pin, _rx_pin, baudrate);
    }

    void UART::Write(const uint8_t* data, size_t len) {
        if (_hal) _hal->Write(data, len);
    }

    void UART::Write(char c) {
        if (_hal) _hal->Write(c);
    }

    void UART::Write(const char* str) {
        if (_hal) _hal->Write(str);
    }

    size_t UART::Read(uint8_t* buffer, size_t len, uint32_t timeout_ms) {
        if (_hal) return _hal->Read(buffer, len, timeout_ms);
        return 0;
    }
}
