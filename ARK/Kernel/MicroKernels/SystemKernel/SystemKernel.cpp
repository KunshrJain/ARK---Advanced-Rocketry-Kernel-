#include "SystemKernel.hpp"
#include "ARK/System/FDIR/FDIR.hpp"
#include "ARK/HAL/Flash/Flash.hpp"
#include "ARK/HAL/Console/Console.hpp"
#include "ARK/HAL/Time/Time.hpp"
#include "ARK/Kernel/StateMachine/States.hpp"
#include "ARK/CoreTypes.hpp"
#include "ARK/UserAPI/UserTransitions.hpp"

extern StatesManager FlightManager;

namespace ARK {
    extern ShadowRegistry shadow;
    FlightData g_flightData = {};
}

namespace ARK {

    void SystemKernel::Initialize() {
        // Initialization logic is now primarily in SuperiorLoop::Start()
        SystemConsole.Print("[SYSTEM] System Kernel Initialized.");
    }

    void SystemKernel::Sync() {
        FDIR::CheckHealth();
        shadow.flightState = static_cast<uint32_t>(FlightManager.GetState());
        shadow.activeFaults = FDIR::GetCurrentMask();
        
        if (FDIR::IsSystemCritical()) {
            FlightManager.SetState(FlightState::FAILSAFE);
        }

        shadow.lastAltitude = g_flightData.altitudeM;
        g_flightData.timeUs = SystemTime.GetMicros();
        UserEvaluateTransitions(FlightManager);

        FlightState current = FlightManager.GetState();
        switch (current) {
            case FlightState::BOOT: 
                FlightManager.HandleBoot(); 
                    break;
            case FlightState::INITIALIZING: FlightManager.HandleInitializing(); break;
            case FlightState::CALIBRATION: FlightManager.HandleCalibration(); break;
            case FlightState::IDLE: FlightManager.HandleIdle(); break;
            case FlightState::PRE_ARM: FlightManager.HandlePreArm(); break;
            case FlightState::ARMED: FlightManager.HandleArmed(); break;
            case FlightState::LAUNCH: FlightManager.HandleLaunch(); break;
            case FlightState::ASCENT: FlightManager.HandleAscent(); break;
            case FlightState::BURNOUT: FlightManager.HandleBurnout(); break;
            case FlightState::SEPARATION: FlightManager.HandleSeparation(); break;
            case FlightState::CRUISING: FlightManager.HandleCruising(); break;
            case FlightState::COASTING: FlightManager.HandleCoasting(); break;
            case FlightState::APOGEE: FlightManager.HandleApogee(); break;
            case FlightState::DROGUE: FlightManager.HandleDrogue(); break;
            case FlightState::DOUBLE_DEPLOYMENT: FlightManager.HandleDoubleDeployment(); break;
            case FlightState::MAIN_DEPLOYMENT: FlightManager.HandleMainDeployment(); break;
            case FlightState::DESCENT: FlightManager.HandleDescent(); break;
            case FlightState::LANDING_DETECTION: FlightManager.HandleLandingDetection(); break;
            case FlightState::LANDED: FlightManager.HandleLanded(); break;
            case FlightState::FAILSAFE: FlightManager.HandleFailsafe(); break;
            default: break;
        }
    }
}