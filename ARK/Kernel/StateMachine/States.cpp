#include "States.hpp"
#include "../../../Config.hpp"

StatesManager FlightManager;

StatesManager::StatesManager() : currentState(FlightState::BOOT) {}

void StatesManager::SetState(FlightState newState) {
    currentState = newState;
}

FlightState StatesManager::GetState() const {
    return currentState;
}

void StatesManager::HandleBoot() {
#if USE_STATE_BOOT
    
#endif
}

void StatesManager::HandleInitializing() {
#if USE_STATE_INITIALIZING
#endif
}

void StatesManager::HandleCalibration() {
#if USE_STATE_CALIBRATION
#endif
}

void StatesManager::HandleIdle() {
#if USE_STATE_IDLE
#endif
}

void StatesManager::HandlePreArm() {
#if USE_STATE_PRE_ARM
#endif
}

void StatesManager::HandleArmed() {
#if USE_STATE_ARMED
#endif
}

void StatesManager::HandleLaunch() {
#if USE_STATE_LAUNCH
#endif
}

void StatesManager::HandleAscent() {
#if USE_STATE_ASCENT
#endif
}

void StatesManager::HandleBurnout() {
#if USE_STATE_BURNOUT
#endif
}

void StatesManager::HandleSeparation() {
#if USE_STATE_SEPARATION
#endif
}

void StatesManager::HandleCruising() {
#if USE_STATE_CRUISING
#endif
}

void StatesManager::HandleCoasting() {
#if USE_STATE_COASTING
#endif
}

void StatesManager::HandleApogee() {
#if USE_STATE_APOGEE
#endif
}

void StatesManager::HandleDrogue() {
#if USE_STATE_DROGUE
#endif
}

void StatesManager::HandleDoubleDeployment() {
#if USE_STATE_DOUBLE_DEPLOYMENT
#endif
}

void StatesManager::HandleMainDeployment() {
#if USE_STATE_MAIN_DEPLOYMENT
#endif
}

void StatesManager::HandleDescent() {
#if USE_STATE_DESCENT
#endif
}

void StatesManager::HandleLandingDetection() {
#if USE_STATE_LANDING_DETECTION
#endif
}

void StatesManager::HandleLanded() {
#if USE_STATE_LANDED
#endif
}

void StatesManager::HandleFailsafe() {
#if USE_STATE_FAILSAFE
#endif
}