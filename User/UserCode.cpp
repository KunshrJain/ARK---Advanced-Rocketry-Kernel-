#include "ARK/Ark.hpp"
#include "ARK/System/CommunicationProtocols/Gpio/Gpio.hpp"
#include "ARK/HAL/Time/Time.hpp"

#ifdef ARK_ARCH_PICO
#include "Modules/WS2812/WS2812.hpp"
#endif

#ifdef ARK_ARCH_PICO
#define PIN_NEOPIXEL 16
Modules::WS2812* onboardLed = nullptr;
#elif defined(ARK_ARCH_ESP32)
#define PIN_LED 2
ARK::GPIO espLed(PIN_LED);
#endif

void UserSetup() {
#ifdef ARK_ARCH_PICO
    onboardLed = new Modules::WS2812(pio0, PIN_NEOPIXEL, 1);
#elif defined(ARK_ARCH_ESP32)
    espLed.Mode(ARK::HAL::PinMode::OUTPUT);
#endif
}

void UserLoop() {
    static bool state = false;
    static uint64_t lastToggle = 0;
    
    uint64_t currentTime = ARK::SystemTime.GetMicros();

    // Toggle every 500ms
    if (currentTime - lastToggle >= 500000) {
        state = !state;
        
#ifdef ARK_ARCH_PICO
        if (onboardLed) {
            if (state) {
                onboardLed->SetPixel(0, 50, 0, 50); 
            } else {
                onboardLed->SetPixel(0, 0, 0, 0);
            }
            onboardLed->Show();
        }
#elif defined(ARK_ARCH_ESP32)
        espLed.Set(state);
#endif
        
        lastToggle = currentTime;
    }
}