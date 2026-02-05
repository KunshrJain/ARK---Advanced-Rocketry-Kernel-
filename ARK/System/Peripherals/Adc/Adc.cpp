#include "Adc.hpp"
#include "../../../Config.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Adc/Adc.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Adc/Adc.hpp"
#elif defined(ARK_ARCH_SIL)
#include "ARK/Arch/SIL/Hal/Adc/Adc.hpp"
#endif

namespace ARK {

    ADC::ADC(uint8_t pin) : _pin(pin) {
        #ifdef ARK_ARCH_PICO
            _hal = new HAL::Pico::Adc();
        #elif defined(ARK_ARCH_ESP32)
            _hal = new HAL::Esp32::Adc();
        #elif defined(ARK_ARCH_SIL)
            _hal = new HAL::SIL::Adc();
        #endif
    }

    ADC::~ADC() {
        if (_hal) delete _hal;
    }

    bool ADC::Init() {
        if (_hal) return _hal->Init(_pin);
        return false;
    }

    float ADC::ReadVoltage(float ref_voltage) {
        if (_hal) return _hal->ReadVoltage(ref_voltage);
        return 0.0f;
    }
    
    uint16_t ADC::ReadRaw() {
        if (_hal) return _hal->ReadRaw();
        return 0;
    }
}
