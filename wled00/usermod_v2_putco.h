//#define BUILD_FOR_WOKWI

/*
TODO:

1) "rising edge/falling edge"
2) "rising edge/falling edge/timer"
3) "rising edge/timer"
*/

#pragma once

#if !defined(BUILD_FOR_WOKWI)

#include "wled.h"

#else

#include <stdint.h>
#include <stdbool.h>

extern byte buttonPin[WLED_MAX_BUTTONS];

#define DEBUG_PRINT(s) Serial.print(s)
#define DEBUG_PRINTLN(s) Serial.println(s)

void handlePowerup(void);
void handleStartup(void);
void handleRunning(void);
void handleReversing(void);
void handleConfig(void);
void handleWorkblade(void);

void handlePresetQueue(void);
void addPresetToQueue(int preset);
int getPresetFromQueue(void);

void initButtons(void);
void pollButtons(void);
int getLastPolledButtonStatus(uint8_t btn);
int getLastPolledTwoButtonStatus(uint8_t btn1, uint8_t btn2);

// TODO: Add the rest
void turnBrakesOn(int);
void turnRunningLightsOn(void);

bool presetIsContinuous(int preset);
bool presetIsSolid(int preset);

#endif // BUILD_FOR_WOKWI

/*
 * Usermods allow you to add own functionality to WLED more easily
 * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
 *
 * Using a usermod:
 * 1. Copy the usermod into the sketch folder (same folder as wled00.ino)
 * 2. Register the usermod by adding #include "usermod_filename.h" in the top and registerUsermod(new MyUsermodClass()) in the bottom of usermods_list.cpp
 */

/*--------------------------------------------------------------------------*/
// Putco DEFAULT defines.
/*--------------------------------------------------------------------------*/

// Define the presets to use, and the range of presets for each mode:
// i.e., "Brake presets are from 10 to 19", or "10 to 10" if there is only one.
#define DEFAULT_PRESET_ALL_OFF              9

#define DEFAULT_PRESET_BRAKE_FIRST          10
#define DEFAULT_PRESET_BRAKE_LAST           11
#define DEFAULT_PRESET_BRAKE_LEFT           12
#define DEFAULT_PRESET_BRAKE_RIGHT          13
#define DEFAULT_PRESET_BRAKE_PULSE          11

#define DEFAULT_PRESET_BRAKES_OFF           1

#define DEFAULT_PRESET_REVERSE_FIRST        20
#define DEFAULT_PRESET_REVERSE_LAST         20
#define DEFAULT_PRESET_REVERSE_OFF          2

#define DEFAULT_PRESET_RUNNING_FIRST        30
#define DEFAULT_PRESET_RUNNING_LAST         30
#define DEFAULT_PRESET_RUNNING_OFF          3

#define DEFAULT_PRESET_STARTUP_FIRST        40
#define DEFAULT_PRESET_STARTUP_LAST         44

#define DEFAULT_PRESET_TURN_LEFT_FIRST      50
#define DEFAULT_PRESET_TURN_LEFT_LAST       53
#define DEFAULT_PRESET_TURN_LEFT_OFF        4

#define DEFAULT_PRESET_TURN_RIGHT_FIRST     60
#define DEFAULT_PRESET_TURN_RIGHT_LAST      63
#define DEFAULT_PRESET_TURN_RIGHT_OFF       5

#define DEFAULT_PRESET_TURN_BOTH_OFF        7

#define DEFAULT_PRESET_HAZARD_FIRST         70
#define DEFAULT_PRESET_HAZARD_LAST          70
#define DEFAULT_PRESET_HAZARD_OFF           6

#define DEFAULT_PRESET_WORKBLADE_FIRST      0 // Not enabled by default.
#define DEFAULT_PRESET_WORKBLADE_LAST       0 // Not enabled by default.
#define DEFAULT_PRESET_WORKBLADE_OFF        0 // Not enabled by default.

// Speial, since ther is only one of these...
#define DEFAULT_PRESET_WORKBLADE_STARTUP    0 // Not enabled by default.

// PRESETS: Default presets (if config has not been created).
#define DEFAULT_BRAKE_PRESET                DEFAULT_PRESET_BRAKE_FIRST
#define DEFAULT_REVERSE_PRESET              DEFAULT_PRESET_REVERSE_FIRST
#define DEFAULT_RUNNING_PRESET              DEFAULT_PRESET_RUNNING_FIRST
#define DEFAULT_STARTUP_PRESET              DEFAULT_PRESET_STARTUP_FIRST
#define DEFAULT_TURN_LEFT_PRESET            DEFAULT_PRESET_TURN_LEFT_FIRST
#define DEFAULT_TURN_RIGHT_PRESET           DEFAULT_PRESET_TURN_RIGHT_FIRST
#define DEFAULT_HAZARD_PRESET               DEFAULT_PRESET_HAZARD_FIRST
#define DEFAULT_WORKBLADE_PRESET            DEFAULT_PRESET_WORKBLADE_FIRST

// TIMING: Default timing values.
#if defined(BUILD_FOR_WOKWI)
#define DEFAULT_POWERUP_DELAY_MS            1000
#define DEFAULT_STARTUP_TIME_MS             1000
#else
#define DEFAULT_POWERUP_DELAY_MS            5000
#define DEFAULT_STARTUP_TIME_MS             4000 // 4000 ms = 4 seconds
#endif
#define DEFAULT_CONFIG_TIME_MS              5000  // 5 seconds w/o input to choose
#define DEFAULT_TURNING_TIME_MS             750
#define DEFAULT_ANIMATION_TIME_MS           380
#define DEFAULT_HAZARD_TIME_MS              750
#define DEFAULT_BRAKE_PULSE_TIME_MS         250

// Button timing
#define DEFAULT_DEBOUNCE_TIME_MS            50  // only consider button input of at least 50ms as valid (debouncing)
#define DEFAULT_LONG_PRESS_TIME_MS          600 // long press if button is released after held for at least 600ms

// INPUTS: Mapped to the Button 0-X of WLED.
#define DEFAULT_BUTTON_RUNNING              0
#define DEFAULT_BUTTON_REVERSE              1
#define DEFAULT_BUTTON_TURN_LEFT            2
#define DEFAULT_BUTTON_TURN_RIGHT           3
#define DEFAULT_BUTTON_BRAKE                4
#define DEFAULT_BUTTON_TAP_WIRE             5

// Preset queue timing
#define DEFAULT_PRESET_QUEUE_TIME_MS        50 // may need to be longer.
#define DEFAULT_PRESET_QUEUE_SIZE           10

#define MAX_CONTINUOUS_PRESETS              5
#define MAX_SOLID_PRESETS                   5


/*--------------------------------------------------------------------------*/
// Stuff you probably shouldn't change...
/*--------------------------------------------------------------------------*/
// Useful editor: https://jsonparser.org
//
// NEVER reformat cfg.json / presets.json and re-upload. If you have to
// hand-edit, use something like that website to prettify the json text,
// make changes, then use the same website to compact it back down with
// no spaces. Any reformatting can/will cause Presets to corrupt.

/*--------------------------------------------------------------------------*/
// CONFIGURATION: Names of things inside cfg.json
/*--------------------------------------------------------------------------*/

// Name of this config section:
#define CONFIG_SECTION_NAME                 "putco"

// Name of each entry in this config section:
// Presets
#define CFG_JSON_BRAKE                      "brakePreset"
#define CFG_JSON_REVERSE                    "reversePreset"
#define CFG_JSON_RUNNING                    "runningPreset"
#define CFG_JSON_STARTUP                    "startupPreset"
#define CFG_JSON_TURN_LEFT                  "turnLeftPreset"
#define CFG_JSON_TURN_RIGHT                 "turnRightPreset"
#define CFG_JSON_HAZARD                     "hazardPreset"
#define CFG_JSON_WORKBLADE                  "workbladePreset"

// Buttons
#define CFG_JSON_BUTTON_RUNNING             "buttonRunning"
#define CFG_JSON_BUTTON_REVERSE             "buttonReverse"
#define CFG_JSON_BUTTON_TURN_LEFT           "buttonTurnLeft"
#define CFG_JSON_BUTTON_TURN_RIGHT          "buttonTurnRight"
#define CFG_JSON_BUTTON_BRAKE               "buttonBrake"
#define CFG_JSON_BUTTON_TAP_WIRE            "buttonTapWire"

// Presets
#define CFG_JSON_PRESET_ALL_OFF             "presetAllOff"

#define CFG_JSON_PRESET_BRAKE_FIRST         "presetBrakeFirst"
#define CFG_JSON_PRESET_BRAKE_LAST          "presetBrakeLast"
#define CFG_JSON_PRESET_BRAKE_LEFT          "presetBrakeLeft"
#define CFG_JSON_PRESET_BRAKE_RIGHT         "presetBrakeRight"
#define CFG_JSON_PRESET_BRAKES_OFF          "presetBrakesOff"
#define CFG_JSON_PRESET_BRAKE_PULSE         "presetBrakePulse"

#define CFG_JSON_PRESET_REVERSE_FIRST       "presetReverseFirst"
#define CFG_JSON_PRESET_REVERSE_LAST        "presetReverseLast"
#define CFG_JSON_PRESET_REVERSE_OFF         "presetReverseOff"

#define CFG_JSON_PRESET_RUNNING_FIRST       "presetRunningFirst"
#define CFG_JSON_PRESET_RUNNING_LAST        "presetRunningLast"
#define CFG_JSON_PRESET_RUNNING_OFF         "presetRunningOff"

#define CFG_JSON_PRESET_STARTUP_FIRST       "presetStartupFirst"
#define CFG_JSON_PRESET_STARTUP_LAST        "presetStartupLast"

#define CFG_JSON_PRESET_TURN_LEFT_FIRST     "presetTurnLeftFirst"
#define CFG_JSON_PRESET_TURN_LEFT_LAST      "presetTurnLeftLast"
#define CFG_JSON_PRESET_TURN_LEFT_OFF       "presetTurnLeftOff"

#define CFG_JSON_PRESET_TURN_RIGHT_FIRST    "presetTurnRightFirst"
#define CFG_JSON_PRESET_TURN_RIGHT_LAST     "presetTurnRightLast"
#define CFG_JSON_PRESET_TURN_RIGHT_OFF      "presetTurnRightOff"

#define CFG_JSON_PRESET_TURN_BOTH_OFF       "presetTurnBothOff"

#define CFG_JSON_PRESET_HAZARD_FIRST        "presetHazardFirst"
#define CFG_JSON_PRESET_HAZARD_LAST         "presetHazardLast"
#define CFG_JSON_PRESET_HAZARD_OFF          "presetHazardOff"

#define CFG_JSON_PRESET_WORKBLADE_STARTUP   "presetWorkbladeStartup"
#define CFG_JSON_PRESET_WORKBLADE_FIRST     "presetWorkbladeFirst"
#define CFG_JSON_PRESET_WORKBLADE_LAST      "presetWorkbladeLast"
#define CFG_JSON_PRESET_WORKBLADE_OFF       "presetWorkbladeOff"

// Timing (how long to wait for something to happen).
#define CFG_JSON_POWERUP_DELAY_MS           "powerupDelayMS"
#define CFG_JSON_STARTUP_TIME_MS            "startupTimeMS"
#define CFG_JSON_CONFIG_TIME_MS             "configTimeMS"
#define CFG_JSON_TURNING_TIME_MS            "turningTimeMS"
#define CFG_JSON_ANIMATION_TIME_MS          "animationTimeMS"
#define CFG_JSON_HAZARD_TIME_MS             "hazardTimeMS"
#define CFG_JSON_BRAKE_PULSE_TIME_MS        "brakePulseTimeMS"

// Button timing
#define CFG_JSON_LONG_PRESS_TIME_MS         "longPressTimeMS"
#define CFG_JSON_DEBOUNCE_TIME_MS           "debounceTimeMS"

// Preset queue timing
#define CFG_JSON_PRESET_QUEUE_TIME_MS       "presetQueueTimeMS"


/*--------------------------------------------------------------------------*/
// STATE MACHINE:
/*--------------------------------------------------------------------------*/

#define STATE_NONE                  -1
#define STATE_POWERUP               0   // Just powered on...
#define STATE_STARTUP               1   // Startup
#define STATE_RUNNING               2   // Brake and Turns
#define STATE_REVERSING             3   // Reverse lights
#define STATE_CONFIG                4   // Configuring section preset
#define STATE_WORKBLADE             5   // Workblade

#define CONFIG_STATE_STARTUP        0   // Cycle through startup presets
#define CONFIG_STATE_TURNS          1   // Cycle through turn presets
#define CONFIG_STATE_BRAKES         2   // Cycle through brake presets
#define CONFIG_STATE_EXIT           3

// STATE_RUNNING - TURNING modes:

#define BLINKERS_OFF                0
#define BLINKERS_LEFT               1
#define BLINKERS_RIGHT              2
#define BLINKERS_HAZARD             3

// STATE_RUNNING - BRAKING modes:

#define BRAKES_OFF                  0
#define BRAKES_4WIRE_ON             1
#define BRAKES_5WIRE_ON             2


/*--------------------------------------------------------------------------*/
// Other stuff for the code to work.
/*--------------------------------------------------------------------------*/

// Button routine:
#define BUTTON_RELEASED         0
#define BUTTON_PRESSED          1
#define BUTTON_SHORT_PRESS      2
#define BUTTON_LONG_PRESS       3

#if !defined(BUILD_FOR_WOKWI)
// class name. Use something descriptive and leave the ": public Usermod" part :)
class PutcoUsermod : public Usermod
{
private:
#endif // WOKWI
    // Private class members. You can declare variables and functions only accessible to your usermod here

    /*----------------------------------------------------------------------*/
    // Variables that will be set based on cfg.json entries.
    /*----------------------------------------------------------------------*/

    // These inistialize with the default values, but the config load
    // routines will override them with whatever setting is specified there.
    // (When it loads a section, if the section is not found it will use
    // a value specified there. See those routines for what really gets
    // used.)

    // Current preset in use
    int brakePreset = DEFAULT_BRAKE_PRESET;
    int reversePreset = DEFAULT_REVERSE_PRESET;
    int runningPreset = DEFAULT_RUNNING_PRESET;
    int startupPreset = DEFAULT_STARTUP_PRESET;
    int turnLeftPreset = DEFAULT_TURN_LEFT_PRESET;
    int turnRightPreset = DEFAULT_TURN_RIGHT_PRESET;
    int hazardPreset = DEFAULT_HAZARD_PRESET;
    int workbladePreset = DEFAULT_WORKBLADE_PRESET;
    // Different, because there is only one of these.
    int workbladeStartupPreset = DEFAULT_PRESET_WORKBLADE_STARTUP;

    // Button mapping
    int buttonRunning = DEFAULT_BUTTON_RUNNING;
    int buttonReverse = DEFAULT_BUTTON_REVERSE;
    int buttonTurnLeft = DEFAULT_BUTTON_TURN_LEFT;
    int buttonTurnRight = DEFAULT_BUTTON_TURN_RIGHT;
    int buttonBrake = DEFAULT_BUTTON_BRAKE;
    int buttonTapWire = DEFAULT_BUTTON_TAP_WIRE;

    // Presets
    int presetAllOff = DEFAULT_PRESET_ALL_OFF;

    int presetBrakeFirst = DEFAULT_PRESET_BRAKE_FIRST;
    int presetBrakeLast = DEFAULT_PRESET_BRAKE_LAST;
    int presetBrakesOff = DEFAULT_PRESET_BRAKES_OFF;
    int presetBrakeLeft = DEFAULT_PRESET_BRAKE_LEFT;
    int presetBrakeRight = DEFAULT_PRESET_BRAKE_RIGHT;
    int presetBrakePulse = DEFAULT_PRESET_BRAKE_PULSE;

    int presetReverseFirst = DEFAULT_PRESET_REVERSE_FIRST;
    int presetReverseLast = DEFAULT_PRESET_REVERSE_LAST;
    int presetReverseOff = DEFAULT_PRESET_REVERSE_OFF;

    int presetRunningFirst = DEFAULT_PRESET_RUNNING_FIRST;
    int presetRunningLast = DEFAULT_PRESET_RUNNING_LAST;
    int presetRunningOff = DEFAULT_PRESET_RUNNING_OFF;

    int presetStartupFirst = DEFAULT_PRESET_STARTUP_FIRST;
    int presetStartupLast = DEFAULT_PRESET_STARTUP_LAST;

    int presetTurnLeftFirst = DEFAULT_PRESET_TURN_LEFT_FIRST;
    int presetTurnLeftLast = DEFAULT_PRESET_TURN_LEFT_LAST;
    int presetTurnLeftOff = DEFAULT_PRESET_TURN_LEFT_OFF;

    int presetTurnRightFirst = DEFAULT_PRESET_TURN_RIGHT_FIRST;
    int presetTurnRightLast = DEFAULT_PRESET_TURN_RIGHT_LAST;
    int presetTurnRightOff = DEFAULT_PRESET_TURN_RIGHT_OFF;
    int presetTurnBothOff = DEFAULT_PRESET_TURN_BOTH_OFF;

    int presetHazardFirst = DEFAULT_PRESET_HAZARD_FIRST;
    int presetHazardLast = DEFAULT_PRESET_HAZARD_LAST;
    int presetHazardOff = DEFAULT_PRESET_HAZARD_OFF;

    int presetWorkbladeStartup = DEFAULT_PRESET_WORKBLADE_STARTUP;
    int presetWorkbladeFirst = DEFAULT_PRESET_WORKBLADE_FIRST;
    int presetWorkbladeLast =  DEFAULT_PRESET_WORKBLADE_LAST;
    int presetWorkbladeOff =   DEFAULT_PRESET_WORKBLADE_OFF;

    // Arrays of presets that are continuous or solid
#if !defined(BUILD_FOR_WOKWI)
    int continuousPresets[MAX_CONTINUOUS_PRESETS]       _INIT({0});
    int solidPresets[MAX_SOLID_PRESETS]                 _INIT({0});
#else
    int continuousPresets[MAX_CONTINUOUS_PRESETS] = { 54,55,64,65,0 };
    int solidPresets[MAX_SOLID_PRESETS] = { 52,53,62,63,0 };
#endif // BUILD_FOR_WOKWI

    // Timers
    // I forget if these need to be signed or unsigned, or if it matters.
    int powerupDelayMS = DEFAULT_POWERUP_DELAY_MS;
    int startupTimeMS = DEFAULT_STARTUP_TIME_MS;
    int configTimeMS = DEFAULT_CONFIG_TIME_MS;
    int turningTimeMS = DEFAULT_TURNING_TIME_MS;
    int animationTimeMS = DEFAULT_ANIMATION_TIME_MS;
    int hazardTimeMS = DEFAULT_HAZARD_TIME_MS;
    int brakePulseTimeMS = DEFAULT_BRAKE_PULSE_TIME_MS;

    // Button times
    int debounceTimeMS = DEFAULT_DEBOUNCE_TIME_MS;
    int longPressTimeMS = DEFAULT_LONG_PRESS_TIME_MS;

    // Preset queue time
    int presetQueueTimeMS = DEFAULT_PRESET_QUEUE_TIME_MS;

    /*----------------------------------------------------------------------*/
    // Program varialbes (not part of the cfg.json stuff).
    /*----------------------------------------------------------------------*/
    // Timers
    unsigned long powerupDelayTimer = 0;
    unsigned long turnOffStartupTimer = 0;
    unsigned long turnOffLeftBlinkerTimer = 0;
    unsigned long turnOffRightBlinkerTimer = 0;
    unsigned long configTimer = 0;
    unsigned long turnOffHazardsTimer = 0;
    unsigned long brakePulseTimer = 0;
    unsigned long turnOnLeftBrakeTimer = 0;
    unsigned long turnOnRightBrakeTimer = 0;
    unsigned long brakePulseAllowedTimer = 0;

    unsigned long shortPressTimer[WLED_MAX_BUTTONS] = { 0, 0, 0, 0, 0, 0 };

    int turnOffTimeMS = 0;

    // State machine
    int state = STATE_POWERUP;
    int prevState = STATE_NONE;

    // Light states
    int blinkerState = BLINKERS_OFF;
    int brakingState = BRAKES_OFF;

    // CONFIG state machine
    int configState = 0;
    int configPreset = 0;
    int configPresetStart = 0;
    int configPresetEnd = 0;

    // These are used to tell if config changes one of the sections.
    int orgStartupPreset = 0;
    int orgTurnLeftPreset = 0;
    int orgBrakePreset = 0;
    int orgWorkbladePreset = 0;
    bool configNeedsToBeSaved = false;

    // Preset queue
    // WLED presets are asynchronous, so you cannot gaurantee they happen
    // when you think they do.
    int presetQueueCount = 0;
    int presetQueueNextIn = 0;
    int presetQueueNextOut = 0;
    unsigned long presetQueueTimer = 0;

#if !defined(BUILD_FOR_WOKWI)
    int presetQueue[DEFAULT_PRESET_QUEUE_SIZE] _INIT({0});
#else
    int presetQueue[DEFAULT_PRESET_QUEUE_SIZE] = { 0,0,0,0,0,0,0,0,0,0 };
#endif

#if !defined(BUILD_FOR_WOKWI)
    // Our own copies of these, separate from button.cpp globals.
    bool buttonPressedBefore[WLED_MAX_BUTTONS]          _INIT({false});
    bool buttonLongPressed[WLED_MAX_BUTTONS]            _INIT({false});
    unsigned long buttonPressedTime[WLED_MAX_BUTTONS]   _INIT({0});
#else
    bool buttonPressedBefore[WLED_MAX_BUTTONS] = { false, false, false, false, false, false };
    bool buttonLongPressed[WLED_MAX_BUTTONS] = { false, false, false, false, false, false };
    unsigned long buttonPressedTime[WLED_MAX_BUTTONS] = { 0, 0, 0, 0, 0, 0, };
#endif // BUILD_FOR_WOKWI
    int buttonStatus[WLED_MAX_BUTTONS];

    // HACK
    int lastTwoButtonStatus = BUTTON_RELEASED;
    bool tapWireReleased = false;
    int leftButtonCounter = 0;
    int rightButtonCounter = 0;

#if !defined(BUILD_FOR_WOKWI)
public:
#endif // BUILD_FOR_WOKWI
    // Functions called by WLED

    /*----------------------------------------------------------------------*/
    /*
     * setup() is called once at boot. WiFi is not yet connected at this point.
     * You can use it to initialize variables, sensors or similar.
     */
#if !defined(BUILD_FOR_WOKWI)
    void setup()
#else
    void usermodsetup(void)
#endif // BUILD_FOR_WOKWI
    {
        // DEBUG_PRINTLN("Hello from my usermod!");
        addPresetToQueue(presetAllOff);
      
        initButtons();

        for (int idx=0; idx<100; idx++)
        {
            pollButtons();

            if (getLastPolledButtonStatus(buttonReverse) != BUTTON_RELEASED)
            {
                DEBUG_PRINTLN("AP_BEHAVIOR_ALWAYS");
#if !defined(BUILD_FOR_WOKWI)
                // Turn on access point:
                apBehavior = AP_BEHAVIOR_ALWAYS;
                WLED::instance().initAP(true);
#endif
                break;
            }
        }

        // Kickstart the queue timer.
        presetQueueTimer = millis();
    }


    /*----------------------------------------------------------------------*/
    /*
     * connected() is called every time the WiFi is (re)connected
     * Use it to initialize network interfaces
     */
    void connected()
    {
        // DEBUG_PRINTLN("Connected to WiFi!");

        // Move on to "in startup" state.
        if (state == STATE_POWERUP)
        {
            state = STATE_STARTUP;
        }

        // TODO: Disable "turn off AP" code that is also TODO
    }


    /*----------------------------------------------------------------------*/
    /*
     * loop() is called continuously. Here you can check for events, read sensors, etc.
     *
     * Tips:
     * 1. You can use "if (WLED_CONNECTED)" to check for a successful network connection.
     *    Additionally, "if (WLED_MQTT_CONNECTED)" is available to check for a connection to an MQTT broker.
     *
     * 2. Try to avoid using the delay() function. NEVER use delays longer than 10 milliseconds.
     *    Instead, use a timer check as shown here.
     */
#if !defined(BUILD_FOR_WOKWI)
    void loop()
#else
    void usermodloop(void)
#endif
    {
        /*------------------------------------------------------------------*/
        // And so it begins...
        /*------------------------------------------------------------------*/

        // applyPreset() for any pending presets.
        handlePresetQueue();

        // Read all buttons and store status.
        pollButtons();

#if 0 //defined(BUILD_FOR_WOKWI)
        showButtonStatus();
#endif // BUILD_FOR_WOKWI

        // State machine
        switch (state)
        {
            /*==================================================================*/
            // Initial state does nothing, currently, but it might be needed
            // to do some initialization or wait for it to be save to start up.
            /*==================================================================*/
            case STATE_POWERUP:
                handlePowerup();
                break; // end of STATE_POWERUP

            /*==================================================================*/
            // Play the Startup sequence for "STARTUP_TIME_MS", ignoring any
            // other buttons during this time.
            /*==================================================================*/
            case STATE_STARTUP:
                handleStartup();
                break; // end of case STATE_STARTUP

            /*==================================================================*/
            // Normal running mode, where all inputs are being checked. This
            // mode detects turn signals, braking, reverse and entering the
            // configuration state. Reverse and Config will leave this state and
            // go in to a dedicated state that only does that, ignoring stuff
            // here.
            /*==================================================================*/
            case STATE_RUNNING:
                handleRunning();
                break; // end of case STATE_RUNNING

            /*==================================================================*/
            // While reversing, all other buttons are ignored. This state will
            // not return until Reverse has been turned off.
            /*==================================================================*/
            case STATE_REVERSING:
                handleReversing();
                break; // end of case STATE_REVERSING

            /*==================================================================*/
            //
            /*==================================================================*/
            case STATE_CONFIG:
                handleConfig();
                break; // end of case STATE_CONFIG

            /*==================================================================*/
            //
            /*==================================================================*/
            case STATE_WORKBLADE:
                handleWorkblade();
                break; // end of case STATE_WORKBLADE

            // Commented out due to a weird compiler error I can't figure out.
            default:
                // This should never happen.
                break;
        } // end of switch(state)
    }


    /*----------------------------------------------------------------------*/
    // Instead of doing this all manually...
    /*----------------------------------------------------------------------*/
    void turnLeftBlinkerOn()
    {
        blinkerState = BLINKERS_LEFT;
        addPresetToQueue(turnLeftPreset);
        turnOnLeftBrakeTimer = 0; // cancel

        brakePulseAllowedTimer = millis();
    }

    void turnLeftBlinkerOff()
    {
        if (blinkerState == BLINKERS_LEFT)
        {
            blinkerState = BLINKERS_OFF;
        }

        turnOffLeftBlinkerTimer = 0; // shut off
        addPresetToQueue(presetTurnLeftOff);
    
        if (brakingState != BRAKES_OFF)
        {
            // Turn left brake back on in 500ms.
            turnOnLeftBrakeTimer = millis();
        }
    }

    void turnRightBlinkerOn()
    {
        blinkerState = BLINKERS_RIGHT;
        addPresetToQueue(turnRightPreset);
        turnOnRightBrakeTimer = 0; // cancel
    
        brakePulseAllowedTimer = millis();
    }

    void turnRightBlinkerOff()
    {
        if (blinkerState == BLINKERS_RIGHT)
        {
            blinkerState = BLINKERS_OFF;
        }

        turnOffRightBlinkerTimer = 0; // turn off
        addPresetToQueue(presetTurnRightOff);

        if (brakingState != BRAKES_OFF)
        {
            // Turn bright rake back on in 500ms.
            turnOnRightBrakeTimer = millis();
        }
    }

    void turnLeftAndRightBlinkersOff()
    {
        blinkerState = BLINKERS_OFF;
        turnOffLeftBlinkerTimer = 0;
        turnOffRightBlinkerTimer = 0;
        addPresetToQueue(presetTurnBothOff);
    }

    void turnHazardsOn()
    {
        blinkerState = BLINKERS_HAZARD;
        addPresetToQueue(hazardPreset);

        brakePulseTimer = 0; // cancel
        turnOnLeftBrakeTimer = 0; // cancel
        turnOnRightBrakeTimer = 0; // cancel
    }

    void turnHazardsOff()
    {
        blinkerState = BLINKERS_OFF;
        turnOffHazardsTimer = 0; // turn off

        // Turn brakes back on if they are on.
        if (brakingState != BRAKES_OFF)
        {
            turnBrakesOn(brakingState);
        }
        else
        {
            addPresetToQueue(presetHazardOff);
        }
    }

    void turnBrakesOn(int state)
    {
        // Ignore if we are in hazard mode.
        //if (blinkerState == BLINKERS_OFF)
        {
#if defined(BUILD_FOR_WOKWI)
            if (state == BRAKES_4WIRE_ON)
            {
                DEBUG_PRINT("4-Wire: ");
            }
            else if (state == BRAKES_5WIRE_ON)
            {
                DEBUG_PRINT("5-Wire: ");
            }
#endif // WOKWI

            if (blinkerState == BLINKERS_OFF)
            {
                if ((brakePreset == presetBrakePulse) && (brakePulseAllowedTimer == 0))
                {
                    // Start timer to know when to transition to normal brakes.
                    brakePulseTimer = millis();
                    addPresetToQueue(brakePreset);
                }
                else
                {
                    // TODO: fix this logic a bit.
                    addPresetToQueue(presetBrakeFirst);
                }
            }
            else if (blinkerState == BLINKERS_LEFT)
            {
                addPresetToQueue(presetBrakeRight);
            }
            else if (blinkerState == BLINKERS_RIGHT)
            {
                addPresetToQueue(presetBrakeLeft);
            }
            else
            {
                // Hazards. Do nothing.
            }
        }

        brakingState = state;
    }

    void turnBrakesOff()
    {
        brakingState = BRAKES_OFF;

        // TODO: do we EVER send brakes off?
        if (blinkerState == BLINKERS_LEFT)
        {
            // Turn off right blinker segment.
            addPresetToQueue(presetTurnRightOff);
        }
        else if (blinkerState == BLINKERS_RIGHT)
        {
            // Turn off left blinker segment.
            addPresetToQueue(presetTurnLeftOff);
        }
        else
        {
            // Turn off both blinker segments.
            addPresetToQueue(presetTurnBothOff);
        }

        // TODO: Do we need to do this here?
        turnRunningLightsOn();
    }

    void turnReverseLightsOn()
    {
        // In case they were running...
        turnOffLeftBlinkerTimer = 0;
        turnOffRightBlinkerTimer = 0;
        addPresetToQueue(reversePreset);
    }

    void turnReverseLightsOff()
    {
        addPresetToQueue(presetReverseOff);

        // Turn brakes back on if they are on.
        if (brakingState != BRAKES_OFF)
        {
            turnBrakesOn(brakingState);
        }
    }

    void turnRunningLightsOn()
    {
        // Brakes take priority.
        if (brakingState == BRAKES_OFF)
        {
            addPresetToQueue(runningPreset);
        }
    }
    
    void turnRunningLightsOff()
    {
        // No such thing.
    }

    /*----------------------------------------------------------------------*/
    void handlePowerup()
    {
        // For anything that needs to be done only once when entering this state.
        if (prevState != STATE_POWERUP)
        {
            DEBUG_PRINTLN("STATE_POWERUP");
            prevState = STATE_POWERUP;

            powerupDelayTimer = millis();
        }

        // Stay in this mode until time has elapsed.
        if ((powerupDelayTimer != 0) && (millis() - powerupDelayTimer > powerupDelayMS))
        {
            powerupDelayTimer = 0; // turn off

            // Time elapsed.
            state = STATE_STARTUP;
        }
    } // end of handlePowerup()


    /*----------------------------------------------------------------------*/
    void handleStartup()
    {
        // For anything that needs to be done only once when entering this state.
        if (prevState != STATE_STARTUP)
        {
            DEBUG_PRINTLN("STATE_STARTUP");
            prevState = STATE_STARTUP;

            // Maybe turn off lights to keep everything in sync?
            addPresetToQueue(presetAllOff);

            // Workblade config takes priority.
            if (presetWorkbladeFirst != 0)
            {
                // In case of bad config value...
                if (workbladePreset < presetWorkbladeFirst)
                {
                    workbladePreset = presetWorkbladeFirst;
                }

                if (workbladeStartupPreset != 0)
                {
                    // Play the workblade STARTUP preset.
                    addPresetToQueue(workbladeStartupPreset);
                }
                else
                {
                    // If no startup, go direct to state.
                    state = STATE_WORKBLADE;
                }
            }
            else if (startupPreset != 0)
            {
                // Play the STARTUP preset.
                addPresetToQueue(startupPreset);
            }
            
            // If here, we have a startup playing.

            // Remember the current time.
            turnOffStartupTimer = millis();
        }

        // Stay in this mode until time has elapsed.
        if ((turnOffStartupTimer != 0) && (millis() - turnOffStartupTimer > startupTimeMS))
        {
            turnOffStartupTimer = 0; // turn off

            // Time elapsed.
            // TODO: Do we need a dedicated preset for Startup Off?
            // Let next mode decide if it wants the lights off.
            //addPresetToQueue(presetAllOff);

            // Shut off startup lights.
            if (presetWorkbladeFirst != 0)
            {
                // Move to the "workblade" state.
                state = STATE_WORKBLADE;
            }
            else
            {
                // Move on to the "running" state.
                state = STATE_RUNNING;
            }
        }
    } // end of handleStartup()


    /*----------------------------------------------------------------------*/
    void handleRunning()
    {
        // For anything that needs to be done only once when entering this state.
        if (prevState != STATE_RUNNING)
        {
            DEBUG_PRINTLN("STATE_RUNNING");
            prevState = STATE_RUNNING;

            // Maybe turn off lights to keep everything in sync?
            addPresetToQueue(presetAllOff);

            // Assume running lights were not on if entering this
            // state (either because it's the first time and they
            // have never been turned on, or we went in to another
            // state that turned them off).
            if (brakingState == BRAKES_OFF)
            {
                turnRunningLightsOn();
            }
            else
            {
                turnBrakesOn(brakingState);
            }
        }

        // Turn off things that need to be turned off.

        if ((turnOffHazardsTimer != 0) && (millis() - turnOffHazardsTimer > hazardTimeMS))
        {
            turnOffHazardsTimer = 0;

            turnHazardsOff();
        }

        if ((brakePulseTimer != 0) && (millis() - brakePulseTimer > brakePulseTimeMS))
        {
            brakePulseTimer = 0;

            if (brakingState != BRAKES_OFF)
            {
                if (brakePreset == presetBrakePulse)
                {
                    // HARD CODED: use the first brake pattern.
                    addPresetToQueue(presetBrakeFirst);
                }
                else
                {
                    // Timer should never be set except for brake pulse, but
                    // just in case...
                    //turnBrakesOn(brakingState);
                    addPresetToQueue(brakePreset);
                }
            }
        }

        // Elsewhere, if this value is not 0, don't pulse.
        if ((brakePulseAllowedTimer != 0) && (millis() - brakePulseAllowedTimer > 800)) // TODO:
        {
            brakePulseAllowedTimer = 0;
        }

        if ((turnOnLeftBrakeTimer != 0) && (millis() - turnOnLeftBrakeTimer > 500)) // TODO: hard-coded
        {
            turnOnLeftBrakeTimer = 0;

            if (brakingState != BRAKES_OFF)
            {
                addPresetToQueue(presetBrakeLeft);
            }
        }

        if ((turnOnRightBrakeTimer != 0) && (millis() - turnOnRightBrakeTimer > 500)) // TODO: hard-coded
        {
            turnOnRightBrakeTimer = 0;

            if (brakingState != BRAKES_OFF)
            {
                addPresetToQueue(presetBrakeRight);
            }
        }

        if ((turnOffLeftBlinkerTimer != 0) && (millis() - turnOffLeftBlinkerTimer > turnOffTimeMS))
        {
            turnOffLeftBlinkerTimer = 0; // shut off

            if (blinkerState == BLINKERS_LEFT)
            {
                turnLeftBlinkerOff();
            }
        }

        if ((turnOffRightBlinkerTimer != 0) && (millis() - turnOffRightBlinkerTimer > turnOffTimeMS))
        {
            turnOffRightBlinkerTimer = 0;

            if (blinkerState == BLINKERS_RIGHT)
            {
                turnRightBlinkerOff();
            }
        }

        /*--------------------------------------------------------------*/
        // Button 1 - Reverse
        /*--------------------------------------------------------------*/
        // Honor going in to Reverse no matter what state we are in.
        switch (getLastPolledButtonStatus(buttonReverse))
        {
            case BUTTON_PRESSED:
            case BUTTON_SHORT_PRESS:
            case BUTTON_LONG_PRESS:
                state = STATE_REVERSING;
                // No need to do anything else here.

                // BAD STYLE! Should be only one return in a function!
                return; // Don't do anything else this cycle.
            
            default:
                break;
        }

        /*----------------------------------------------------------*/
        // Buttons (Left+Right) for 4-Wire Brake and Hazard mode.
        /*----------------------------------------------------------*/
        switch (getLastPolledTwoButtonStatus(buttonTurnLeft, buttonTurnRight))
        {
            case BUTTON_RELEASED: // Both off
                // HACK for Walter.
                if (blinkerState == BLINKERS_HAZARD)
                {
                    turnLeftAndRightBlinkersOff();
                    // Turn hazard mode off.
                    turnOffHazardsTimer = 0;
                }
                break;
            
            case BUTTON_LONG_PRESS: // Both saw long press
                if (brakingState == BRAKES_OFF)
                {
                    if (blinkerState != BLINKERS_HAZARD)
                    {
                        DEBUG_PRINT("e");
                        turnBrakesOn(BRAKES_4WIRE_ON);
                    }
                    else
                    {
                        // Flag so they turn on when hazards end.
                        brakingState = BRAKES_4WIRE_ON;
                    }
                }
                break;
            
            // We can't use BUTTON_PRESSED here since it would
            // activate and override a long press for brakes.
            case BUTTON_PRESSED:
            case BUTTON_SHORT_PRESS: // Both saw short press
                if (blinkerState != BLINKERS_HAZARD)
                {
                    DEBUG_PRINT("(");
                    DEBUG_PRINT(getLastPolledTwoButtonStatus(buttonTurnLeft, buttonTurnRight));
                    DEBUG_PRINT(")");

                    DEBUG_PRINT("$");
                    turnHazardsOn();
                }

                if (blinkerState == BLINKERS_HAZARD)
                {
                    turnOffHazardsTimer = millis();
                }
                break;

            default:
                // Nothing do to here.
                break;
        } // end of switch (getLastPolledTwoButtonStatus(buttonTurnLeft, buttonTurnRight))

        // Hazard takes priority, so we won't check turn signals
        // unless hazards are NOT on.
        //if (blinkerState != BLINKERS_HAZARD)
        {
            // Hazards were not on.

            /*----------------------------------------------------------*/
            // Button 2 - Left Turn
            /*----------------------------------------------------------*/
            int leftButtonStatus = getLastPolledButtonStatus(buttonTurnLeft);
            int rightButtonStatus = getLastPolledButtonStatus(buttonTurnRight);

            switch (leftButtonStatus)
            {
                case BUTTON_RELEASED:
                    if ((brakingState == BRAKES_4WIRE_ON) &&
                        (rightButtonStatus == BUTTON_RELEASED))
                    {
                        turnBrakesOff();
                    }
                    // HACK for Walter.
                    if (blinkerState == BLINKERS_LEFT)
                    {
                        if (presetIsSolid(turnLeftPreset) == true)
                        {
                            turnLeftBlinkerOff();
                        }
                    }
                    break;

                case BUTTON_PRESSED: // left pressed
                case BUTTON_SHORT_PRESS: // or left being held down
                    if ((rightButtonStatus == BUTTON_PRESSED) ||
                        (rightButtonStatus == BUTTON_SHORT_PRESS))
                    {
                        if (blinkerState != BLINKERS_HAZARD)
                        {
                            turnHazardsOn();
                        }
                    }
                    else
                    if ((rightButtonStatus == BUTTON_RELEASED) ||
                        (rightButtonStatus == BUTTON_LONG_PRESS))
                    {
                        if (leftButtonCounter++ > 20)
                        {
                            // if (blinkerState == BLINKERS_RIGHT)
                            // {
                            //     turnRightBlinkerOff();
                            // }

                            if (blinkerState == BLINKERS_OFF)
                            {
                                turnLeftBlinkerOn();

                                if (presetIsContinuous(turnLeftPreset) == true)
                                {
                                    turnOffTimeMS = turningTimeMS;
                                }
                                else
                                {
                                    turnOffTimeMS = animationTimeMS;
                                }
                            }

                            if (blinkerState == BLINKERS_LEFT)
                            {
                                // Start timer so we know when to shut it off.
                                turnOffLeftBlinkerTimer = millis();
                            }

                            leftButtonCounter = 0;
                        }
                    }
                    else
                    {
                        leftButtonCounter = 0;  
                    }
                    break;
              
                // In case of braking while turning.
                case BUTTON_LONG_PRESS: // Left saw long press
                    if (brakingState == BRAKES_OFF)
                    {
                        if (blinkerState != BLINKERS_HAZARD)
                        {
                            DEBUG_PRINT("?");
                            turnBrakesOn(BRAKES_4WIRE_ON);
                        }
                        else
                        {
                            // Flag so they turn on when hazards end.
                            DEBUG_PRINT("1");
                            brakingState = BRAKES_4WIRE_ON;
                            turnHazardsOff();
                        }
                    }
                    break;

                default:
                    // Nothing do to here.
                    break;
            }

            /*----------------------------------------------------------*/
            // Button 3 - Right Turn
            /*----------------------------------------------------------*/
            //int btn3Status = getLastPolledButtonStatus(buttonTurnRight);
            switch (rightButtonStatus)
            {
                case BUTTON_RELEASED:
                    if ((brakingState == BRAKES_4WIRE_ON) &&
                        (leftButtonStatus == BUTTON_RELEASED))
                    {
                        turnBrakesOff();
                    }
                    // HACK for Walter.
                    if (blinkerState == BLINKERS_RIGHT)
                    {
                        if (presetIsSolid(turnRightPreset) == true)
                        {
                            turnRightBlinkerOff();
                        }
                    }
                    break;

                case BUTTON_PRESSED: // right pressed
                case BUTTON_SHORT_PRESS: // or right being held down
                    if ((leftButtonStatus == BUTTON_PRESSED) ||
                        (leftButtonStatus == BUTTON_SHORT_PRESS))
                    {
                        if (blinkerState != BLINKERS_HAZARD)
                        {
                            turnHazardsOn();
                        }
                    }
                    else
                    if ((leftButtonStatus == BUTTON_RELEASED) ||
                        (leftButtonStatus == BUTTON_LONG_PRESS))
                    {
                        if (rightButtonCounter++ > 20)
                        {
                            // if (blinkerState == BLINKERS_RIGHT)
                            // {
                            //     turnLeftBlinkerOff();
                            // }

                            if (blinkerState == BLINKERS_OFF)
                            {
                                turnRightBlinkerOn();

                                if (presetIsContinuous(turnRightPreset) == true)
                                {
                                    turnOffTimeMS = turningTimeMS;
                                }
                                else
                                {
                                    turnOffTimeMS = animationTimeMS;
                                }
                            }

                            if (blinkerState == BLINKERS_RIGHT)
                            {
                                // Start timer so we know when to shut it off.
                                turnOffRightBlinkerTimer = millis();
                            }
                            
                            rightButtonCounter = 0;
                        }
                    }
                    else
                    {
                        rightButtonCounter = 0;
                    }
                    break;

                // In case of braking while turning.
                case BUTTON_LONG_PRESS: // Right saw long press
                    if (brakingState == BRAKES_OFF)
                    {
                        if (blinkerState != BLINKERS_HAZARD)
                        {
                            DEBUG_PRINT("f");
                            turnBrakesOn(BRAKES_4WIRE_ON);
                        }
                        else
                        {
                            // Flag so they turn on when hazards end.
                            DEBUG_PRINT("2");
                            brakingState = BRAKES_4WIRE_ON;
                            turnHazardsOff();
                        }
                    }
                    break;

                default:
                    // Nothing do to here.
                    break;
            }
        } // end of (blinkerState != BLINKERS_HAZARD)

        /*----------------------------------------------------------*/
        // Button 5 - Brake (5-Wire)
        /*----------------------------------------------------------*/
        // Use fast read of button
        switch (getLastPolledButtonStatus(buttonBrake))
        {
            case BUTTON_PRESSED:
            case BUTTON_SHORT_PRESS:
            case BUTTON_LONG_PRESS:
                // Above returns true as long as the brake is held down,
                // so only trigger this one time.
                if (brakingState != BRAKES_5WIRE_ON)
                {
                    // TODO: What if 4-Wire is on?
                    turnBrakesOn(BRAKES_5WIRE_ON);
                }
                break;
            
            case BUTTON_RELEASED:
                // 5-Wire brake released
                if (brakingState == BRAKES_5WIRE_ON)
                {
                    turnBrakesOff();
                }
                break;

            default:
                break;
        }

        /*----------------------------------------------------------*/
        // Button 6 - Tap Wire (Config)
        /*----------------------------------------------------------*/
        switch (getLastPolledButtonStatus(buttonTapWire))
        {
            case BUTTON_SHORT_PRESS:
            case BUTTON_LONG_PRESS:
                state = STATE_CONFIG;
                break;
            
            default:
                break;
        }
    } // end of handleRunning()


    /*----------------------------------------------------------------------*/
    void handleReversing()
    {
        // For anything that needs to be done only once when entering this state.
        if (prevState != STATE_REVERSING)
        {
            DEBUG_PRINTLN("STATE_REVERSING");

            //addPresetToQueue(presetAllOff);

            turnReverseLightsOn();

            // Disable brake mode, but if still held down it will be
            // turned back on after leaving this mode.
            brakingState = BRAKES_OFF;

            prevState = STATE_REVERSING;
        }

        // Only leave this state if Reverse is released.
        if (getLastPolledButtonStatus(buttonReverse) == BUTTON_RELEASED) // No Reverse
        {
            state = STATE_RUNNING;
        }    
    } // end of handleReversing()


    /*----------------------------------------------------------------------*/
    void handleConfig()
    {
        int btnStatus = BUTTON_RELEASED;

        // For anything that needs to be done only once when entering this state.
        if (prevState != STATE_CONFIG)
        {
            DEBUG_PRINTLN("STATE_CONFIG");
            prevState = STATE_CONFIG;

            configState = CONFIG_STATE_STARTUP;

            // Save current presets so we know if they changed (for saving out).
            orgStartupPreset = startupPreset;
            orgTurnLeftPreset = turnLeftPreset;
            orgBrakePreset = brakePreset;
            // Add other sections here.

            configPresetStart = presetStartupFirst;
            configPresetEnd = presetStartupLast;
            configPreset = startupPreset; // current startup preset

            // Turn off lights to enter this mode.
            addPresetToQueue(presetAllOff);

            // Shut off any timers.
            turnOffLeftBlinkerTimer = 0;
            turnOffRightBlinkerTimer = 0;

            // Show the new preset and continue.
            addPresetToQueue(configPreset);
            configTimer = millis();
        }

        btnStatus = getLastPolledButtonStatus(buttonTapWire);
        if ((btnStatus == BUTTON_SHORT_PRESS) ||
            (btnStatus == BUTTON_LONG_PRESS))
        {
            // Cycle through items.
            if (tapWireReleased == true)
            {
                tapWireReleased = false;

                configPreset++;
                if (configPreset > configPresetEnd)
                {
                    configPreset = configPresetStart;
                }

                addPresetToQueue(configPreset);
                configTimer = millis();
            }
        }
        else if (btnStatus == BUTTON_RELEASED) // no button, check for timeout.
        {
            tapWireReleased = true;

            // If no press in X seconds, the preset will be selected and
            // we will move on to the next section.

            // Timer means we are waiting to see if we should save.
            // Stay in this mode until time has elapsed.
            if ((configTimer != 0) && (millis() - configTimer > configTimeMS))
            {
                configTimer = 0; // turn off

                // using if/then instead of switch/case so we can "break" out.
                switch (configState)
                {
                    case CONFIG_STATE_STARTUP:
                        startupPreset = configPreset;

                        // If different, flag that we need to save it.
                        if (startupPreset != orgStartupPreset)
                        {
                            configNeedsToBeSaved = true;
                        }

                        // Move on to next section.
                        configState = CONFIG_STATE_TURNS;
                        configPresetStart = presetTurnLeftFirst;
                        configPresetEnd = presetTurnLeftLast;
                        configPreset = turnLeftPreset; // current turn preset
                        break;
                    
                    case CONFIG_STATE_TURNS:
                        turnLeftPreset = configPreset;
                        // Sync the right turn preset to match.
                        turnRightPreset = presetTurnRightFirst + (turnLeftPreset - presetTurnLeftFirst);
                    
                        // If different, flag that we need to save it.
                        if (turnLeftPreset != orgTurnLeftPreset)
                        {
                            configNeedsToBeSaved = true;
                        }

                        // Move on tot he next section.
                        configState = CONFIG_STATE_BRAKES;
                        configPresetStart = presetBrakeFirst;
                        configPresetEnd = presetBrakeLast;
                        configPreset = brakePreset; // current brake preset
                        break;

                    case CONFIG_STATE_BRAKES:
                        brakePreset = configPreset;
                    
                        // If different, flag that we need to save it.
                        if (brakePreset != orgBrakePreset)
                        {
                            configNeedsToBeSaved = true;
                        }

                        // Move on tot he next section.
                        configState = CONFIG_STATE_EXIT; // done!
                        break;

                    default:
                        // This should never happen, but if it does, exit.
                        configState = CONFIG_STATE_EXIT;
                        break;
                } // switch (configState)

                if (configState != CONFIG_STATE_EXIT)
                {  
                    // Shut off old, apply new, reset timer.
                    addPresetToQueue(presetAllOff);
                    addPresetToQueue(configPreset);
                    configTimer = millis();                    
                }
            } // end of if millis()

            if (configState == CONFIG_STATE_EXIT)
            {
                // SAVE IF ANYTHING CHANGED!
                if (configNeedsToBeSaved == true)
                {
                    serializeConfig();
                }

                // This is the last one. Exit config.
                state = STATE_RUNNING;
                addPresetToQueue(presetAllOff);
            }
        } // end of button not pressed.
    } // end of handleConfig()


    /*----------------------------------------------------------------------*/
    void handleWorkblade()
    {
        int btnStatus = BUTTON_RELEASED;

        // For anything that needs to be done only once when entering this state.
        if (prevState != STATE_WORKBLADE)
        {
            prevState = STATE_WORKBLADE;

            // Start initial preset.
            addPresetToQueue(workbladePreset);

            orgWorkbladePreset = workbladePreset;

            configTimer = 0;
        }

        btnStatus = getLastPolledButtonStatus(buttonTapWire);
        if ((btnStatus == BUTTON_SHORT_PRESS) ||
            (btnStatus == BUTTON_LONG_PRESS))
        {
            if (tapWireReleased == true)
            {
                tapWireReleased = false;

                workbladePreset++;
                if (workbladePreset > presetWorkbladeLast)
                {
                    workbladePreset = presetWorkbladeFirst;
                }

                addPresetToQueue(workbladePreset);

                configTimer = millis(); // TODO: new timer?
            }
        }
        else if (btnStatus == BUTTON_RELEASED) // no button, check for timeout.
        {
            tapWireReleased = true;

            // If no press in X seconds, the preset will be selected and
            // we will move on to the next section.
            // Stay in this mode until time has elapsed.
            if ((configTimer != 0) && (millis() - configTimer > configTimeMS))
            {
                configTimer = 0; // turn off

                // SAVE IF IT WAS CHANGED!
                if (workbladePreset != orgWorkbladePreset)
                {
                    serializeConfig();
                }
            }
        }
    } // end of handleWorkblade()


    /*----------------------------------------------------------------------*/
    /* CONTINUOUS
    case 54:
    case 55:
    case 64:
    case 65:
    */
    bool presetIsContinuous(int preset)
    {
        bool isContinuous = false;

        for (int idx=0; idx < MAX_CONTINUOUS_PRESETS; idx++)
        {
            if (preset == continuousPresets[idx])
            {
                isContinuous = true;
                break;
            }
        }

        return isContinuous;
    }

    /* SOLID
    case 52:
    case 53:
    case 62:
    case 63:
    */
    bool presetIsSolid(int preset)
    {
        bool isSolid = false;

        for (int idx=0; idx < MAX_SOLID_PRESETS; idx++)
        {
            if (preset == solidPresets[idx])
            {
                isSolid = true;
                break;
            }
        }

        return isSolid;
    }

    /*----------------------------------------------------------------------*/
    void handlePresetQueue(void)
    {
        // If timer has expired, apply any pending preset.
        if ((presetQueueTimer != 0) && (millis() - presetQueueTimer > presetQueueTimeMS))
        {
            int preset = getPresetFromQueue();

            if (preset > 0)
            {
                applyPreset (preset);
            }

            presetQueueTimer = millis(); // Reset timer.
        }
    }

    void addPresetToQueue(int preset)
    {
        if (presetQueueCount < DEFAULT_PRESET_QUEUE_SIZE)
        {
            DEBUG_PRINT("[");
            if (preset < 10)
            {
                DEBUG_PRINT(" ");
            }
            DEBUG_PRINT(preset);
            DEBUG_PRINT("] ");
            presetQueue[presetQueueNextIn] = preset;
            presetQueueCount++;
            presetQueueNextIn++;
            if (presetQueueNextIn >= DEFAULT_PRESET_QUEUE_SIZE)
            {
                presetQueueNextIn = 0;
            }
        }
        else
        {
          DEBUG_PRINT("Preset queue full. Did not add ");
          DEBUG_PRINTLN(preset);
        }
    } // end of addPresetToQueue()

    /*----------------------------------------------------------------------*/
    int getPresetFromQueue(void)
    {
        int preset = -1;

        if (presetQueueCount > 0)
        {
            preset = presetQueue[presetQueueNextOut];
            presetQueueCount--;
            presetQueueNextOut++;
            if (presetQueueNextOut >= DEFAULT_PRESET_QUEUE_SIZE)
            {
                presetQueueNextOut = 0;
            }
        }
        else
        {
            preset = -1;
        }

        return preset;
    } // end of getPresetFromQueue()


    /*----------------------------------------------------------------------*/
    // void disableWiFi()
    // {
    //     adc_power_off();
    //     WiFi.disconnect(true);  // Disconnect from the network
    //     WiFi.mode(WIFI_OFF);    // Switch WiFi off
    // }


    /*----------------------------------------------------------------------*/
    /**
     * handleButton() can be used to override default button behaviour. Returning true
     * will prevent button working in a default way.
     * Replicating button.cpp
     */
    bool handleButton(uint8_t b)
    {
        // yield();
        return true; // Disable WLED button handling.
    } // end of handleButtion()


#if defined(BUILD_FOR_WOKWI)
    /*----------------------------------------------------------------------*/
    void showButtonStatus()
    {
        static int lastBtnStatus[WLED_MAX_BUTTONS] = { 0,0,0,0,0,0 };
        for (int btn=0; btn<WLED_MAX_BUTTONS; btn++)
        {
            int btnStatus = getLastPolledButtonStatus(btn);
            if (btnStatus != lastBtnStatus[btn])
            {
                lastBtnStatus[btn] = btnStatus;
                for (int idx=0; idx<WLED_MAX_BUTTONS; idx++)
                {
                    Serial.print(getLastPolledButtonStatus(idx));
                    Serial.print(" ");
                }

                Serial.print("(");
                Serial.print(getLastPolledTwoButtonStatus(buttonTurnLeft, buttonTurnRight));
                Serial.println(")");
                break;
            }
        }
      } // end of showButtonStatus()
#endif // BUILD_FOR_WOKWI

#if !defined(BUILD_FOR_WOKWI)    
    /*----------------------------------------------------------------------*/
    /*
     * addToConfig() can be used to add custom persistent settings to the cfg.json file in the "um" (usermod) object.
     * It will be called by WLED when settings are actually saved (for example, LED settings are saved)
     * If you want to force saving the current state, use serializeConfig() in your loop().
     *
     * CAUTION: serializeConfig() will initiate a filesystem write operation.
     * It might cause the LEDs to stutter and will cause flash wear if called too often.
     * Use it sparingly and always in the loop, never in network callbacks!
     *
     * addToConfig() will make your settings editable through the Usermod Settings page automatically.
     *
     * Usermod Settings Overview:
     * - Numeric values are treated as floats in the browser.
     *   - If the numeric value entered into the browser contains a decimal point, it will be parsed as a C float
     *     before being returned to the Usermod.  The float data type has only 6-7 decimal digits of precision, and
     *     doubles are not supported, numbers will be rounded to the nearest float value when being parsed.
     *     The range accepted by the input field is +/- 1.175494351e-38 to +/- 3.402823466e+38.
     *   - If the numeric value entered into the browser doesn't contain a decimal point, it will be parsed as a
     *     C int32_t (range: -2147483648 to 2147483647) before being returned to the usermod.
     *     Overflows or underflows are truncated to the max/min value for an int32_t, and again truncated to the type
     *     used in the Usermod when reading the value from ArduinoJson.
     * - Pin values can be treated differently from an integer value by using the key name "pin"
     *   - "pin" can contain a single or array of integer values
     *   - On the Usermod Settings page there is simple checking for pin conflicts and warnings for special pins
     *     - Red color indicates a conflict.  Yellow color indicates a pin with a warning (e.g. an input-only pin)
     *   - Tip: use int8_t to store the pin value in the Usermod, so a -1 value (pin not set) can be used
     *
     * See usermod_v2_auto_save.h for an example that saves Flash space by reusing ArduinoJson key name strings
     *
     * If you need a dedicated settings page with custom layout for your Usermod, that takes a lot more work.
     * You will have to add the setting to the HTML, xml.cpp and set.cpp manually.
     * See the WLED Soundreactive fork (code and wiki) for reference.  https://github.com/atuline/WLED
     *
     * I highly recommend checking out the basics of ArduinoJson serialization and deserialization in order to use custom settings!
     */
    void addToConfig(JsonObject &root)
    {
        JsonObject top = root.createNestedObject(CONFIG_SECTION_NAME);
        // save these vars persistently whenever settings are saved

        // Preset defaults
        top[CFG_JSON_BRAKE] = brakePreset;
        top[CFG_JSON_REVERSE] = reversePreset;
        top[CFG_JSON_RUNNING] = runningPreset;
        top[CFG_JSON_STARTUP] = startupPreset;
        top[CFG_JSON_TURN_LEFT] = turnLeftPreset;
        top[CFG_JSON_TURN_RIGHT] = turnRightPreset;
        top[CFG_JSON_HAZARD] = hazardPreset;
        top[CFG_JSON_WORKBLADE] = workbladePreset;

        // Buttons
        top[CFG_JSON_BUTTON_RUNNING] = buttonBrake;
        top[CFG_JSON_BUTTON_REVERSE] = buttonReverse;
        top[CFG_JSON_BUTTON_TURN_LEFT] = buttonTurnLeft;
        top[CFG_JSON_BUTTON_TURN_RIGHT] = buttonTurnRight;
        top[CFG_JSON_BUTTON_BRAKE] = buttonBrake;
        top[CFG_JSON_BUTTON_TAP_WIRE] = buttonTapWire;

        // Presets
        top[CFG_JSON_PRESET_ALL_OFF] = presetAllOff;

        top[CFG_JSON_PRESET_BRAKE_FIRST] = presetBrakeFirst;
        top[CFG_JSON_PRESET_BRAKE_LAST] = presetBrakeLast;
        top[CFG_JSON_PRESET_BRAKE_LEFT] = presetBrakeLeft;
        top[CFG_JSON_PRESET_BRAKE_RIGHT] = presetBrakeRight;
        top[CFG_JSON_PRESET_BRAKES_OFF] = presetBrakesOff;
        top[CFG_JSON_PRESET_BRAKE_PULSE] = presetBrakePulse;

        top[CFG_JSON_PRESET_REVERSE_FIRST] = presetReverseFirst;
        top[CFG_JSON_PRESET_REVERSE_LAST] = presetReverseLast;
        top[CFG_JSON_PRESET_REVERSE_OFF] = presetReverseOff;

        top[CFG_JSON_PRESET_RUNNING_FIRST] = presetRunningFirst;
        top[CFG_JSON_PRESET_RUNNING_LAST] = presetRunningLast;
        top[CFG_JSON_PRESET_RUNNING_OFF] = presetRunningOff;

        top[CFG_JSON_PRESET_STARTUP_FIRST] = presetStartupFirst;
        top[CFG_JSON_PRESET_STARTUP_LAST] = presetStartupLast;

        top[CFG_JSON_PRESET_TURN_LEFT_FIRST] = presetTurnLeftFirst;
        top[CFG_JSON_PRESET_TURN_LEFT_LAST] = presetTurnLeftLast;
        top[CFG_JSON_PRESET_TURN_LEFT_OFF] = presetTurnLeftOff;

        top[CFG_JSON_PRESET_TURN_RIGHT_FIRST] = presetTurnRightFirst;
        top[CFG_JSON_PRESET_TURN_RIGHT_LAST] = presetTurnRightLast;
        top[CFG_JSON_PRESET_TURN_RIGHT_OFF] = presetTurnRightOff;

        top[CFG_JSON_PRESET_TURN_BOTH_OFF] = presetTurnBothOff;

        top[CFG_JSON_PRESET_HAZARD_FIRST] = presetHazardFirst;
        top[CFG_JSON_PRESET_HAZARD_LAST] = presetHazardLast;
        top[CFG_JSON_PRESET_HAZARD_OFF] = presetHazardOff;

        top[CFG_JSON_PRESET_WORKBLADE_STARTUP] = presetWorkbladeStartup;
        top[CFG_JSON_PRESET_WORKBLADE_FIRST] = presetWorkbladeFirst;
        top[CFG_JSON_PRESET_WORKBLADE_LAST] = presetWorkbladeLast;
        top[CFG_JSON_PRESET_WORKBLADE_OFF] = presetWorkbladeOff;

        // Time values
        top[CFG_JSON_POWERUP_DELAY_MS] = powerupDelayMS;
        top[CFG_JSON_STARTUP_TIME_MS] = startupTimeMS;
        top[CFG_JSON_CONFIG_TIME_MS] = configTimeMS;
        top[CFG_JSON_TURNING_TIME_MS] = turningTimeMS;
        top[CFG_JSON_ANIMATION_TIME_MS] = animationTimeMS;
        top[CFG_JSON_HAZARD_TIME_MS] = hazardTimeMS;
        top[CFG_JSON_BRAKE_PULSE_TIME_MS] = brakePulseTimeMS;

        // Button times
        top[CFG_JSON_DEBOUNCE_TIME_MS] = debounceTimeMS;
        top[CFG_JSON_LONG_PRESS_TIME_MS] = longPressTimeMS;

        // Preset queue timing
        top[CFG_JSON_PRESET_QUEUE_TIME_MS] = presetQueueTimeMS;

        // Continuous and Solid presets
        JsonArray continuousPresetArray = top.createNestedArray("continuousPresets");
        for (int idx=0; idx < MAX_CONTINUOUS_PRESETS; idx++)
        {
            continuousPresetArray.add(continuousPresets[idx]);
        }

        JsonArray solidPresetArray = top.createNestedArray("solidPresets");
        for (int idx=0; idx < MAX_SOLID_PRESETS; idx++)
        {
            solidPresetArray.add(solidPresets[idx]);
        }
    }


    /*----------------------------------------------------------------------*/
    /*
     * readFromConfig() can be used to read back the custom settings you added with addToConfig().
     * This is called by WLED when settings are loaded (currently this only happens immediately after boot, or after saving on the Usermod Settings page)
     *
     * readFromConfig() is called BEFORE setup(). This means you can use your persistent values in setup() (e.g. pin assignments, buffer sizes),
     * but also that if you want to write persistent values to a dynamic buffer, you'd need to allocate it here instead of in setup.
     * If you don't know what that is, don't fret. It most likely doesn't affect your use case :)
     *
     * Return true in case the config values returned from Usermod Settings were complete, or false if you'd like WLED to save your defaults to disk (so any missing values are editable in Usermod Settings)
     *
     * getJsonValue() returns false if the value is missing, or copies the value into the variable provided and returns true if the value is present
     * The configComplete variable is true only if the "exampleUsermod" object and all values are present.  If any values are missing, WLED will know to call addToConfig() to save them
     *
     * This function is guaranteed to be called on boot, but could also be called every time settings are updated
     */
    bool readFromConfig(JsonObject &root)
    {
        // default settings values could be set here (or below using the 3-argument getJsonValue()) instead of in the class definition or constructor
        // setting them inside readFromConfig() is slightly more robust, handling the rare but plausible use case of single value being missing after boot (e.g. if the cfg.json was manually edited and a value was removed)

        JsonObject top = root[CONFIG_SECTION_NAME];

        bool configComplete = !top.isNull();

        // Uncomment this to use the config.
        // Use hard-coded defaults for now:

        // A 3-argument getJsonValue() assigns the 3rd argument as a default value if the Json value is missing

        // Preset Defaults
        configComplete &= getJsonValue(top[CFG_JSON_BRAKE], brakePreset, DEFAULT_BRAKE_PRESET);
        configComplete &= getJsonValue(top[CFG_JSON_REVERSE], reversePreset, DEFAULT_REVERSE_PRESET);
        configComplete &= getJsonValue(top[CFG_JSON_RUNNING], runningPreset, DEFAULT_RUNNING_PRESET);
        configComplete &= getJsonValue(top[CFG_JSON_STARTUP], startupPreset, DEFAULT_STARTUP_PRESET);
        configComplete &= getJsonValue(top[CFG_JSON_TURN_LEFT], turnLeftPreset, DEFAULT_TURN_LEFT_PRESET);
        configComplete &= getJsonValue(top[CFG_JSON_TURN_RIGHT], turnRightPreset, DEFAULT_TURN_RIGHT_PRESET);
        configComplete &= getJsonValue(top[CFG_JSON_HAZARD], hazardPreset, DEFAULT_HAZARD_PRESET);

        // Different, because there is only one of these.
        configComplete &= getJsonValue(top[CFG_JSON_WORKBLADE], workbladeStartupPreset, DEFAULT_PRESET_WORKBLADE_STARTUP);

        // Buttons
        configComplete &= getJsonValue(top[CFG_JSON_BUTTON_RUNNING], buttonBrake, DEFAULT_BUTTON_BRAKE);
        configComplete &= getJsonValue(top[CFG_JSON_BUTTON_REVERSE], buttonReverse, DEFAULT_BUTTON_REVERSE);
        configComplete &= getJsonValue(top[CFG_JSON_BUTTON_TURN_LEFT], buttonTurnLeft, DEFAULT_BUTTON_TURN_LEFT);
        configComplete &= getJsonValue(top[CFG_JSON_BUTTON_TURN_RIGHT], buttonTurnRight, DEFAULT_BUTTON_TURN_RIGHT);
        configComplete &= getJsonValue(top[CFG_JSON_BUTTON_BRAKE], buttonBrake, DEFAULT_BUTTON_BRAKE);
        configComplete &= getJsonValue(top[CFG_JSON_BUTTON_TAP_WIRE], buttonTapWire, DEFAULT_BUTTON_TAP_WIRE);

        // Presets
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_ALL_OFF], presetAllOff, DEFAULT_PRESET_ALL_OFF);

        configComplete &= getJsonValue(top[CFG_JSON_PRESET_BRAKE_FIRST], presetBrakeFirst, DEFAULT_PRESET_BRAKE_FIRST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_BRAKE_LAST], presetBrakeLast, DEFAULT_PRESET_BRAKE_LAST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_BRAKE_LEFT], presetBrakeLeft, DEFAULT_PRESET_BRAKE_LEFT);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_BRAKE_RIGHT], presetBrakeRight, DEFAULT_PRESET_BRAKE_RIGHT);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_BRAKES_OFF], presetBrakesOff, DEFAULT_PRESET_BRAKES_OFF);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_BRAKE_PULSE], presetBrakePulse, DEFAULT_PRESET_BRAKE_PULSE);

        configComplete &= getJsonValue(top[CFG_JSON_PRESET_REVERSE_FIRST], presetReverseFirst, DEFAULT_PRESET_REVERSE_FIRST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_REVERSE_LAST], presetReverseLast, DEFAULT_PRESET_REVERSE_LAST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_REVERSE_OFF], presetReverseOff, DEFAULT_PRESET_REVERSE_OFF);

        configComplete &= getJsonValue(top[CFG_JSON_PRESET_RUNNING_FIRST], presetRunningFirst, DEFAULT_PRESET_RUNNING_FIRST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_RUNNING_LAST], presetRunningLast, DEFAULT_PRESET_RUNNING_LAST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_RUNNING_OFF], presetRunningOff, DEFAULT_PRESET_RUNNING_OFF);

        configComplete &= getJsonValue(top[CFG_JSON_PRESET_STARTUP_FIRST], presetStartupFirst, DEFAULT_PRESET_STARTUP_FIRST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_STARTUP_LAST], presetStartupLast, DEFAULT_PRESET_STARTUP_LAST);

        configComplete &= getJsonValue(top[CFG_JSON_PRESET_TURN_LEFT_FIRST], presetTurnLeftFirst, DEFAULT_PRESET_TURN_LEFT_FIRST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_TURN_LEFT_LAST], presetTurnLeftLast, DEFAULT_PRESET_TURN_LEFT_LAST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_TURN_LEFT_OFF], presetTurnLeftOff, DEFAULT_PRESET_TURN_LEFT_OFF);

        configComplete &= getJsonValue(top[CFG_JSON_PRESET_TURN_RIGHT_FIRST], presetTurnRightFirst, DEFAULT_PRESET_TURN_RIGHT_FIRST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_TURN_RIGHT_LAST], presetTurnRightLast, DEFAULT_PRESET_TURN_RIGHT_LAST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_TURN_RIGHT_OFF], presetTurnRightOff, DEFAULT_PRESET_TURN_RIGHT_OFF);

        configComplete &= getJsonValue(top[CFG_JSON_PRESET_TURN_BOTH_OFF], presetTurnBothOff, DEFAULT_PRESET_TURN_BOTH_OFF);

        configComplete &= getJsonValue(top[CFG_JSON_PRESET_HAZARD_FIRST], presetHazardFirst, DEFAULT_PRESET_HAZARD_FIRST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_HAZARD_LAST], presetHazardLast, DEFAULT_PRESET_HAZARD_LAST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_HAZARD_OFF], presetHazardOff, DEFAULT_PRESET_HAZARD_OFF);

        configComplete &= getJsonValue(top[CFG_JSON_PRESET_WORKBLADE_STARTUP], presetWorkbladeStartup, DEFAULT_PRESET_WORKBLADE_STARTUP);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_WORKBLADE_FIRST], presetWorkbladeFirst, DEFAULT_PRESET_WORKBLADE_FIRST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_WORKBLADE_LAST], presetWorkbladeLast, DEFAULT_PRESET_WORKBLADE_LAST);
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_WORKBLADE_OFF], presetWorkbladeOff, DEFAULT_PRESET_WORKBLADE_OFF);

        // Timers
        configComplete &= getJsonValue(top[CFG_JSON_POWERUP_DELAY_MS], powerupDelayMS, DEFAULT_POWERUP_DELAY_MS);
        configComplete &= getJsonValue(top[CFG_JSON_STARTUP_TIME_MS], startupTimeMS, DEFAULT_STARTUP_TIME_MS);
        configComplete &= getJsonValue(top[CFG_JSON_CONFIG_TIME_MS], configTimeMS, DEFAULT_CONFIG_TIME_MS);
        configComplete &= getJsonValue(top[CFG_JSON_TURNING_TIME_MS], turningTimeMS, DEFAULT_TURNING_TIME_MS);
        configComplete &= getJsonValue(top[CFG_JSON_ANIMATION_TIME_MS], animationTimeMS, DEFAULT_ANIMATION_TIME_MS);
        configComplete &= getJsonValue(top[CFG_JSON_HAZARD_TIME_MS], hazardTimeMS, DEFAULT_HAZARD_TIME_MS);
        configComplete &= getJsonValue(top[CFG_JSON_BRAKE_PULSE_TIME_MS], brakePulseTimeMS, DEFAULT_BRAKE_PULSE_TIME_MS);

        // Button times
        configComplete &= getJsonValue(top[CFG_JSON_DEBOUNCE_TIME_MS], debounceTimeMS, DEFAULT_DEBOUNCE_TIME_MS);
        configComplete &= getJsonValue(top[CFG_JSON_LONG_PRESS_TIME_MS], longPressTimeMS, DEFAULT_LONG_PRESS_TIME_MS);

        // Preset queue time
        configComplete &= getJsonValue(top[CFG_JSON_PRESET_QUEUE_TIME_MS], presetQueueTimeMS, DEFAULT_PRESET_QUEUE_TIME_MS);

        // Continuous and Solid presets
        for (int idx=0; idx < MAX_CONTINUOUS_PRESETS; idx++)
        {
            configComplete &= getJsonValue(top["continuousePresets"][idx], continuousPresets[idx], -1);
        }

        for (int idx=0; idx < MAX_SOLID_PRESETS; idx++)
        {
            configComplete &= getJsonValue(top["solidPresets"][idx], solidPresets[idx], -1);
        }

        // Correct any bad values.
        if ((brakePreset < presetBrakeFirst) || (brakePreset > presetBrakeLast))
        {
            brakePreset = presetBrakeFirst;
        }

        if ((reversePreset < presetReverseFirst) || (reversePreset > presetReverseLast))
        {
            reversePreset = presetReverseFirst;
        }
        
        if ((runningPreset < presetRunningFirst) || (runningPreset > presetRunningLast))
        {
            runningPreset = presetRunningFirst;
        }
        
        if ((startupPreset < presetStartupFirst) || (startupPreset > presetStartupLast))
        {
            startupPreset = presetStartupFirst;
        }
        
        if ((turnLeftPreset < presetTurnLeftFirst) || (turnLeftPreset > presetTurnLeftLast))
        {
            turnLeftPreset = presetTurnLeftFirst;
        }
        
        if ((turnRightPreset < presetTurnRightFirst) || (turnRightPreset > presetTurnRightLast))
        {
            turnRightPreset = presetTurnRightFirst;
        }
        
        if ((hazardPreset < presetHazardFirst) || (hazardPreset > presetHazardLast))
        {
            hazardPreset = presetHazardFirst;
        }
        
        if ((workbladePreset < presetWorkbladeFirst) || (workbladePreset > presetWorkbladeLast))
        {
            workbladePreset = presetWorkbladeFirst;
        }
        
        // Only one workblade startup, if in use.
        //if (workbladeStartupPreset < presetWorkbladeStartupFirst) workbladeStartupPreset = presetWorkbladeStartupFirst;

        return configComplete;
    }


    /*----------------------------------------------------------------------*/
    /*
     * handleOverlayDraw() is called just before every show() (LED strip update frame) after effects have set the colors.
     * Use this to blank out some LEDs or set them to a different color regardless of the set effect mode.
     * Commonly used for custom clocks (Cronixie, 7 segment)
     */
    void handleOverlayDraw()
    {
        // strip.setPixelColor(0, RGBW32(0,0,0,0)) // set the first pixel to black
    }


    /*----------------------------------------------------------------------*/
    /*
     * getId() allows you to optionally give your V2 usermod an unique ID (please define it in const.h!).
     * This could be used in the future for the system to determine whether your usermod is installed.
     */
    uint16_t getId()
    {
        return USERMOD_ID_EXAMPLE;
    }
#endif // BUILD_FOR_WOKWI

    // More methods can be added in the future, this example will then be extended.
    // Your usermod will remain compatible as it does not need to implement all methods from the Usermod base class!

  /*---------------------------------------------------------------------------*/
  // Button routines
  /*---------------------------------------------------------------------------*/
  void initButtons()
  {
      // Configure pins and init variables.
      for (int btn=0; btn<WLED_MAX_BUTTONS; btn++)
      {
#if defined(BUILD_FOR_WOKWI)
          pinMode (buttonPin[btn], INPUT_PULLUP);
#endif // BUILD_FOR_WOKWI

          buttonPressedBefore[btn] = false;
          buttonLongPressed[btn] = false;
          buttonPressedTime[btn] = 0;
          buttonStatus[btn] = BUTTON_RELEASED;
      }
  }


    /*---------------------------------------------------------------------------*/
    // Scan all buttons and store status.
    /*---------------------------------------------------------------------------*/
    void pollButtons()
    {
        // Read them all at the same time.
        bool buttonPressedNow[WLED_MAX_BUTTONS];
        for (int b = 0; b < WLED_MAX_BUTTONS; b++)
        {
            buttonPressedNow[b] = isButtonPressed(b);
        }

        // Some logic copied from button.cpp
        unsigned long now = millis();

        for (int b=0; b<WLED_MAX_BUTTONS; b++)
        {
            //buttonStatus[b] = BUTTON_RELEASED;

            // momentary button logic
            if (buttonPressedNow[b]) // pressed
            {
                // Stop any timer.
                shortPressTimer[b] = 0;

                if (!buttonPressedBefore[b])
                {
                    buttonPressedBefore[b] = true;
                    buttonPressedTime[b] = now;
                }

                long dur = now - buttonPressedTime[b];

                if (dur > longPressTimeMS) // long press
                {
                    if (!buttonLongPressed[b])
                    {
                        buttonLongPressed[b] = true;
                    }

                    buttonStatus[b] = BUTTON_LONG_PRESS;
                }
                else if (dur > debounceTimeMS)
                {
                    buttonStatus[b] = BUTTON_PRESSED;
                }
                else
                {
                    buttonStatus[b] = BUTTON_RELEASED;
                }
            }
            else if (!buttonPressedNow[b] && buttonPressedBefore[b])
            {
                // released
                long dur = now - buttonPressedTime[b];

                if ((dur < debounceTimeMS) || (buttonLongPressed[b]))
                {
                    // Not long enough, or releasing a long press.
                    buttonLongPressed[b] = false;
                    buttonPressedBefore[b] = false;
                    buttonStatus[b] = BUTTON_RELEASED;
                }
                else //if (dur >= debounceTimeMS)
                {
                    // At least debounce and not a long press.
                    if (buttonStatus[b] != BUTTON_SHORT_PRESS)
                    {
                        shortPressTimer[b] = millis();
                    }
                    buttonStatus[b] = BUTTON_SHORT_PRESS;
                }
            }

            // Hold short press for some time...
            if ((shortPressTimer[b] != 0) && (millis() - shortPressTimer[b] > 50))
            {
                shortPressTimer[b] = 0;

                buttonLongPressed[b] = false;
                buttonPressedBefore[b] = false;
                buttonStatus[b] = BUTTON_RELEASED;
            }

        } // end of for (int b=0; b<WLED_MAX_BUTTONS; b++)
    }


  /*---------------------------------------------------------------------------*/
  // Retrieve last stored button status.
  /*---------------------------------------------------------------------------*/
  int getLastPolledButtonStatus(uint8_t btn)
  {
      return buttonStatus[btn];
  }


    /*---------------------------------------------------------------------------*/
    // Retrieve last stored status for two buttons.
    /*---------------------------------------------------------------------------*/
    int getLastPolledTwoButtonStatus(uint8_t btn1, uint8_t btn2)
    {
        if (buttonStatus[btn1] == buttonStatus[btn2])
        {
            if (buttonStatus[btn1] != lastTwoButtonStatus)
            {
                lastTwoButtonStatus = buttonStatus[btn1];
            }
            return lastTwoButtonStatus;
        }
        else
        {
            return 42;
        }
        //return lastTwoButtonStatus;
    }
#if !defined(BUILD_FOR_WOKWI)
};
#endif // BUILD_FOR_WOKWI

// End of usermod_v2_putco.h
