// Uncomment this line to enable sound for the S.U.E. expansion board
//#define SOUND

// Uncomment this line if implementing using WS2812 LEDs (NeoPixels)
//#define PIXELS

// Uncomment this line to enable Walsh MK85 Jaw Control (Open/Close)
// WARNING!!! Enabling WALSH85 Code will only compile/work with the correct combinations/configurations
//#define WALSH85

// Servo PWM Range is determined by: (Time/Frequency) x Duty Cycle(%) , Time is based on 1 second (1,000,000 Micro-Seconds) , Frequency in Hertz, and Duty Cycle as (% / 100)
// Example using MG90s Servos with a time of 1 Second (1,000,000 micro-Seconds) and Frequency of 50Hz (Hertz) and normal duty Cycle of .02 (2% Low) & .12 (12% High)  
// PWM_LOW = (1000000/50) x .02 , PWM_LOW = 400    <-- Optimal Setting for Authentic Tower Pro MG90s Servo
// PWM_HIGH = (1000000/50) x .12 , PWM_HIGH = 2400 <-- Optimal Setting for Authentic Tower Pro MG90s Servo

//#define TPMG90S
#define GENERIC
//#define MANUAL

#ifdef TPMG90S
#define PWM_HIGH 2400 // Authentic Tower Pro MG90s Servo using 12% Duty Cycle
#define PWM_LOW  400 // Authentic Tower Pro MG90s Servo using 2% Duty Cycle
#endif

#ifdef GENERIC
#define PWM_HIGH 2600 // Generic MG90s Servo using 13% Duty Cycle
#define PWM_LOW  200 // Generic MG90s Servo using 1% Duty Cycle
#endif

// Use these settings for manual configuration of servos
#ifdef MANUAL
#define PWM_HIGH 2500 // Manual Servo Duty Cycle
#define PWM_LOW  300 //  Manual Servo Duty Cycle
#endif

// Declare pin settings
#if defined (__AVR_ATtiny85__) // A.L.I.S.H.A Mini II
#define SERVO1_PIN                               0 // pin for servo 1 (Configuration for ATtiny85)
#define SERVO2_PIN                               1 // pin for servo 2 (Configuration for ATtiny85)
#define BUTTON_PIN                               2 // pin for switch/button (Configuration for ATtiny85)
#define EYE_LEFT_PIN                             3 // pin for left LED eye or DFPlayer (TX) // Tested and Working
#ifdef PIXELS
#define PIXELS_PIN                               4 // pin repurposed for Neo Pixels
#else
#ifdef WALSH85
#define SERVO3_PIN                               4 // pin for servo 3 (Walsh85 Jaw Control) - Configuration for ATtiny85
#else
#define EYE_RIGHT_PIN                            4 // pin for right LED eye
#endif
#endif
#define AUX_LED_PIN                              5 // pin for Reset 
#endif

#if defined (__AVR_ATtiny88__) // A.L.I.S.H.A MK88
#define SERVO1_PIN                               9  // pin for servo 1 (Configuration for ATtiny88)
#define SERVO2_PIN                               10 // pin for servo 2 (Configuration for ATtiny88)
#define BUTTON_PIN                               8  // pin for switch/button (Configuration for ATtiny88)
#define PIXELS_PIN                               7  // pin for Neo-PIXELS (WS2812) (Configuration for ATtiny88)
#ifdef WALSH85
#define SERVO3_PIN                               11 // pin for servo 3 (Walsh85 Jaw Control) - Configuration for ATtiny85
#endif
#define EYE_LEFT_PIN                             3 // pin for left LED eye
#define EYE_RIGHT_PIN                            4 // pin for right LED eye
#define AUX_LED_PIN                              5 // pin for aux LED
#endif

// Declare variables for servo control
#define SERVO_CLOSE_SPEED                     3200 // set the speed of the servo close function (0 = Max Speed  / 10000 = Slowest Speed) 
#define SERVO_OPEN_SPEED                         0 // set the speed of the servo opening recommend set to max speed to aid in lift (0 = Max Speed  / 10000 = Slowest Speed) 

//Servo 3 (Walsh85 Jaw Control) variables for servo speed control
#define JAW_CLOSE_SPEED                        400 // set the speed of the servo close function (0 = Max Speed  / 10000 = Slowest Speed) , Originally Set to 500
#define JAW_OPEN_SPEED                           0 // set the speed of the servo opening recommend set to max speed to aid in lift (0 = Max Speed  / 10000 = Slowest Speed) 

// In Dual Servo Configuration the servos move in opposing directions, so the angles of the servos will be opposite to each other. 
// Normal Servo range is 0° ~ 180°, for initial setup the range has been adjusted to 20° ~ 160°, this allows for a 20° adjustment at both ends of the servo range.
// See Helmet tutorial for further information on servo setup.
#define SERVO1_OPEN_POS                         20 // set the open position of servo 1
#define SERVO2_OPEN_POS                        160 // set the open position of servo 2
#define SERVO1_CLOSE_POS                       160 // set the closed position of servo 1
#define SERVO2_CLOSE_POS                        20 // set the closed position of servo 2

#ifdef WALSH85
//Servo 3 (Walsh85 Jaw Control) Open / Close Angle , 90° range of motion, do not set close angle to 0°, actual starting point is 10°
#define SERVO3_OPEN_POS                        100 // set the open position of servo 3
#define SERVO3_CLOSE_POS                        10 // set the closed position of servo 3
#endif

#ifdef PIXELS
#define NEO_NUM_LEDS                              2 // Number of LEDs attached to the NEO pin
#define NEO_COLOR_HIGH      (cRGB){ 255, 255, 255 } // Sets the rgb color for high mode
#define NEO_COLOR_MID       (cRGB){ 175, 175, 175 } // Sets the rgb color for high mode
#define NEO_COLOR_LOW          (cRGB){ 75, 75, 75 } // Sets the rgb color for high mode
#define NEO_COLOR_ALT           (cRGB){ 255, 0, 0 } // Alternate color
#endif

// Declare variables for button control
#define MOVIE_BLINK_ON_SETUP 1 // set to 1 to Blink LEDs on Initial Power Up / Setup, Sequence based on Avengers Movie
#define MOVIE_BLINK_ON_CLOSE 0 // set to 1 to Blink LEDs on close of faceplate, Sequence based on Avengers Movie

// Levels for LED eyes
#define LED_OFF                                   0
#define LED_LOW                                   1
#define LED_MID                                   2
#define LED_HIGH                                  3

// Declare variables for sound control
#ifdef SOUND
#define VOLUME                                   29 // sound board volume level (30 is max)
#define SND_CLOSE                                 1 // sound track for helmet closing sound
#define SND_JARVIS                                2 // sound track for JARVIS sound
#define SND_OPEN                                  3 // sound track for helmet opening sound
#define SND_STT                                   7 // music activated on long button press
#endif
