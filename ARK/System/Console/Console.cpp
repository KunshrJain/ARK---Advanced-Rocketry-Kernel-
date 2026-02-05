#include "ARK/HAL/Console/Console.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Console/Console.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Console/Console.hpp"
#elif defined(ARK_ARCH_SIL)
#include "ARK/Arch/SIL/Hal/Console/Console.hpp"
#endif

namespace ARK {
    static HAL::Console* CreateConsole() {
        #ifdef ARK_ARCH_PICO
            return new HAL::Pico::Console();
        #elif defined(ARK_ARCH_ESP32)
            return new HAL::Esp32::Console();
        #elif defined(ARK_ARCH_SIL)
            return new HAL::SIL::Console();
        #else
            #error "No architecture selected"
            return nullptr;
        #endif
    }

    HAL::Console& SystemConsole = *CreateConsole();
}
