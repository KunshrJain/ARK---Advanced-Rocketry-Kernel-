#include "pico/stdlib.h"
#include "../../Kernel/Loops/SuperiorLoop.hpp"

int main() {
    stdio_init_all(); // Pico-specific peripheral init
    ARK::SuperiorLoop::Start(); 
    return 0;
}