#include "Gpio.hpp"
#include "ARK/HAL/Console/Console.hpp"
#include <iostream>

namespace ARK {
    namespace HAL {
        namespace SIL {
            void GPIO::Init(uint8_t pin, PinMode mode) {
                // Log initialization
                // std::cout << "[SIL] GPIO Init Pin " << (int)pin << std::endl;
            }

            void GPIO::Set(uint8_t pin, bool high) {
                // std::cout << "[SIL] GPIO Set Pin " << (int)pin << " to " << high << std::endl;
            }

            bool GPIO::Get(uint8_t pin) {
                return false; // Default
            }

            void GPIO::Toggle(uint8_t pin) {
                // std::cout << "[SIL] GPIO Toggle Pin " << (int)pin << std::endl;
            }
        }
    }
}
