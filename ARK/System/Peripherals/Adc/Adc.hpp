#pragma once
#include <cstdint>
#include "ARK/HAL/Adc/Adc.hpp"

namespace ARK {
    class ADC {
    public:
        ADC(uint8_t pin);
        ~ADC();

        bool Init(); // Retruns false if pin invalid
        float ReadVoltage(float ref_voltage = 3.3f);
        uint16_t ReadRaw();

    private:
        uint8_t _pin;
        HAL::Adc* _hal = nullptr;
    };
}
