#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ARK/Ark.hpp"

extern "C" void app_main() {
    // Pin the Superior Loop to Core 1 to avoid WiFi/BT interference on Core 0
    xTaskCreatePinnedToCore(
        [](void*){ Setup(); }, 
        "SuperiorLoop", 8192, NULL, 10, NULL, 1
    );
}