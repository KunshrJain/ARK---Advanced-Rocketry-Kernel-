#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../../Kernel/Loops/SuperiorLoop.hpp"

extern "C" void app_main() {
    // Pin the Superior Loop to Core 1 to avoid WiFi/BT interference on Core 0
    xTaskCreatePinnedToCore(
        [](void*){ ARK::SuperiorLoop::Start(); }, 
        "SuperiorLoop", 8192, NULL, 10, NULL, 1
    );
}