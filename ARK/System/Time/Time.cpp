#include "ARK/HAL/Time/Time.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Time/Time.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Time/Time.hpp"
#elif defined(ARK_ARCH_SIL)
#include "ARK/Arch/SIL/Hal/Time/Time.hpp"
#endif

namespace ARK {
    HAL::Time& SystemTime =
#ifdef ARK_ARCH_PICO
        *new HAL::Pico::Time();
#elif defined(ARK_ARCH_ESP32)
        *new HAL::Esp32::Time();
#elif defined(ARK_ARCH_SIL)
        *new HAL::SIL::Time();
#else
        #error "No architecture selected for Time implementation"
#endif
}
