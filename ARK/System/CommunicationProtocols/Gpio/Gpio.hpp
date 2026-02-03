#pragma once
#include <stdint.h>

namespace ARK {
    namespace GPIO {
        void Setup(uint8_t pin, bool isOutput);
        void Write(uint8_t pin, bool value);
        bool Read(uint8_t pin);
    }
}