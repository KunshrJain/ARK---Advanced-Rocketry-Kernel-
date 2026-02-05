#pragma once
#include <cstdint>

namespace ARK {
    namespace Arch {
        namespace SIL {
            class PinCheck {
            public:
                static bool IsValidADC(uint8_t pin) { return true; }
                static bool IsValidPWM(uint8_t pin) { return true; }
            };
        }
    }
}
