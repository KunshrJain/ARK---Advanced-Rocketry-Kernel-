# 06 — States Reference

All flight states, where they run, and typical transitions you define in **UserTransitions.cpp**.


## State list (enum order)

| # | State | Typical “from” | Typical “to” (you define in UserTransitions.cpp) |
|---|-------|----------------|---------------------------------------------------|
| 0 | **BOOT** | (start / reset) | INITIALIZING when ready |
| 1 | **INITIALIZING** | BOOT | CALIBRATION or IDLE when init done |
| 2 | **CALIBRATION** | INITIALIZING | IDLE when cal done |
| 3 | **IDLE** | CALIBRATION, or after LANDED | PRE_ARM when arm button / command |
| 4 | **PRE_ARM** | IDLE | ARMED when prearm checks OK |
| 5 | **ARMED** | PRE_ARM | LAUNCH when accel > threshold (or liftoff switch) |
| 6 | **LAUNCH** | ARMED | ASCENT (template does this immediately; you can add delay) |
| 7 | **ASCENT** | LAUNCH | BURNOUT when time or accel drop |
| 8 | **BURNOUT** | ASCENT | COASTING (template does immediately) or SEPARATION |
| 9 | **SEPARATION** | BURNOUT (if staged) | CRUISING or COASTING |
| 10 | **CRUISING** | SEPARATION | COASTING or APOGEE when your condition |
| 11 | **COASTING** | BURNOUT, SEPARATION, or CRUISING | APOGEE when velocity ≤ threshold |
| 12 | **APOGEE** | COASTING | DROGUE (fire drogue) |
| 13 | **DROGUE** | APOGEE | DOUBLE_DEPLOYMENT (template does immediately) |
| 14 | **DOUBLE_DEPLOYMENT** | DROGUE | MAIN_DEPLOYMENT (template does immediately) |
| 15 | **MAIN_DEPLOYMENT** | DOUBLE_DEPLOYMENT | DESCENT when altitude ≤ threshold |
| 16 | **DESCENT** | MAIN_DEPLOYMENT | LANDING_DETECTION (template does immediately) |
| 17 | **LANDING_DETECTION** | DESCENT | LANDED when your “landed” condition |
| 18 | **LANDED** | LANDING_DETECTION | (terminal; or IDLE for next flight if you want) |
| 19 | **FAILSAFE** | any (set by framework on critical fault) | (terminal; or IDLE if you allow recovery) |


## Where each state is handled

- **UserTransitions.cpp** — You add **when** to leave each state (conditions + **SetState(...)**).
- **ARK/Kernel/StateMachine/States.cpp** — Handlers **HandleBoot()**, **HandleLaunch()**, **HandleApogee()**, etc. Run **after** UserEvaluateTransitions in the same SystemKernel tick. Use them for **actions** (e.g. fire drogue in HandleApogee, fire main in HandleMainDeployment, blink LED in HandleIdle).


## Data you use in UserTransitions

All from **ARK::g_flightData** (you fill in **UserLoop()** except timeUs and launchTimeUs):

| Field | Type | Set by | Use for |
|-------|------|--------|---------|
| timeUs | uint64_t | Framework before UserEvaluateTransitions | Current time (µs) |
| launchTimeUs | uint64_t | You (e.g. in LAUNCH case when setting ASCENT) | Time since launch = timeUs - launchTimeUs |
| altitudeM | float | You (baro) | Main deploy, landed detection |
| accelMps2 | float | You (IMU) | Launch detect, burnout |
| velocityMps | float | You (baro derivative or IMU) | Apogee (negative = descending) |
| updated | bool | You | Optional “new data” flag |


## Config numbers (UserConfig.hpp)

| Define | Meaning | Example |
|--------|---------|---------|
| USER_LAUNCH_ACCEL_THRESHOLD_MPS2 | Accel (m/s²) to detect liftoff | 20.0f |
| USER_BURNOUT_ACCEL_THRESHOLD_MPS2 | Accel below this = burnout (if not using time) | 5.0f |
| USER_BURNOUT_TIME_AFTER_LAUNCH_US | µs after launch to go to BURNOUT | 5000000ULL (5 s) |
| USER_APOGEE_VELOCITY_THRESHOLD_MPS | Velocity (m/s) at/below which apogee | -2.0f |
| USER_MAIN_DEPLOY_ALTITUDE_M | Altitude (m) below which to deploy main | 300.0f |
| USER_LANDED_ALTITUDE_STABLE_M | Optional: altitude stability for landed | 0.5f |
| USER_LANDED_TIME_STABLE_US | Optional: time stable for landed | 2000000ULL |
| USER_USE_ACCEL_LAUNCH | 1 = use accel for launch detect | 1 |
| USER_USE_TIME_BURNOUT | 1 = use time for burnout; 0 = use accel | 1 |
| USER_USE_ALTITUDE_APOGEE | 1 = use velocity for apogee | 1 |


## Loop constraints (reminder)

- **UserEvaluateTransitions** runs at **SYSTEM_KERNEL_FREQUENCY** (e.g. 300 Hz), not every frame and not from UserLoop.
- **UserLoop** runs at **USER_KERNEL_FREQUENCY** (e.g. 200 Hz). Fill **g_flightData** there; the next SystemKernel tick will use it in **UserEvaluateTransitions**.

Back to [Documentation index](README.md).
