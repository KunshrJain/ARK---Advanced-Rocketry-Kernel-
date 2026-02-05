#include "Power.hpp"
#include "ARK/HAL/Console/Console.hpp"

#ifdef ARK_ARCH_PICO
#include "pico/stdlib.h"
#include "hardware/adc.h"
#endif



namespace ARK {
    uint8_t Power::adc_pin;
    float Power::voltage_ref;
    float Power::resistor1;
    float Power::resistor2;

#ifdef ARK_ARCH_ESP32
#include "esp_adc/adc_oneshot.h"

    static adc_oneshot_unit_handle_t adc_handle = nullptr;
    static adc_channel_t adc_ch;

    // Helper to convert GPIO pin to ADC1 channel
    static bool gpio_to_adc1_channel(uint8_t pin, adc_channel_t* channel) {
        switch(pin) {
            case 36: *channel = ADC_CHANNEL_0; return true;
            case 37: *channel = ADC_CHANNEL_1; return true;
            case 38: *channel = ADC_CHANNEL_2; return true;
            case 39: *channel = ADC_CHANNEL_3; return true;
            case 32: *channel = ADC_CHANNEL_4; return true;
            case 33: *channel = ADC_CHANNEL_5; return true;
            case 34: *channel = ADC_CHANNEL_6; return true;
            case 35: *channel = ADC_CHANNEL_7; return true;
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
        if (adc_handle == nullptr) {
            adc_oneshot_unit_init_cfg_t init_config = {
                .unit_id = ADC_UNIT_1,
                .clk_src = (adc_oneshot_clk_src_t)0,
                .ulp_mode = ADC_ULP_MODE_DISABLE, 
            };
            ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));
        }

        if (gpio_to_adc1_channel(adc_pin, &adc_ch)) {
            adc_oneshot_chan_cfg_t config = {
                .atten = ADC_ATTEN_DB_12,
                .bitwidth = ADC_BITWIDTH_DEFAULT,
            };
            ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, adc_ch, &config));
        }
#endif

#ifdef ARK_ARCH_SIL
        SystemConsole.Print("[SIL_POWER] Setup on pin: %d", pin);
#endif
    }

    float Power::GetVoltage() {
        int adc_value = 0;
#ifdef ARK_ARCH_PICO
        adc_value = adc_read();
        // Calculate voltage based on voltage divider
        float adc_voltage = adc_value * (voltage_ref / 4095.0);
        float battery_voltage = adc_voltage * ((resistor1 + resistor2) / resistor2);
        return battery_voltage;
#endif

#ifdef ARK_ARCH_ESP32
        if (adc_handle) {
             ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, adc_ch, &adc_value));
        }
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
