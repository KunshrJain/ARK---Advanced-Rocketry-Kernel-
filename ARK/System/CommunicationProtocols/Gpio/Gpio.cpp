#include "Gpio.hpp"
#include "Config.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Gpio/Gpio.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Gpio/Gpio.hpp"
#endif

namespace ARK {

    GPIO::GPIO(uint8_t pin) : _pin(pin) {
        #ifdef ARK_ARCH_PICO
            _hal = new HAL::Pico::GPIO();
        #elif defined(ARK_ARCH_ESP32)
            _hal = new HAL::Esp32::GPIO();
        #endif
    }

    GPIO::~GPIO() {
        if (_hal) delete _hal;
    }

    void GPIO::Mode(HAL::PinMode mode) {
        if (_hal) _hal->Init(_pin, mode);
    }

    void GPIO::Set(bool high) {
        if (_hal) _hal->Set(_pin, high);
    }

    bool GPIO::Get() {
        if (_hal) return _hal->Get(_pin);
        return false;
    }

    void GPIO::Toggle() {
        if (_hal) _hal->Toggle(_pin);
    }
}