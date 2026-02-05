#include "FDIR.hpp"
#include "../../../Config.hpp"
#include "../../System/Power/Power.hpp"
#include "../../HAL/Console/Console.hpp"

namespace ARK {
    uint32_t FDIR::currentFaults = 0;
    
    // Define which faults are considered system-critical
    const uint32_t CRITICAL_FAULTS_MASK = Fault::BATT_LOW | Fault::IMU_DETACHED | Fault::KERNEL_OVERRUN;

    void FDIR::CheckHealth() {
        
        #if IS_BATTERY
            float voltage = SystemPower.GetVoltage();
            if (voltage < 3.5) { // Assuming 1S Lipo/Li-Ion threshold
                RaiseFault(Fault::BATT_LOW);
                SystemConsole.Error("[FDIR] Battery Critical: " + std::to_string(voltage) + "V");
            } else {
                ClearFault(Fault::BATT_LOW);
            }
        #endif

        #if IS_IMU
            // Placeholder: Check if IMU is communicating
            // bool imuOk = SystemIMU.TestConnection();
            // if (!imuOk) RaiseFault(Fault::IMU_DETACHED);
        #endif

        if (currentFaults == 0) {
            // System is healthy
        }
    }

    void FDIR::RaiseFault(Fault f) {
        if ((currentFaults & f) == 0) { // Only print on new fault
             SystemConsole.Error("[FDIR] Fault Raised: " + std::to_string(f));
        }
        currentFaults |= f;
    }

    void FDIR::ClearFault(Fault f) {
        currentFaults &= ~f;
    }

    uint32_t FDIR::GetCurrentMask() {
        return currentFaults;
    }

    bool FDIR::IsSystemCritical() {
        return (currentFaults & CRITICAL_FAULTS_MASK) != 0;
    }
}
