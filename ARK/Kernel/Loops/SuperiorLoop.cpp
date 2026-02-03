#include "SuperiorLoop.hpp"
#include "../../HAL/Console/Console.hpp"
#include "../../HAL/Clock/Clock.hpp"
#include "../../HAL/Flash/Flash.hpp"
#include "../../HAL/Time/Time.hpp"
#include "../../../Config.hpp"
#include "../../CoreTypes.hpp"
#include "../MicroKernels/ModulesKernel/ModulesKernel.hpp"
#include "../MicroKernels/SystemKernel/SystemKernel.hpp"
#include "../MicroKernels/UserKernel/UserKernel.hpp"
#include "../../System/FDIR/FDIR.hpp"
#include "../StateMachine/States.hpp"

extern StatesManager FlightManager;

namespace ARK {
    // GLOBAL SHADOW DEFINITION (Visible to all Kernels via extern)
    ShadowRegistry shadow;

    void SuperiorLoop::Start() {
        SystemClock.ApplyMcuFrequency(); 
        SystemConsole.Initialize();
        SystemFlash.Initialize();

        shadow = SystemFlash.RecoverShadow();
        
        if (shadow.magic == 0xDEADBEEF) {
            SystemConsole.Print("[SHADOW] Resurrection Active. Last Alt: %.2f", shadow.lastAltitude);
            shadow.bootCount++;
            FDIR::RaiseFault(Fault::KERNEL_OVERRUN); 
            FlightManager.SetState(static_cast<FlightState>(shadow.flightState));
        } else {
            SystemConsole.Print("[SHADOW] Fresh Start.");
            shadow.magic = 0xDEADBEEF;
            shadow.flightState = static_cast<uint32_t>(FlightState::BOOT);
            shadow.lastAltitude = 0.0f;
            shadow.bootCount = 1;
        }

        ARK::SystemKernel::Initialize(); 
        ARK::ModulesKernel::Initialize();
        ARK::UserKernel::Initialize();
        
        Run();
    }

    void SuperiorLoop::Run() {
        const uint64_t kernelGuardUs = KERNEL_GUARD_US; 
        const uint64_t tickPeriod = SystemClock.GetTickPeriodUs();
        static uint64_t lastM = 0, lastS = 0, lastU = 0;

        while (true) {
            uint64_t frame_start = SystemTime.GetMicros();

            if (SystemTime.GetMicros() - lastM >= (1000000 / MODULES_KERNEL_FREQUENCY)) {
                uint64_t start = SystemTime.GetMicros();
                ARK::ModulesKernel::Update();
                if (SystemTime.GetMicros() - start > kernelGuardUs) FDIR::RaiseFault(Fault::KERNEL_OVERRUN);
                lastM = SystemTime.GetMicros();
            }

            if (SystemTime.GetMicros() - lastS >= (1000000 / SYSTEM_KERNEL_FREQUENCY)) {
                uint64_t start = SystemTime.GetMicros();
                ARK::SystemKernel::Sync();
                if (SystemTime.GetMicros() - start > kernelGuardUs) FDIR::RaiseFault(Fault::KERNEL_OVERRUN);
                lastS = SystemTime.GetMicros();
            }

            if (SystemTime.GetMicros() - lastU >= (1000000 / USER_KERNEL_FREQUENCY)) {
                uint64_t start = SystemTime.GetMicros();
                ARK::UserKernel::Execute(); // This calls contd() inside UserCode
                if (SystemTime.GetMicros() - start > kernelGuardUs) FDIR::RaiseFault(Fault::KERNEL_OVERRUN);
                lastU = SystemTime.GetMicros();
            }

            // MIRRORING TO FLASH: Only if state changes
            static uint32_t lastSavedState = 999;
            if (shadow.flightState != lastSavedState) {
                SystemFlash.CommitShadow(shadow);
                lastSavedState = shadow.flightState;
            }

            SystemTime.DelayUntil(frame_start + tickPeriod);
        }
    }
}