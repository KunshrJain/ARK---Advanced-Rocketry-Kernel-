#include "ARK/HAL/Flash/Flash.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Flash/Flash.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Flash/Flash.hpp"
#elif defined(ARK_ARCH_SIL)
#include "ARK/Arch/SIL/Hal/Flash/Flash.hpp"
#endif

namespace ARK {
    HAL::Flash& SystemFlash =
#ifdef ARK_ARCH_PICO
        *new HAL::Pico::Flash();
#elif defined(ARK_ARCH_ESP32)
        *new HAL::Esp32::Flash();
#elif defined(ARK_ARCH_SIL)
        *new HAL::SIL::Flash();
#else
        #error "No architecture selected for Flash implementation"
#endif
}
