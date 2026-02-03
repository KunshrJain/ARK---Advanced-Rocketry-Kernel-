#pragma once
#include <cstdint>

namespace ARK {
    class Power {
    public:
        static void Setup(uint8_t pin, float v_ref, float r1, float r2);
        static float GetVoltage();
    private:
        static uint8_t adc_pin;
        static float voltage_ref;
        static float resistor1;
        static float resistor2;
    };
}
