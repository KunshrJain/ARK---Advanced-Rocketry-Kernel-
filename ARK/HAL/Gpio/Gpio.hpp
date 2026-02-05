#pragma once
#include <cstdint>

namespace ARK {
    namespace HAL {
        enum class PinMode {
            INPUT,
            OUTPUT,
            INPUT_PULLUP,
            INPUT_PULLDOWN
        };

        class GPIO {
        public:
            virtual ~GPIO() = default;

            virtual void Init(uint8_t pin, PinMode mode) = 0;
            virtual void Set(uint8_t pin, bool high) = 0;
            virtual bool Get(uint8_t pin) = 0;
            virtual void Toggle(uint8_t pin) = 0;
        };
    }
}
