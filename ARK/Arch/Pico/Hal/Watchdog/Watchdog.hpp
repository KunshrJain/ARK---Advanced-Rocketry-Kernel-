#pragma once
#include "ARK/HAL/Watchdog/Watchdog.hpp"
#include "hardware/watchdog.h"

namespace ARK {
    namespace HAL {
        namespace Pico {
            class Watchdog : public ARK::HAL::Watchdog {
            public:
                void Enable(uint32_t timeout_ms) override {
                    watchdog_enable(timeout_ms, 1);
                }
                void Feed() override {
                    watchdog_update();
                }
                void Disable() override {
                    // Pico WDT cannot be disabled once enabled roughly speaking without reset
                }
            };
        }
    }
}
