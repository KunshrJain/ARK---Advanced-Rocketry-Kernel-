<div align="center">

<img src="Documentation/public/ark_logo.png" alt="ARK Logo" width="400"/>

<h3>Advanced Rocketry Kernel (ARK)</h3>

<p>
  <img src="https://img.shields.io/badge/Platform-RP2040%20%7C%20ESP32-blue.svg" alt="Platform"/>
  <img src="https://img.shields.io/badge/Language-C++17-orange.svg" alt="Language"/>
  <img src="https://img.shields.io/badge/Build-CMake-green.svg" alt="Build System"/>
  <img src="https://img.shields.io/badge/Team-Ignition-red.svg" alt="Team"/>
</p>

<p><em>A high-performance, crash-resilient, multi-rate RTOS kernel designed for competitive model rocketry and avionics.</em></p>

<p>
  <a href="#core-architecture">Architecture</a> •
  <a href="#fdir--shadow-state">FDIR & Shadow</a> •
  <a href="#getting-started">Getting Started</a> •
  <a href="#python-tools-suite">Tools</a>
</p>

<hr/>

<img src="Documentation/public/ign_logo.png" alt="Team Ignition Logo" width="150"/>

<p><strong>Lead Architect: Kunsh Jain</strong><br/>
<em>Developed for Team Ignition, VIT Chennai</em></p>

</div>

---

## Overview

**ARK (Advanced Rocketry Kernel)** is a modular Avionics Software Framework. It provides a deterministic, real-time operating environment for model rockets, ensuring that critical flight control loops execute with microsecond precision while maintaining robust fault tolerance.

ARK is built to be **Hardware Agnostic**, running seamlessly on both the **Raspberry Pi Pico (RP2040)** and the **ESP32**. The architecture separates the hardware abstraction layer (HAL) from the flight logic, allowing for rapid porting to new platforms.

## Key Features

*   **Multi-Rate Scheduler**: The "Superior Loop" manages three distinct kernel frequencies (Modules: 200Hz, System: 300Hz, User: 200Hz) to optimize CPU time for sensor fusion, state estimation, and mission logic.
*   **FDIR Engine**: A dedicated Fault Detection, Isolation, and Recovery system monitors 8 critical system health bits in real-time, triggering safe-state transitions upon failure.
*   **Shadow State Persistence**: Flight state and critical telemetry are mirrored to non-volatile memory, allowing the system to resume the correct flight phase instantly after a mid-air reboot.
*   **Space-Efficient Compilation**: The build system utilizes aggressive dead-code stripping (`-ffunction-sections -fdata-sections -Wl,--gc-sections`) to ensure only the code required for the current configuration is flashed to memory.

---

## Core Architecture

The system is divided into three micro-kernels:

| Kernel | Frequency | Responsibility |
| :--- | :--- | :--- |
| **Modules** | 200 Hz | Hardware drivers, Sensor drivers (IMU, Baro, GPS), and raw data acquisition. |
| **System** | 300 Hz | State Machine management, FDIR Engine, Health Monitoring, and Shadow State management. |
| **User** | 200 Hz | Mission-specific logic, PID control loops, Apogee detection algorithms, and Payload control. |

---

## Getting Started

### Prerequisites

*   **Python 3.x**
*   **CMake** (3.16+)
*   **ARM GCC Toolchain** (for RP2040)
*   **ESP-IDF** (Automatically managed for ESP32)

### Directory Structure

*   `ARK/`: Core kernel source code (HAL and System layers).
*   `Modules/`: Peripheral and Sensor drivers.
*   `User/`: Mission-specific implementations.
*   `Tools/`: Development utilities.
*   `Build/`: Generated build artifacts.
*   `Documentation/`: Detailed technical documentation.

---

## Python Tools Suite

The project includes a suite of Python tools to streamline the development workflow.

### 1. Build System (`Tools/Build.py`)

Handles toolchain setup and compilation.

```bash
# Build for Raspberry Pi Pico
python3 Tools/Build.py pico

# Build for ESP32
python3 Tools/Build.py esp32

# Clean build artifacts
python3 Tools/Build.py clean
```

### 2. Upload Tool (`Tools/Upload.py`)

Flashes the binary to the target hardware.

```bash
python3 Tools/Upload.py pico
python3 Tools/Upload.py esp32
```

### 3. Configuration Manager (`Tools/GenerateConfig.py`)

Interactively toggles system features and constants in `Config.hpp`.

```bash
python3 Tools/GenerateConfig.py
```

---

## Contributing

1.  Fork the repository.
2.  Create a feature branch.
3.  Ensure code adheres to the Superior Loop logic (non-blocking).
4.  Submit a Pull Request.

<div align="center">
<p>Distributed under the GNU General Public License v3.0.</p>
<p>Copyright © 2026 Team Ignition Software Department</p>
</div>