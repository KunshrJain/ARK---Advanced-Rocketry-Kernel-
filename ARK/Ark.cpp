#include "Ark.hpp"
#include "ARK/Kernel/Loops/SuperiorLoop.hpp"
#include "ARK/HAL/Console/Console.hpp"

// Main entry point for the ARK Framework.
void Setup() {
    // Start the main kernel loop.
    // This function initializes all drivers and kernels and then enters an infinite loop.
    ARK::SuperiorLoop::Start();
}

// This function will never be reached because SuperiorLoop::Start() contains an infinite loop.
void Loop() {
    ARK::SystemConsole.Error("FATAL: Reached empty main loop. SuperiorLoop exited unexpectedly.");
}
