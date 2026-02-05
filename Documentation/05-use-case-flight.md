# 05 — Full Flight Walkthrough

This guide explains a typical flight path using the ARK Simple API.

## The Standard Flight Path

Most rockets will follow this path. You don't have to use every state, but this is the standard flow.

### Phase 1: Ground Operations

1.  **BOOT** → **INITIALIZING** → **CALIBRATION**
    *   *What happens:* ARK starts up, checks memory, and calibrates the IMU (don't move the rocket!).
    *   *Your Code:* Usually nothing. Transitions happen automatically when tasks complete.
2.  **IDLE**
    *   *What happens:* Rocket is calibrated and sitting on the pad.
    *   *Your Code:* You might wait for a "Go" signal from the radio to move to PRE_ARM.
3.  **PRE_ARM**
    *   *What happens:* Fast blinking LED? Siren? Final checks?
    *   *Your Code:* Check battery voltage or GPS lock. If good, go to ARMED.
4.  **ARMED**
    *   *What happens:* Igniters are live. Waiting for liftoff.
    *   *Your Code:* Monitor `ARK::Acceleration()`. If it exceeds your threshold (e.g. 2g), call `ARK::Launch()`.

### Phase 2: Powered Flight

5.  **LAUNCH** (Momentary)
    *   *What happens:* We just detected liftoff.
    *   *Your Code:* Automatically goes to ASCENT immediately. Use this to mark the `launchTime`.
6.  **ASCENT**
    *   *What happens:* Motor is burning. Velocity is increasing.
    *   *Your Code:* Check for **Burnout**. This happens when acceleration drops (motor stops pushing) or a timer expires. Call `ARK::Burnout()`.
7.  **SEPARATION** (Optional)
    *   *What happens:* If you have a booster stage, it drops off here.
    *   *Your Code:* Fire separation charges. Then go to COASTING.

### Phase 3: Coasting & Apogee

8.  **COASTING**
    *   *What happens:* Motor is off. Rocket is trading speed for altitude.
    *   *Your Code:* Watch `ARK::Velocity()`. When it drops to near 0 (or becomes negative), we are at the top. Call `ARK::Apogee()`.
9.  **APOGEE**
    *   *What happens:* Top of the flight.
    *   *Your Code:* Usually triggers `ARK::DeployDrogue()` immediately.

### Phase 4: Recovery

10. **DROGUE**
    *   *What happens:* Small parachute is out.
    *   *Your Code:* Transition to `DOUBLE_DEPLOYMENT` to start watching altitude for the main chute.
11. **DOUBLE_DEPLOYMENT**
    *   *What happens:* Falling fast under drogue.
    *   *Your Code:* Watch `ARK::Altitude()`. When it gets low (e.g. 300m), call `ARK::DeployMain()`.
12. **MAIN_DEPLOYMENT**
    *   *What happens:* Main chute is out.
    *   *Your Code:* Wait for the chute to fully inflate, then switch to `DESCENT`.
13. **DESCENT**
    *   *What happens:* Drifting down slowly.
    *   *Your Code:* Watch altitude. If it stops changing, we have landed. Go to `LANDING_DETECTION`.

### Phase 5: Landing

14. **LANDING_DETECTION**
    *   *What happens:* Verifying we are actually on the ground (to prevent false landings during wind gusts).
    *   *Your Code:* If altitude remains constant for 5 seconds → `ARK::SetState(FlightState::LANDED)`.
15. **LANDED**
    *   *What happens:* Flight over. Save logs, beacon location.
    *   *Your Code:* Turn on recovery beeper.

### Handling Failure

*   **FAILSAFE**
    *   *What happens:* At ANY point, if a critical error occurs (e.g. battery dies, sensor fails), ARK can jump here.
    *   *Your Code:* Deploy all chutes immediately. safely save data.
