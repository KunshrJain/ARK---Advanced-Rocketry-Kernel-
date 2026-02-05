# 04 — User Guide

Welcome to ARK! This guide explains how to program your rocket's behavior. We have simplified everything so you can focus on the logic.

## 🚀 The Simple API

Just use the `ARK` namespace. It gives you direct access to everything.

### Core Functions

| Function | What it does |
| :--- | :--- |
| `ARK::Altitude()` | Returns altitude in meters (AGL). |
| `ARK::Acceleration()` | Returns total acceleration in m/s². |
| `ARK::Velocity()` | Returns vertical velocity in m/s. |
| `ARK::Time()` | Returns system time in microseconds. |
| `ARK::IsState(STATE)` | Returns `true` if the rocket is in the specified state. |
| `ARK::SetState(STATE)`| Forces the rocket into a specific state. |

### Helper Actions

Shortcuts for common state changes:
*   `ARK::Launch()` → Go to LAUNCH state.
*   `ARK::Burnout()` → Go to BURNOUT state.
*   `ARK::Apogee()` → Go to APOGEE state.
*   `ARK::DeployDrogue()` → Go to DROGUE state.
*   `ARK::DeployMain()` → Go to MAIN_DEPLOYMENT state.

---

## 📂 Where to Write Code

You only need to care about the **User** folder.

### 1. `User/UserTransitions.cpp` (The Brain)
This file controls **state changes**. It runs constantly. You check conditions (like altitude or speed) and tell the rocket to change states.

We have provided a template with all 20 possible states:

*   **BOOT** (0): First power on.
*   **INITIALIZING** (1): Setting up drivers.
*   **CALIBRATION** (2): Calibrating sensors (gyro/accel biases).
*   **IDLE** (3): Sitting on the pad, waiting.
*   **PRE_ARM** (4): Safety check before arming.
*   **ARMED** (5): Ready for launch.
*   **LAUNCH** (6): Liftoff detected!
*   **ASCENT** (7): Powered flight (motor burning).
*   **BURNOUT** (8): Motor stopped.
*   **SEPARATION** (9): Optional stage separation or payload release.
*   **CRUISING** (10): Optional powered cruise phase.
*   **COASTING** (11): Coasting upwards to apogee.
*   **APOGEE** (12): Highest point reached.
*   **DROGUE** (13): First parachute event.
*   **DOUBLE_DEPLOYMENT** (14): Waiting for main chute altitude.
*   **MAIN_DEPLOYMENT** (15): Main chute released.
*   **DESCENT** (16): Falling under main canopy.
*   **LANDING_DETECTION** (17): Checking if we have hit the ground.
*   **LANDED** (18): Safe on the ground.
*   **FAILSAFE** (19): Something went wrong (abort/error).

**How to use it:**
Find the state you are in, and add an `if` statement for when to leave it.
```cpp
if (ARK::IsState(FlightState::ARMED)) {
    if (ARK::Acceleration() > 30.0) {
        ARK::Launch();
    }
}
```

### 2. `User/UserCode.cpp` (The Body)
This file handles **sensors and devices**.
*   **UserSetup()**: Runs once. Initialize your IMU, Barometer, GPS, servos, etc.
*   **UserLoop()**: Runs repeatedly. Read your sensors and update usage.

---

## Configuration (`User/UserConfig.hpp`)
Contains simpler numbers you might want to tune, like launch thresholds. You can use these Macros in your code, or just ignore them and write numbers directly in `UserTransitions.cpp` if you prefer.

**Next:** [Flight Walkthrough](05-use-case-flight.md)
