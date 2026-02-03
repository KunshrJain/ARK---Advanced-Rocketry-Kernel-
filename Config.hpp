
/* System Configuration */

#define IS_BATTERY false;
#define IS_FILTERS false;
#define MCU_FREQUENCY_MHZ 200         
#define SYSTEM_FREQUENCY_HZ 400

/**/

/* Kernel Configuration */
        
#define MODULES_KERNEL_FREQUENCY 200   
#define SYSTEM_KERNEL_FREQUENCY 300    
#define USER_KERNEL_FREQUENCY 200      
#define KERNEL_GUARD_US 500

#define USE_STATE_BOOT true
#define USE_STATE_INITIALIZING true
#define USE_STATE_CALIBRATION true
#define USE_STATE_IDLE true
#define USE_STATE_PRE_ARM true
#define USE_STATE_ARMED true
#define USE_STATE_LAUNCH true
#define USE_STATE_ASCENT true
#define USE_STATE_BURNOUT true
#define USE_STATE_SEPARATION true
#define USE_STATE_CRUISING true
#define USE_STATE_COASTING true
#define USE_STATE_APOGEE true
#define USE_STATE_DROGUE true
#define USE_STATE_DOUBLE_DEPLOYMENT true
#define USE_STATE_MAIN_DEPLOYMENT true
#define USE_STATE_DESCENT true
#define USE_STATE_LANDING_DETECTION true
#define USE_STATE_LANDED true
#define USE_STATE_FAILSAFE true

/**/

/* Modules Configuration */

#define IS_ACTUATORS false
#define IS_ALTIMETER false
#define IS_ANALOG false
#define IS_AUDIO false
#define IS_COMMUNICATION false
#define IS_GYROSCOPE false
#define IS_IMU false
#define IS_LIGHT false
#define IS_PAYLOAD false
#define IS_POSITIONING false
#define IS_RECOVERY_EJECTION false
#define IS_STORAGE false

/**/

/* User Configuration */



/**/

/* Simulation Configuration */



/**/

/* Simulation Configuration */

#define SIMULATION_MODE_ACTIVE false
#define SIL_MODE_ACTIVE false
#define HIL_MODE_ACTIVE false

/**/
