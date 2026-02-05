#pragma once
#include <cstdint>

namespace ARK {
    enum Fault : uint32_t {
        NONE            = 0,
        I2C_BUS_LOST    = 1 << 0,
        SPI_BUS_LOST    = 1 << 1,
        KERNEL_OVERRUN  = 1 << 2,
        BATT_LOW        = 1 << 3,
        BARO_ANOMALY    = 1 << 4,
        IMU_DETACHED    = 1 << 5,
        PYRO_CONTINUITY = 1 << 6,
        RADIO_LOST      = 1 << 7
    };

    struct ShadowRegistry {
        uint32_t magic;         // 0xDEADBEEF check
        uint32_t flightState;   // Last recorded State index
        uint32_t activeFaults;  // FDIR Bitmask
        float lastAltitude;     // Last recorded Altitude
        uint32_t bootCount;
    };

    struct FlightData {
        uint64_t timeUs;
        uint64_t launchTimeUs;
        float altitudeM;
        float accelMps2;
        float velocityMps;
        bool updated;
    };

    extern FlightData g_flightData;
}
