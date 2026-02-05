#include "Watchdog.hpp"
#include "../../Config.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Watchdog/Watchdog.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Watchdog/Watchdog.hpp"
#elif defined(ARK_ARCH_SIL)
#include "ARK/Arch/SIL/Hal/Watchdog/Watchdog.hpp"
#endif

namespace ARK {
    HAL::Watchdog& SystemWatchdog =
#ifdef ARK_ARCH_PICO
        *new HAL::Pico::Watchdog();
#elif defined(ARK_ARCH_ESP32)
        *new HAL::Esp32::Watchdog();
#elif defined(ARK_ARCH_SIL)
        *new HAL::SIL::Watchdog();
#else
        #error "No architecture selected for Watchdog implementation"
#endif
}
