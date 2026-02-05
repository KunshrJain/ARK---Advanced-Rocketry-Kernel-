#include "Power.hpp"
#include "ARK/HAL/Console/Console.hpp"
#include "ARK/System/Peripherals/Adc/Adc.hpp"

// We no longer need direct hardware includes here!
// The ADC System Wrapper handles it.

namespace ARK {
    uint8_t Power::adc_pin;
    float Power::voltage_ref;
    float Power::resistor1;
    float Power::resistor2;
    static ARK::ADC* _powerAdc = nullptr;

    void Power::Setup(uint8_t pin, float v_ref, float r1, float r2) {
        adc_pin = pin;
        voltage_ref = v_ref;
        resistor1 = r1;
        resistor2 = r2;

        _powerAdc = new ARK::ADC(pin);
        if (!_powerAdc->Init()) {
            SystemConsole.Error("[Power] Failed to Init ADC on Pin " + std::to_string(pin));
        } else {
            SystemConsole.Print("[Power] Initialized on Pin %d", pin);
        }
    }

    float Power::GetVoltage() {
        if (!_powerAdc) return 0.0f;
        
        float adc_voltage = _powerAdc->ReadVoltage(voltage_ref);
        // V_out = V_in * (R2 / (R1 + R2))
        // V_in = V_out * ((R1 + R2) / R2)
        float battery_voltage = adc_voltage * ((resistor1 + resistor2) / resistor2);
        
        return battery_voltage;
    }
}
