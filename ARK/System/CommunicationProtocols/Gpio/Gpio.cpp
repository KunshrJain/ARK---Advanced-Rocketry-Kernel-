#include "Gpio.hpp"
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