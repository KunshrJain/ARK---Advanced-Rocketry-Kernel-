# 01 — Overview

## What is ARK?

ARK is an **embedded framework** for building flight-computer software for rockets. It gives you:

- A **main loop** that runs at a fixed rate.
- **Three kernels** that run at different rates: Modules (sensors), System (state machine + your transitions), User (your code).
- A **flight state machine** (BOOT → IDLE → ARMED → LAUNCH → … → LANDED / FAILSAFE).
- **User-defined state transitions**: you decide when to move from one state to the next (e.g. when acceleration exceeds a threshold = launch, when velocity goes negative = apogee).


## Supported hardware

| Target | Description |
|--------|-------------|
| **SIL** | Software-in-the-loop: runs on your PC, no hardware. Good for testing logic. |
| **Pico** | Raspberry Pi Pico. |
| **ESP32** | ESP32 with ESP-IDF. |


## High-level flow

1. **Power on** → ARK starts, loads saved state from flash (if any), then enters the main loop.
2. **Main loop** runs forever. Each “frame” it:
   - Runs **ModulesKernel** (e.g. read barometer, IMU) at one rate.
   - Runs **SystemKernel** (FDIR, **your transition logic**, state handlers) at another rate.
   - Runs **UserKernel** (your `UserLoop()`) at another rate.
   - Waits until the next frame so the loop keeps a fixed period.
3. **Your job** in the `User/` folder:
   - Fill **FlightData** (altitude, acceleration, velocity, time) from your sensors in `UserLoop()`.
   - Define **when** to change state in `UserTransitions.cpp` (e.g. “go to LAUNCH when accel > 20 m/s²”).
   - Optionally add one-time setup in `UserSetup()` and per-state actions in the state handlers in `States.cpp`.


## Where your code lives

| Place | Purpose |
|-------|---------|
| **User/UserCode.cpp** | `UserSetup()` once at start, `UserLoop()` every user tick. Read sensors, fill `g_flightData`, GPIO, etc. |
| **User/UserConfig.hpp** | Numbers you tune: launch accel threshold, burnout time, apogee velocity, main deploy altitude, etc. |
| **User/UserTransitions.cpp** | `UserEvaluateTransitions()`: given current state and `g_flightData`, call `flightManager.SetState(...)` when your conditions are met. |
| **ARK/Kernel/StateMachine/States.cpp** | Handlers for each state (HandleBoot, HandleLaunch, …). Add actions when entering a state (e.g. fire drogue). |

Next: [02-architecture](02-architecture.md) — how the main loop and kernels work.
