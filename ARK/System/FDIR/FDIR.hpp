#pragma once
#include "ARK/CoreTypes.hpp"

namespace ARK {
    class FDIR {
    public:
        static void CheckHealth();
        static void RaiseFault(Fault f);
        static void ClearFault(Fault f);
        static uint32_t GetCurrentMask();
        static bool IsSystemCritical(); // Returns true if rocket should go to FAILSAFE
    private:
        static uint32_t currentFaults;
    };
}