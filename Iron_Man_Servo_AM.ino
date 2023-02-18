/*
 
MIT License

Copyright (c) 2022 Crash Works 3D

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

DESCRIPTION
  ====================
  The purpose of this code is to automate the servos and LED eyes for the Iron Man helmet

  Inspiration from the early work by "XL97" of The RPF Community

DEVELOPED BY
  ====================
  Dropwire
  Cranshark
*/

// Version.  Don't change unless authorized by Cranshark
#define VERSION "0.1.1.2"

// Uncomment this line to enable sound for the S.U.E. expansion board
#define SOUND     

// Uncomment this line if implementing using WS2812 LEDs (NeoPixels)
// #define PIXELS

// Uncomment this line to enable Walsh MK85 Jaw Control (Open/Close)
// WARNING!!! Enabling WALSH85 Code will only compile/work with the correct combinations/configurations
//#define WALSH85

#if defined (SOUND) && defined (WALSH85)
#error "Invalid configuration.  Cannot compile both SOUND and WALSH85 code."
#endif

#if defined (PIXELS) && defined (WALSH85)
#error "Invalid configuration.  Cannot compile both PIXELS and WALSH85 code."
#endif

// Referenced libraries

// For installation instructions see https://github.com/adafruit/Adafruit_SoftServo

#include "Adafruit_SoftServo.h"
// Servo PWM Range is determined by: (Time/Frequency) x Duty Cycle(%) , Time is based on 1 second (1,000,000 Micro-Seconds) , Frequency in Hertz, and Duty Cycle as (% / 100)
// Example using MG90s Servos with a time of 1 Second (1,000,000 micro-Seconds) and Frequency of 50Hz (Hertz) and normal duty Cycle of .02 (2% Low) & .12 (12% High)  
// PWM_LOW = (1000000/50) x .02 , PWM_LOW = 400    <-- Optimal Setting for Authentic Tower Pro MG90s Servo
// PWM_HIGH = (1000000/50) x .12 , PWM_HIGH = 2400 <-- Optimal Setting for Authentic Tower Pro MG90s Servo

#define TPMG90S
//#define GENERIC
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
#define PWM_HIGH 9000 // Manual Servo Duty Cycle
#define PWM_LOW  200 //  Manual Servo Duty Cycle
#endif

#if !defined (TPMG90S)  && !defined (GENERIC) && !defined (MANUAL)
  #error At least one servo configuration needs to be defined.
#endif

#if (defined (TPMG90S) && defined (GENERIC) && defined (MANUAL)) || (defined (TPMG90S) && defined (GENERIC)) || (defined (GENERIC) && defined (MANUAL)) || (defined (TPMG90S) && defined (MANUAL))
  #error More than one servo configuration defined.  Only define one: TPMG90S, GENERIC, or MANUAL
#endif

// For installation instructions see: https://github.com/mathertel/OneButton
#include <OneButton.h>

#ifdef SOUND
// See: https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299#target_6
// Important!!! On the SD card copy the mp3 files into an mp3 directory
// Download and install the DFPlayerMiniLite library

#include "DFPlayerMiniCW3D.h"

// For installation and usage instructions see: https://github.com/nickgammon/SendOnlySoftwareSerial
#include <SendOnlySoftwareSerial.h>

#endif

#ifdef PIXELS
// For installation instructions see https://github.com/cpldcpu/light_ws2812
#include "WS2812.h"
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


#if defined (GENERIC) && (SERVO1_OPEN_POS < 10) || (SERVO2_CLOSE_POS < 10) || (SERVO2_OPEN_POS > 170) || (SERVO1_CLOSE_POS > 170)
  #error This servo configuration will not operate in a position less than 10° or greater than 170° 
#endif

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

#if defined (__AVR_ATtiny88__)
SendOnlySoftwareSerial serialObj(6); // Create object for serial communications TX only on pin pd6 (ATtiny88)
#endif

#if defined (__AVR_ATtiny85__)
SendOnlySoftwareSerial serialObj(3); // Create object for serial communications TX only on pin pd3 (ATtiny85)
#endif

DFPlayerMiniCW3D mp3Obj; // Create object for DFPlayer Mini
#endif

uint8_t curLedLevel = 0; // Start with off

// Used for timer controls in milliseconds
unsigned long curLedMillis = millis();

// User for timer controls in microseconds
unsigned long curLedMicros = micros();  


byte isOpen = true; // keep track of whether or not the faceplate is open

// Declare servo objects
Adafruit_SoftServo servo1; // create servo object to control servo 1
Adafruit_SoftServo servo2; // create servo object to control servo 2

#ifdef WALSH85
Adafruit_SoftServo servo3; // create servo object to control servo 3
#endif

// Define object for primary button to handle 
// multiple button press features:
// 1. Single Tap
// 2. Double Tap
// 3. Long Press
OneButton primaryButton = OneButton(BUTTON_PIN, true, true);

#ifdef PIXELS
// Create object for NEO LEDs
WS2812 pixels(NEO_NUM_LEDS);  
#endif

// State of the faceplate 1 = open, 0 = closed
#define FACEPLATE_CLOSED 0
#define FACEPLATE_OPEN   1
uint8_t facePlateCurMode = FACEPLATE_OPEN; // Keep track if the faceplate is open or closed

// State of the LED eyes 1 = on, 2 = off
#define LED_EYES_OFF 0
#define LED_EYES_ON  1

/**
 * Helper Method
 * Simulate a delay in processing without disabling the processor completely
 * 
 * @param[out] period - the amount of time in milliseconds to delay
 * @param[out] resolution -  MILLIS = milliseconds, MICROS = microseconds
 * 
 * See: https://randomnerdtutorials.com/why-you-shouldnt-always-use-the-arduino-delay-function/
*/
void simDelayMillis(unsigned long period){
  unsigned long delayMillis = millis() + period;
  while (millis() <= delayMillis)
  {
    byte x = 0; // dummy variable, does nothing
  }
}

void simDelayMicros(unsigned long period){
  unsigned long delayMicros = micros() + period;

  while (micros() <= delayMicros)
  {
    byte x = 0;
  }
}

/**
 * Initializes the primary button for multi-functions
 */
void initPrimaryButton(){
  primaryButton.attachClick(handlePrimaryButtonSingleTap);
  primaryButton.attachDoubleClick(handlePrimaryButtonDoubleTap);
  //primaryButton.attachLongPressStart(handlePrimaryButtonLongPress);
  primaryButton.attachDuringLongPress(handlePrimaryButtonLongPress);
  primaryButton.attachMultiClick(handlePrimaryButtonMultiPress);
}

#ifndef PIXELS
/**
 * Initialize the LED eyes
 */
void initLedEyes(){
  #if defined (__AVR_ATtiny88__)
  pinMode(EYE_LEFT_PIN, OUTPUT);
  pinMode(EYE_RIGHT_PIN, OUTPUT);
  pinMode(AUX_LED_PIN, OUTPUT); 
  #endif

  #if defined (__AVR_ATtiny85__)
    #if defined (PIXELS) && defined (SOUND)
      #else
        #ifdef PIXELS
        pinMode(EYE_LEFT_PIN, OUTPUT);
        #else
        #ifdef SOUND
        pinMode(EYE_RIGHT_PIN, OUTPUT);  // TODO: check if this is needed
        #else
        #ifdef WALSH85
        pinMode(EYE_LEFT_PIN, OUTPUT);  // TODO: check if this is needed
        #else
        pinMode(EYE_LEFT_PIN, OUTPUT);
        pinMode(EYE_RIGHT_PIN, OUTPUT);
        #endif
        #endif
        #endif
      #endif  
  #endif  
}
#else
/**
 * Initialize the NEO LEDs
 * NOTE: Current code is for WS2812 type LEDs.  See FastLED documentation for other LED types
 *       and modify below as needed.
 */
void initPixels(){
  pixels.setOutput(PIXELS_PIN);
  pixels.setColorOrderRGB();
}
#endif

/**
 * Simulate the eyes slowly blinking until fully lit
 */ 
void movieblink(){
  // pause for effect...
  simDelayMillis(300);

  int lowValue = 21;
  int delayInterval[] = { 210, 126, 84 };
  int delayVal = 0;

  // First blink on
  for (int i = 0; i <= lowValue; i++){
    setLedEyes(LED_MID); //Originally LED_LOW
    #if defined (__AVR_ATtiny88__)
    setAuxLeds(LOW);
    #endif
    delayVal = delayInterval[0]/lowValue;
    simDelayMillis(delayVal);
  }

  // Turn off
  setLedEyes(LED_OFF);
  #if defined (__AVR_ATtiny88__)
  setAuxLeds(HIGH);
  #endif
  simDelayMillis(delayInterval[0]);

  // Second blink on
  for (int i = 0; i <= lowValue; i++){
    setLedEyes(LED_MID);
    #if defined (__AVR_ATtiny88__)
    setAuxLeds(LOW);
    #endif
    delayVal = delayInterval[1]/lowValue;
    simDelayMillis(delayVal);
  }

  // Turn off
  setLedEyes(LED_OFF);
  #if defined (__AVR_ATtiny88__)
  setAuxLeds(HIGH);
  #endif 
  simDelayMillis(delayInterval[1]);

  // Third blink on
  setLedEyes(LED_MID); //Originally LED_LOW
  #if defined (__AVR_ATtiny88__)
  setAuxLeds(LOW);
  #endif
  simDelayMillis(delayInterval[2]);

  // Turn off
  setLedEyes(LED_OFF);
  #if defined (__AVR_ATtiny88__)
  setAuxLeds(HIGH);
  #endif
  simDelayMillis(delayInterval[2]);

  // All on
  setLedEyes(LED_HIGH);   
}

#ifdef SOUND
/**
 * Initialization method for DFPlayer Mini board
 */
 void init_player(){
  serialObj.begin(9600);

  bool dfInit = mp3Obj.begin(serialObj, false, true);

  simDelayMillis(1000); //Originally simDelay
  
  if(!dfInit){
    dfInit = mp3Obj.begin(serialObj, false, true);
    simDelayMillis(400); // originally 1000ms //Originally simDelay
  }
   
  mp3Obj.setTimeOut(500); //Set serial communictaion time out 500ms
    
  mp3Obj.volume(VOLUME);
  //mp3Obj.outputDevice(DFPLAYER_DEVICE_SD);
 }

/**
 * Method to play the sound effect for a specified feature
 */
void playSoundEffect(int soundEffect){
  mp3Obj.volume(VOLUME);
  simDelayMillis(90); //Originally simDelay
  mp3Obj.play(soundEffect);
}
#endif

/**
 * @brief Attaches servos
 * 
 */
void servosAttach(){
  servo1.attach(SERVO1_PIN, PWM_HIGH, PWM_LOW);
  servo2.attach(SERVO2_PIN, PWM_HIGH, PWM_LOW);

  #ifdef WALSH85
  servo3.attach(SERVO3_PIN, PWM_HIGH, PWM_LOW);
  #endif
}

/**
 * @brief Detaches servos
 * 
 */
void servosDetach(){
  servo1.detach();
  servo2.detach();

  #ifdef WALSH85
  servo3.detach();
  #endif
}

/**
 * @brief Moves the servos
 * 
 * @param pos1 
 * @param pos2 
 */
void servosMove(int pos1, int pos2){ //Originally uint8_t 4/17/22  
    servo1.write(pos1);
    servo2.write(pos2);
}

/**
 * Method to open face plate
 */
 void facePlateOpen(){
  // Re-attach the servos to their pins
  servosAttach();

  while(!servo1.attached()){
    simDelayMillis(10);
  }

  // Send data to the servos for movement
  int j = SERVO2_CLOSE_POS;

  for(int i = SERVO1_CLOSE_POS; i >= SERVO1_OPEN_POS; i--){
    servosMove(i, j);
    j++;

    simDelayMicros(SERVO_OPEN_SPEED);
  }
  #ifdef WALSH85
  simDelayMillis(225);
  servo3.write(SERVO3_OPEN_POS);
  simDelayMicros(JAW_OPEN_SPEED);
  #endif

  simDelayMillis(500); // wait doesn't wait long enough for servos to fully complete...
 
  // Detach so motors don't "idle"
  servosDetach();

  facePlateCurMode = FACEPLATE_OPEN;
 }

 /**
  * Method to close face plate
  */
 void facePlateClose(){
  // Re-attach the servos to their pins
  servosAttach();

  while(!servo1.attached()){
    simDelayMillis(10);
  }

  #ifdef WALSH85
     servo3.write(SERVO3_CLOSE_POS);
     simDelayMicros(JAW_CLOSE_SPEED);
     simDelayMillis(300); // wait doesn't wait long enough for servos to fully complete...
  #endif

  // Send data to the servos for movement
  int j = SERVO2_OPEN_POS;

  for(int i = SERVO1_OPEN_POS; i <= SERVO1_CLOSE_POS; i++){
    servosMove(i, j);
    j--;
    simDelayMicros(SERVO_CLOSE_SPEED);
  }

  simDelayMillis(500); // wait doesn't wait long enough for servos to fully complete...

  // Detach so motors don't "idle"
  servosDetach();

  facePlateCurMode = FACEPLATE_CLOSED;
 }

#ifndef PIXELS
/**
* Set the brightness of the LED eyes
*/
void setLedEyes(uint8_t ledLevel){
  switch (ledLevel){
    #if defined (__AVR_ATtiny85__)
    case LED_OFF:
      #ifdef SOUND
      pwmOff(EYE_RIGHT_PIN);
      curLedLevel = LED_OFF;
      break;
      #else
      #ifdef WALSH85
      pwmOff(EYE_LEFT_PIN);
      curLedLevel = LED_OFF;
      break;
      #else      
      pwmOff(EYE_LEFT_PIN);
      pwmOff(EYE_RIGHT_PIN);
      curLedLevel = LED_OFF;
      break;
      #endif
      #endif
      
     case LED_LOW:
      #ifdef SOUND
      pwmLow(EYE_RIGHT_PIN);
      curLedLevel = LED_LOW;
      break;
      #else
      #ifdef WALSH85
      pwmLow(EYE_LEFT_PIN);
      curLedLevel = LED_LOW;
      break;
      #else      
      pwmLow(EYE_LEFT_PIN);
      pwmLow(EYE_RIGHT_PIN);
      curLedLevel = LED_LOW;
      break;
      #endif
      #endif
    
    case LED_MID:
      #ifdef SOUND
      pwmMid(EYE_RIGHT_PIN);
      curLedLevel = LED_MID;
      break;
      #else
      #ifdef WALSH85
      pwmMid(EYE_LEFT_PIN);
      curLedLevel = LED_MID;
      break;
      #else      
      pwmMid(EYE_LEFT_PIN);
      pwmMid(EYE_RIGHT_PIN);
      curLedLevel = LED_MID;
      break;
      #endif
      #endif
      
    case LED_HIGH:
      #ifdef SOUND
      pwmHigh(EYE_RIGHT_PIN);
      curLedLevel = LED_HIGH;
      break;
      #else
      #ifdef WALSH85
      pwmHigh(EYE_LEFT_PIN);
      curLedLevel = LED_HIGH;
      break;
      #else      
      pwmHigh(EYE_LEFT_PIN);
      pwmHigh(EYE_RIGHT_PIN);
      curLedLevel = LED_HIGH;
      break;
      #endif 
      #endif  
    default:
      break;
    #endif

    #if defined (__AVR_ATtiny88__)     
    case LED_OFF:
      pwmOff(EYE_LEFT_PIN);
      pwmOff(EYE_RIGHT_PIN);
      curLedLevel = LED_OFF;
      break;
    case LED_LOW:
      pwmLow(EYE_LEFT_PIN);
      pwmLow(EYE_RIGHT_PIN);
      curLedLevel = LED_LOW;
      break;
    case LED_MID:
      pwmMid(EYE_LEFT_PIN);
      pwmMid(EYE_RIGHT_PIN);
      curLedLevel = LED_MID;
      break;
    case LED_HIGH:
      pwmHigh(EYE_LEFT_PIN);
      pwmHigh(EYE_RIGHT_PIN);
      curLedLevel = LED_HIGH;
      break;    
    default:
      break;
    #endif  
  }
}

void pwmOff(uint8_t pin){  
  digitalWrite(pin, LOW);
}

void pwmLow(uint8_t pin){
  digitalWrite(pin,HIGH); //on
  digitalWrite(pin,LOW); //off
}

void pwmMid(uint8_t pin){
  digitalWrite(pin,HIGH); //on
  delayMicroseconds(10);
  digitalWrite(pin,LOW); //off
  delayMicroseconds(245);
}

void pwmHigh(uint8_t pin){
  digitalWrite(pin, HIGH);
}

#else
/**
* Set the brightness of the LED eyes
*/
void setLedEyes(uint8_t ledLevel){
  switch (ledLevel)
  {
  case LED_OFF:
    setPixels(0, 0, 0);
    curLedLevel = LED_OFF;
    break;
  case LED_LOW:
    setPixels(NEO_COLOR_LOW.r, NEO_COLOR_LOW.g, NEO_COLOR_LOW.b);
    curLedLevel = LED_LOW;
    break;
  case LED_MID:
    setPixels(NEO_COLOR_MID.r, NEO_COLOR_MID.g, NEO_COLOR_MID.b);
    curLedLevel = LED_MID;
    break;
  case LED_HIGH:
    setPixels(NEO_COLOR_HIGH.r, NEO_COLOR_HIGH.g, NEO_COLOR_HIGH.b);
    curLedLevel = LED_HIGH;
    break;
  default:
    break;
  }
}
#endif

/**
 * Method to dim or brighten both LED eyes
 */
void ledEyesFade(){
    switch (curLedLevel){
      case LED_OFF:
        curLedLevel = LED_LOW;
        break;
      case LED_LOW:
        curLedLevel = LED_MID;
        break;
      case LED_MID:
        curLedLevel = LED_HIGH;
        break;
      case LED_HIGH:
        curLedLevel = LED_OFF;
      default:
        break;
    }

    setLedEyes(curLedLevel);
}

/**
 * @brief Blinks S-O-S
*/
void blinkSOS(){
  int dotDelay = 200; // the delay between dots and dashes in milliseconds
  int letterDelay = dotDelay * 3; // the delay between letters in milliseconds
  int wordDelay = dotDelay * 7; // the delay between words in milliseconds

  // Blink "S"
  for (int i = 0; i < 3; i++){
    simDelayMillis(dotDelay);
    digitalWrite(EYE_LEFT_PIN, HIGH);
    simDelayMillis(dotDelay);
    digitalWrite(EYE_LEFT_PIN, LOW);
  }

  simDelayMillis(letterDelay);

  // Blink "O"
  for (int i = 0; i < 3; i++){
    simDelayMillis(dotDelay * 3);
    digitalWrite(EYE_LEFT_PIN, HIGH);
    simDelayMillis(dotDelay * 3);
    digitalWrite(EYE_LEFT_PIN, LOW);
  }

  simDelayMillis(letterDelay);

  // Blink "S"
  for (int i = 0; i < 3; i++){
    simDelayMillis(dotDelay);
    digitalWrite(EYE_LEFT_PIN, HIGH);
    simDelayMillis(dotDelay);
    digitalWrite(EYE_LEFT_PIN, LOW);
  }

  simDelayMillis(letterDelay);

  simDelayMillis(wordDelay);
}

#if defined (__AVR_ATtiny88__) 
/**
 * @brief Set the Aux Leds object
 * 
 * @param val HIGH = on; LOW = off
 */
void setAuxLeds(uint8_t val){
  digitalWrite(AUX_LED_PIN, val);
}
#endif

#ifdef PIXELS
/**
 * Method to turn the NEO LEDs on
 */
void setPixels(uint8_t r, uint8_t g, uint8_t b){
  cRGB color;
  color.r = r; color.g = g; color.b = b;

  for(uint8_t i = 0; i < NEO_NUM_LEDS; i++){
    pixels.set_crgb_at(i, color);
  }
  pixels.sync();
}
#endif

/**
 * Method to run sequence of sppecial effects when system first starts or sets up
 */
void startupFx(){
#ifdef SOUND
  #if defined (__AVR_ATtiny85__)
  simDelayMillis(300); // To allow for playing of startup sound when using ATtiny85
  playSoundEffect(SND_CLOSE);
  simDelayMillis(500); // Timing for Helmet Close Sound and delay to servo closing //Originally simDelay
  #else 
  // Below Operation for the ATtiny88
  playSoundEffect(SND_CLOSE);
  simDelayMillis(500); // Timing for Helmet Close Sound and delay to servo closing //Originally simDelay
  #endif
#endif

  facePlateClose();

  if(MOVIE_BLINK_ON_SETUP){
    movieblink();
    #if defined (__AVR_ATtiny88__)
    setAuxLeds(HIGH);
    #endif
  } else {
    setLedEyes(LED_HIGH);
    #if defined (__AVR_ATtiny88__)
    setAuxLeds(HIGH);
    #endif
  }
#ifdef SOUND
  simDelayMillis(800);
  playSoundEffect(SND_JARVIS);
#endif
  
}

/**
 * Method to execute special effects when the faceplate opens
 */
void facePlateOpenFx(){
#ifdef SOUND
  playSoundEffect(SND_OPEN);
#endif
  
  setLedEyes(LED_OFF);

  facePlateOpen();
}

/**
 * Method to execute special effects when the faceplate closes
 */
void facePlateCloseFx(){
#ifdef SOUND
  playSoundEffect(SND_CLOSE);
  simDelayMillis(1200); //Timing for Helmet Close Sound and delay to servo closing
#endif
  
  facePlateClose();

  if(MOVIE_BLINK_ON_CLOSE){
    movieblink();
  } else {
    setLedEyes(LED_HIGH);
  }
}

/**
 * Handle faceplate special effects
 */
void facePlateFx(){
  if (facePlateCurMode == FACEPLATE_OPEN){
    facePlateCloseFx();
  } else {
    facePlateOpenFx();
  }
}

/**
 * Event handler for when the primary button is tapped once
 */
void handlePrimaryButtonSingleTap(){
  facePlateFx();
}

/**
 * Event handler for when the primary button is double tapped
 */
void handlePrimaryButtonDoubleTap(){
  ledEyesFade();
}

/**
 * Event handler for when the primary button is pressed and held
 */
void handlePrimaryButtonLongPress(){
  blinkSOS(); // Switch is wired wrong, blink message on LED
  #ifdef SOUND
  playSoundEffect(SND_STT);
  #endif
}

/**
 * @brief Event handler for when the primary button is pressed multiple times
 * 
 */
void handlePrimaryButtonMultiPress(){
  switch (primaryButton.getNumberClicks())
  {
  case 3:
#ifdef PIXELS
    setPixels(NEO_COLOR_ALT.r, NEO_COLOR_ALT.g, NEO_COLOR_ALT.b);
    curLedLevel = LED_HIGH;
#endif
    break;
  
  default:
    break;
  }
}

/**
 * Monitor for when the primary button is pushed
 */
void monitorPrimaryButton(){
  primaryButton.tick();
}

/**
 * @brief Monitors how often to refresh servos
 */
 
volatile uint8_t counter = 0;
void monitorServoProcess(){
#if defined (__AVR_ATtiny85__) 
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {  
    counter = 0;
    servo1.refresh();
    servo2.refresh();

    #ifdef WALSH85
    servo3.refresh();
    #endif
  }
#endif

#if defined (__AVR_ATtiny88__)
 // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    servo1.refresh();
    servo2.refresh();

    #ifdef WALSH85
    servo3.refresh();
    #endif
  }
#endif      
}

/**
 * @brief Monitors how often to call processes for pwm
 * 
 */
void monitorPwmProcess(){
  int interval = 0;

  switch (curLedLevel)
  {
  case LED_HIGH:
    interval = 0;
    break;
  case LED_MID:
    interval = 1800;
    break;
  case LED_LOW:
    interval = 2000;
    break;
  default:
    break;
  }

  if((micros() - curLedMicros) > interval ){
    curLedMicros = micros();
    setLedEyes(curLedLevel);
  }
}

/**
 * Initialization method called by the Arduino library when the board boots up
 */
void setup() {
#ifdef SOUND
  init_player(); // initializes the sound player
#endif  
  
  initTimer0(); // initialize interrupt timer0 (see ATTiny85 & ATTiny88 datasheet)

#ifndef PIXELS
  initLedEyes(); // initialize the LED eyes
#else
  initPixels(); // initialize the NEO LEDs
#endif

  startupFx(); // Run the initial features

  initPrimaryButton(); // initialize the primary button
}

/**
 * Main program exeucution
 * This method will run perpetually on the board
 */
void loop() {
  monitorPrimaryButton(); // Since all features currently are tied to the one button...
  
#ifndef PIXELS
  if(curLedLevel != LED_HIGH){
    monitorPwmProcess();
  }
#endif

  // Room for future features ;)
}

/**
 * @brief Initializes the timer0 feature in the ATTiny85 (see datasheet) -or- ATTiny88 (see datasheet)
 */

void initTimer0(){
  // Set up the interrupt that will refresh the servo for us automagically
#if defined (__AVR_ATtiny88__)
  OCR0A = 0xAF;              // any number is OK (Configuration for ATtiny88)
  TIMSK0 |= _BV(OCIE0A);    // Turn on the compare interrupt (below!) - (Configuration for ATtiny88)
#endif  

#if defined (__AVR_ATtiny85__)
  OCR0A = 0x00;           // any number is OK (Configuration for ATtiny85)
  TIMSK |= _BV(TOIE0);   // (Configuration for ATtiny85)
#endif  
}

// We'll take advantage of the built in millis() timer that goes off
#if defined (__AVR_ATtiny88__)  
SIGNAL(TIMER0_COMPA_vect) // (Configuration for ATtiny88)
#endif 

#if defined (__AVR_ATtiny85__)  
ISR(TIMER0_OVF_vect) // (Configuration for ATtiny85)
#endif 
{
  monitorServoProcess();
}
