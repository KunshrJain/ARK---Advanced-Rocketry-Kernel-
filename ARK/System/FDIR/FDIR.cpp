#include "FDIR.hpp"

namespace ARK {
    uint32_t FDIR::currentFaults = 0;
    
    // Define which faults are considered system-critical
    const uint32_t CRITICAL_FAULTS_MASK = Fault::BATT_LOW | Fault::IMU_DETACHED | Fault::KERNEL_OVERRUN;

    void FDIR::CheckHealth() {
        // Filhal sab changa si
        // Sensor check logic yahan aayega jab sensors final honge
        if (currentFaults == 0) {
            // System sahi chal raha hai
        }
    }

    void FDIR::RaiseFault(Fault f) {
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
