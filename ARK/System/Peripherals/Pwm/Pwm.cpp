#include "Pwm.hpp"
#include "../../../Config.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/Pwm/Pwm.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/Pwm/Pwm.hpp"
#elif defined(ARK_ARCH_SIL)
#include "ARK/Arch/SIL/Hal/Pwm/Pwm.hpp"
#endif

namespace ARK {

    PWM::PWM(uint8_t pin) : _pin(pin) {
        #ifdef ARK_ARCH_PICO
            _hal = new HAL::Pico::Pwm();
        #elif defined(ARK_ARCH_ESP32)
            _hal = new HAL::Esp32::Pwm();
        #elif defined(ARK_ARCH_SIL)
            _hal = new HAL::SIL::Pwm();
        #endif
    }

    PWM::~PWM() {
        if (_hal) delete _hal;
    }

    void PWM::Init(uint32_t frequency_hz) {
        if (_hal) _hal->Init(_pin, frequency_hz);
    }

    void PWM::Write(float duty_cycle_percent) {
        if (_hal) _hal->Write(_pin, duty_cycle_percent);
    }

    void PWM::WriteUs(uint32_t microseconds) {
        if (_hal) _hal->WriteUs(_pin, microseconds);
    }
}
