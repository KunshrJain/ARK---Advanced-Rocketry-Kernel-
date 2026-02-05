#include "WS2812.hpp"
#include "ws2812.pio.h"

namespace Modules {
    WS2812::WS2812(PIO pio, uint8_t pin, uint8_t num_leds) : _pio(pio), _pin(pin), _num_leds(num_leds) {
        _buffer = new uint32_t[num_leds];
        
        uint offset = pio_add_program(pio, &ws2812_program);
        _sm = pio_claim_unused_sm(pio, true);
        ws2812_program_init(pio, _sm, offset, pin, 800000, false);
    }

    void WS2812::SetPixel(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
        if (index < _num_leds) {
            _buffer[index] = Urgb(r, g, b);
        }
    }

    void WS2812::Clear() {
        for (int i=0; i<_num_leds; i++) {
            _buffer[i] = 0;
        }
    }

    void WS2812::Show() {
        for (int i=0; i<_num_leds; i++) {
            pio_sm_put_blocking(_pio, _sm, _buffer[i] << 8u);
        }
    }

    uint32_t WS2812::Urgb(uint8_t r, uint8_t g, uint8_t b) {
        return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
    }
}
