#include "Watchdog.hpp"
#include "ARK/HAL/Console/Console.hpp"
#include <iostream>

namespace ARK {
    namespace HAL {
        namespace SIL {
            void Watchdog::Enable(uint32_t timeout_ms) {
                SystemConsole.Print("[SIL_WDT] Enabled with timeout: %d ms", timeout_ms);
            }

            void Watchdog::Feed() {
                // SystemConsole.Print("[SIL_WDT] Fed"); // Too spammy for logs
            }

            void Watchdog::Disable() {
                SystemConsole.Print("[SIL_WDT] Disabled");
            }
        }
    }
}
