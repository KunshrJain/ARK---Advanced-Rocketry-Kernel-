# 02 — Architecture

## The Philosophy: "One Codebase, Any Target"

ARK is built on a "Write Once, Run Anywhere" philosophy for avionics. The core logic of your flight software—State Machines, Kernels, FDIR—is completely decoupled from the hardware it runs on.

### The Targets

1.  **Microcontroller (Hardware)**: 
    *   **ESP32**: Uses the ESP-IDF framework.
    *   **RP2040 (Pico)**: Uses the Pico C SDK.
    *   The code is compiled into a binary firmware (`.bin` or `.uf2`) and flashed to the chip.
    *   **HAL**: Uses real hardware drivers (SPI, I2C, GPIO) to talk to sensors and servos.

2.  **SIL (Software In Loop)**:
    *   **PC Environment**: Runs as a standard C++ executable (`./Build/ARK_Avionics_SIL`) on your Linux/macOS/Windows machine.
    *   **HAL**: Uses "Mock" drivers.
        *   `GPIO`: Prints to console instead of toggling pins.
        *   `Flash`: Writes to a local file (`shadow.bin`) instead of EEPROM.
        *   `Time`: Uses system high-resolution clock.
    *   **Purpose**: Allows you to verify **logic**, **state transitions**, and **fault recovery** instantly without needing physical hardware.

## Main loop (SuperiorLoop)

The program runs one infinite loop in `ARK/Kernel/Loops/SuperiorLoop.cpp` which drives the three kernels.

## HAL (Hardware Abstraction Layer)

ARK abstracts hardware per target. Your User Code (and the Kernels) blindly interact with these interfaces:

-   **SystemTime**: Get timestamp, sleep.
-   **SystemClock**: CPU frequency settings.
-   **SystemConsole**: Print logs (UART on Hardware, Stdout on PC).
-   **SystemFlash**: Persist data (Flash mem on Hardware, `shadow.bin` on PC).
-   **SystemPower**: Voltage readings (ADC on Hardware, Mock data on PC).

When you build for `SIL`, CMake links the files in `ARK/Arch/SIL`. When you build for `PICO`, it links `ARK/Arch/Pico`. This seamless swap is key to the framework's robustness.
