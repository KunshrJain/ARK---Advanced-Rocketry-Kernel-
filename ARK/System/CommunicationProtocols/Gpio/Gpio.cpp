#include "Gpio.hpp"
<<<<<<< HEAD
#include "ARK/HAL/Console/Console.hpp"

#ifdef ARK_ARCH_PICO
    #include "pico/stdlib.h"
    void ARK::GPIO::Setup(uint8_t pin, bool isOutput) {
        gpio_init(pin);
        gpio_set_dir(pin, isOutput ? GPIO_OUT : GPIO_IN);
    }
    void ARK::GPIO::Write(uint8_t pin, bool value) {
        gpio_put(pin, value);
    }
    bool ARK::GPIO::Read(uint8_t pin) {
        return gpio_get(pin);
    }

#elif defined(ARK_ARCH_ESP32)
    #include "driver/gpio.h"
    void ARK::GPIO::Setup(uint8_t pin, bool isOutput) {
        gpio_reset_pin((gpio_num_t)pin);
        gpio_set_direction((gpio_num_t)pin, isOutput ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT);
    }
    void ARK::GPIO::Write(uint8_t pin, bool value) {
        gpio_set_level((gpio_num_t)pin, value ? 1 : 0);
    }
    bool ARK::GPIO::Read(uint8_t pin) {
        return gpio_get_level((gpio_num_t)pin);
    }
#elif defined(ARK_ARCH_SIL)
    void ARK::GPIO::Setup(uint8_t pin, bool isOutput) {
        SystemConsole.Print("[SIL_GPIO] Setup pin: %d, isOutput: %d", pin, isOutput);
    }
    void ARK::GPIO::Write(uint8_t pin, bool value) {
        SystemConsole.Print("[SIL_GPIO] Write to pin: %d, value: %d", pin, value);
    }
    bool ARK::GPIO::Read(uint8_t pin) {
        SystemConsole.Print("[SIL_GPIO] Read from pin: %d", pin);
        return false; // Return a dummy value
    }
#endif
=======
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
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
