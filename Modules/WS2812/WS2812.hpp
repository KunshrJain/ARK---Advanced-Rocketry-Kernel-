#pragma once

#include "ARK/Ark.hpp"

#ifdef ARK_ARCH_PICO
#include "pico/stdlib.h"
#include "hardware/pio.h"

namespace Modules {
    class WS2812 {
    public:
        WS2812(PIO pio, uint8_t pin, uint8_t num_leds);
        void SetPixel(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
        void Show();
        void Clear();

    private:
        PIO _pio;
        uint _sm;
        uint8_t _pin;
        uint8_t _num_leds;
        uint32_t *_buffer;
        
        uint32_t Urgb(uint8_t r, uint8_t g, uint8_t b);
    };
}
#endif
