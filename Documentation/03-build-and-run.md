# 03 — Build and Run

We recommend using the Python Tools suite for a seamless experience.

## Prerequisites

- **Python 3.x**
- **CMake** 3.16 or newer
- **C++14** toolchain (ARM GCC for Pico)
- **ESP-IDF** (Auto-installed by Build.py for ESP32)

---

## 1. Using Python Tools (Recommended)

Run these commands from the **project root**.

### Build
```bash
# For Raspberry Pi Pico
python3 Tools/Build.py pico

# For ESP32
python3 Tools/Build.py esp32
```

### Upload / Flash
```bash
# For Raspberry Pi Pico (Auto-detects USB Mass Storage)
python3 Tools/Upload.py pico

# For ESP32 (Auto-detects Serial Port)
python3 Tools/Upload.py esp32
```

---

## 2. Advanced / Manual Build

If you prefer using CMake directly, you must first set up your environment variables.

### Environment Setup
The build tools generate a helper script at `Build/env.sh`. Source it to set `PICO_SDK_PATH` or `IDF_PATH`.

```bash
# Generate the script first (runs setup logic)
python3 Tools/SetupEnv.py

# Activate environment
source Build/env.sh
```

### Manual Pico Build
```bash
mkdir -p Build/Temp/ManualPico
cd Build/Temp/ManualPico
cmake ../../.. -DARCH_TARGET=PICO
make -j4
# Binary is at ARK_Avionics.uf2
```

### Manual ESP32 Build
```bash
# Ensure you have sourced Build/env.sh or your own IDF export
mkdir -p Build/Temp/ManualEsp32
cd Build/Temp/ManualEsp32
cmake ../../.. -DARCH_TARGET=ESP32 -DCMAKE_TOOLCHAIN_FILE=$IDF_PATH/tools/cmake/toolchain-esp32.cmake -DTARGET=esp32
cmake --build .
```

---

## Config.hpp

- **Config.hpp** at the project root holds system and kernel settings.
- Edit interactively: `python3 Tools/GenerateConfig.py`
- **User/UserConfig.hpp** holds flight thresholds.

Next: [04-user-guide](04-user-guide.md)

