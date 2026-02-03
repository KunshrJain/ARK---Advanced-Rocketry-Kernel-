#ifndef STATES_HPP
#define STATES_HPP

enum class FlightState {
    BOOT = 0,
    INITIALIZING = 1,
    CALIBRATION = 2,
    IDLE = 3,
    PRE_ARM = 4,
    ARMED = 5,
    LAUNCH = 6,
    ASCENT = 7,
    BURNOUT = 8,
    SEPARATION = 9,
    CRUISING = 10,
    COASTING = 11,
    APOGEE = 12,
    DROGUE = 13,
    DOUBLE_DEPLOYMENT = 14,
    MAIN_DEPLOYMENT = 15,
    DESCENT = 16,
    LANDING_DETECTION = 17,
    LANDED = 18,
    FAILSAFE = 19
};

class StatesManager {
public:
    StatesManager();
    virtual ~StatesManager() = default;

    virtual void HandleBoot(); 
    virtual void HandleInitializing(); 
    virtual void HandleCalibration(); 
    virtual void HandleIdle(); 
    virtual void HandlePreArm(); 
    virtual void HandleArmed();
    virtual void HandleLaunch(); 
    virtual void HandleAscent(); 
    virtual void HandleBurnout(); 
    virtual void HandleSeparation(); 
    virtual void HandleCruising(); 
    virtual void HandleCoasting(); 
    virtual void HandleApogee(); 
    virtual void HandleDrogue();
    virtual void HandleDoubleDeployment(); 
    virtual void HandleMainDeployment(); 
    virtual void HandleDescent(); 
    virtual void HandleLandingDetection(); 
    virtual void HandleLanded(); 
    virtual void HandleFailsafe(); 
    
    void SetState(FlightState newState);
    FlightState GetState() const;

protected:
    FlightState currentState;
};

#endif