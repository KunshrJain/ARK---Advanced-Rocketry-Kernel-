#pragma once
#include <cstdint>

namespace ARK {
    namespace HAL {
        class Adc {
        public:
            virtual ~Adc() = default;
            virtual bool Init(uint8_t pin) = 0;
            virtual uint16_t ReadRaw() = 0;
            virtual float ReadVoltage(float ref_voltage) = 0;
        };
    }
}
