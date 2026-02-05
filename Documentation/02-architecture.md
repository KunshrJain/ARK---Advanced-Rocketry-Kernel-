# 02 — Architecture

## Main loop (SuperiorLoop)

The program runs one infinite loop in `ARK/Kernel/Loops/SuperiorLoop.cpp`:

```
Start()
  → Apply clock, init console, init flash
  → Load shadow from flash (or fresh start)
  → Init SystemKernel, ModulesKernel, UserKernel
  → Run()

Run()
  → while (true) {
        run ModulesKernel when its period has elapsed
        run SystemKernel when its period has elapsed
        run UserKernel when its period has elapsed
        save shadow to flash if state changed
        wait until next frame (tick period)
     }
```


## Three kernels

Each kernel runs at its **own rate** (set in `Config.hpp`). The main loop checks the time and runs a kernel only when enough time has passed since it last ran.

| Kernel | Config name | Default rate | What it does |
|--------|--------------|--------------|--------------|
| **ModulesKernel** | MODULES_KERNEL_FREQUENCY | 200 Hz | Updates sensors / modules (baro, IMU, etc.). |
| **SystemKernel** | SYSTEM_KERNEL_FREQUENCY | 300 Hz | FDIR check, shadow update, **UserEvaluateTransitions()**, then the state handler (HandleBoot, HandleLaunch, …). |
| **UserKernel** | USER_KERNEL_FREQUENCY | 200 Hz | Calls your `UserLoop()`. |

So **your transition logic** runs inside **SystemKernel**, at **SYSTEM_KERNEL_FREQUENCY** (e.g. 300 Hz). It does **not** run inside UserLoop; UserLoop is where you read sensors and fill `g_flightData`.


## Order in one frame

Within a single frame, the order is:

1. **ModulesKernel** (if due) — e.g. read baro, IMU.
2. **SystemKernel** (if due):
   - FDIR::CheckHealth()
   - Update shadow (flight state, faults, last altitude)
   - If critical fault → SetState(FAILSAFE)
   - Copy altitude into shadow, set g_flightData.timeUs
   - **UserEvaluateTransitions(FlightManager)** ← your “when to change state” logic
   - Run the handler for the **current** state (e.g. HandleAscent)
3. **UserKernel** (if due) — **UserLoop()** (sensors, GPIO, fill g_flightData).
4. If flight state changed, save shadow to flash.
5. Wait until next frame.

So: sensors (Modules) → your transitions + state handler (System) → your loop (User). You fill `g_flightData` in UserLoop; the next time SystemKernel runs it will use that data in `UserEvaluateTransitions()`.


## State machine

- **StatesManager** holds the current **FlightState** (BOOT, IDLE, ARMED, LAUNCH, ASCENT, …).
- **UserEvaluateTransitions()** is where you call **SetState(...)** when your conditions are met.
- After **UserEvaluateTransitions()** returns, the framework runs the **handler** for the current state (e.g. HandleLaunch, HandleApogee). So if you set state to APOGEE, HandleApogee() runs in the same SystemKernel tick.


## HAL (Hardware Abstraction Layer)

ARK abstracts hardware per target:

- **Time** — microsecond clock, sleep, delay-until.
- **Clock** — CPU frequency, tick period.
- **Console** — init, print, success/error.
- **Flash** — init, commit shadow, recover shadow.

Your code uses **SystemTime**, **SystemConsole**, **SystemFlash**, etc.; the right implementation (Pico, ESP32, SIL) is linked by the build.

Next: [03-build-and-run](03-build-and-run.md) — how to build and run.
