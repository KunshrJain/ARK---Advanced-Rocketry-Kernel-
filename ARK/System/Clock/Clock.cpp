#include "ARK/HAL/Clock/Clock.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Clock/Clock.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Clock/Clock.hpp"
#elif defined(ARK_ARCH_SIL)
#include "ARK/Arch/SIL/Hal/Clock/Clock.hpp"
#endif

namespace ARK {
    HAL::Clock& SystemClock =
#ifdef ARK_ARCH_PICO
        *new HAL::Pico::Clock();
#elif defined(ARK_ARCH_ESP32)
        *new HAL::Esp32::Clock();
#elif defined(ARK_ARCH_SIL)
        *new HAL::SIL::Clock();
#else
        #error "No architecture selected for Clock implementation"
#endif
}
