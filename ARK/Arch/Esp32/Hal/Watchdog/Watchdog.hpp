#pragma once
#include "ARK/HAL/Watchdog/Watchdog.hpp"
#include "esp_task_wdt.h"

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            class Watchdog : public ARK::HAL::Watchdog {
            public:
                void Enable(uint32_t timeout_ms) override {
                    // ESP-IDF 5.x WDT setup would go here
                    // Simple placeholder for now
                }
                void Feed() override {
                    esp_task_wdt_reset();
                }
                void Disable() override {
                }
            };
        }
    }
}
