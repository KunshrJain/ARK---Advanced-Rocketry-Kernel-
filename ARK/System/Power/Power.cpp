#include "Power.hpp"
#include "ARK/HAL/Console/Console.hpp"

#ifdef ARK_ARCH_PICO
#include "pico/stdlib.h"
#include "hardware/adc.h"
#endif

#ifdef ARK_ARCH_ESP32
#include "driver/adc.h"
#endif

namespace ARK {
    uint8_t Power::adc_pin;
    float Power::voltage_ref;
    float Power::resistor1;
    float Power::resistor2;

#ifdef ARK_ARCH_ESP32
    static adc1_channel_t adc_ch;

    // Helper to convert GPIO pin to ADC1 channel
    static bool gpio_to_adc1_channel(uint8_t pin, adc1_channel_t* channel) {
        switch(pin) {
            case 36: *channel = ADC1_CHANNEL_0; return true;
            case 37: *channel = ADC1_CHANNEL_1; return true;
            case 38: *channel = ADC1_CHANNEL_2; return true;
            case 39: *channel = ADC1_CHANNEL_3; return true;
            case 32: *channel = ADC1_CHANNEL_4; return true;
            case 33: *channel = ADC1_CHANNEL_5; return true;
            case 34: *channel = ADC1_CHANNEL_6; return true;
            case 35: *channel = ADC1_CHANNEL_7; return true;
            default: return false;
        }
    }
#endif

    void Power::Setup(uint8_t pin, float v_ref, float r1, float r2) {
        adc_pin = pin;
        voltage_ref = v_ref;
        resistor1 = r1;
        resistor2 = r2;

#ifdef ARK_ARCH_PICO
        adc_init();
        adc_gpio_init(adc_pin);
        adc_select_input(adc_pin - 26); // ADC pins are 26, 27, 28
#endif

#ifdef ARK_ARCH_ESP32
        adc1_config_width(ADC_WIDTH_BIT_12);
        if (gpio_to_adc1_channel(adc_pin, &adc_ch)) {
            adc1_config_channel_atten(adc_ch, ADC_ATTEN_DB_11);
        }
#endif

#ifdef ARK_ARCH_SIL
        SystemConsole.Print("[SIL_POWER] Setup on pin: %d", pin);
#endif
    }

    float Power::GetVoltage() {
        uint16_t adc_value = 0;
#ifdef ARK_ARCH_PICO
        adc_value = adc_read();
        // Calculate voltage based on voltage divider
        float adc_voltage = adc_value * (voltage_ref / 4095.0);
        float battery_voltage = adc_voltage * ((resistor1 + resistor2) / resistor2);
        return battery_voltage;
#endif

#ifdef ARK_ARCH_ESP32
        adc_value = adc1_get_raw(adc_ch);
        // Calculate voltage based on voltage divider
        float adc_voltage = adc_value * (voltage_ref / 4095.0);
        float battery_voltage = adc_voltage * ((resistor1 + resistor2) / resistor2);
        return battery_voltage;
#endif

#ifdef ARK_ARCH_SIL
        SystemConsole.Print("[SIL_POWER] Getting voltage.");
        return 4.2; // Return a dummy voltage
#endif
        return 0.0;
    }
}
