# Getting Started with ARK

This guide covers how to build and run the ARK Avionics framework for different targets:
1.  **SIL (Software In Loop)**: Runs on your PC for logic testing.
2.  **Pico (RP2040)**: Runs on Raspberry Pi Pico / RP2040 Zero.
3.  **ESP32**: Runs on ESP32 MCUs using ESP-IDF.

## Prerequisites

-   **CMake** (3.16+)
-   **GCC / G++**
-   **ESP-IDF v5.x** (for ESP32)
-   **Pico SDK** (for RP2040)

## Building the Project

We have provided a helper script in `Tools/build.sh` to manage builds in the `Build/` directory.

### 1. SIL (Software In Loop) Simulation

This runs the flight software logic on your computer.

```bash
./Tools/build.sh -t SIL
```

**Running the Simulation:**

```bash
./Build/ARK_Avionics_SIL
```

### 2. Building for Raspberry Pi Pico

Ensure your `PICO_SDK_PATH` environment variable is set.

```bash
export PICO_SDK_PATH=/path/to/pico-sdk
./Tools/build.sh -t PICO
```

**Flashing:**
Copy the `.uf2` file from `Build/ARK_Avionics.uf2` to your Pico drive.

### 3. Building for ESP32

Ensure you have sourced the ESP-IDF export script.

```bash
. $IDF_PATH/export.sh
./Tools/build.sh -t ESP32
```

**Flashing:**

```bash
cd Build
idf.py flash monitor
```

## Project Structure

-   **ARK/**: Core source code.
    -   `Arch/`: Architecture-specific implementations (SIL, Pico, ESP32).
    -   `HAL/`: Hardware Abstraction Layer interfaces.
    -   `Kernel/`: Core schedulers (SuperiorLoop, MicroKernels).
    -   `System/`: Drivers and system components.
-   **Configuration/**: Config files (`Config.hpp` logic, `sdkconfig`).
-   **Modules/**: External modules (e.g., WS2812).
-   **User/**: User-space code (`UserCode.cpp`) for custom logic.
