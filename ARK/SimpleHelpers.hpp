#pragma once

#include "ARK/CoreTypes.hpp"
#include "ARK/Kernel/StateMachine/States.hpp"
#include "ARK/HAL/Time/Time.hpp"

// Global references need to be available here, they are typically defined in system initialization
namespace ARK {
    extern FlightData g_flightData;
}
extern StatesManager FlightManager;

namespace ARK {

    // --- SENSORS & STATE ACCESSORS ---

    /**
     * @brief Get the current altitude in meters relative to ground (AGL).
     * @return float Altitude (m)
     */
    inline float Altitude() {
        return g_flightData.altitudeM;
    }

    /**
     * @brief Get the current acceleration in m/s^2.
     * @return float Acceleration (m/s^2)
     */
    inline float Acceleration() {
        return g_flightData.accelMps2;
    }

    /**
     * @brief Get the current vertical velocity in m/s.
     * @return float Velocity (m/s)
     */
    inline float Velocity() {
        return g_flightData.velocityMps;
    }

    /**
     * @brief Get the current system time in microseconds since boot.
     * @return uint64_t Time (us)
     */
    inline uint64_t Time() {
        return ARK::g_flightData.timeUs;
    }

    // --- STATE MANAGEMENT ---

    /**
     * @brief Set the flight state.
     * @param s The new state to switch to.
     */
    inline void SetState(FlightState s) {
        FlightManager.SetState(s);
    }

    /**
     * @brief Check if we are currently in a specific state.
     */
    inline bool IsState(FlightState s) {
        return FlightManager.GetState() == s;
    }

    // --- CONVENIENCE ACTIONS ---

    /**
     * @brief Trigger Launch state.
     */
    inline void Launch() {
        SetState(FlightState::LAUNCH);
    }

    /**
     * @brief Trigger Burnout state.
     */
    inline void Burnout() {
        SetState(FlightState::BURNOUT);
    }

    /**
     * @brief Trigger Apogee state.
     */
    inline void Apogee() {
        SetState(FlightState::APOGEE);
    }

    /**
     * @brief Deploy Drogue Parachute.
     */
    inline void DeployDrogue() {
        SetState(FlightState::DROGUE);
    }

    /**
     * @brief Deploy Main Parachute.
     */
    inline void DeployMain() {
        SetState(FlightState::MAIN_DEPLOYMENT);
    }
}
