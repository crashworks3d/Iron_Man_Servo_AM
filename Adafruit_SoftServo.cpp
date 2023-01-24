// This is an ultra simple software servo driver. For best
// results, use with a timer0 interrupt to refresh() all
// your servos once every 20 milliseconds!
// Written by Limor Fried for Adafruit Industries, BSD license

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Adafruit_SoftServo.h"
/**
 * @brief Construct a new Adafruit_SoftServo::Adafruit_SoftServo object
 *
 */
Adafruit_SoftServo::Adafruit_SoftServo(void) {
  isAttached = false;
  servoPin = 255;
  angle = 90;
}
/**
 * @brief Attach to a supplied pin
 *
 * @param pin The pin to attach to for controlling the servo
 */
void Adafruit_SoftServo::attach(uint8_t pin) {
  servoPin = pin;
  angle = 90;
  isAttached = true;
  pinMode(servoPin, OUTPUT);
  pwmHigh = 2400;
  pwmLow = 400;
}
/**
 * @brief Attach to a supplied pin
 * 
 * @param pin The pin to attach to for controlling the servo
 * @param pwmH Maps the mhz high end of the model of servo (see servos specs)
 * @param pwmL Maps the mhz low end of the model of servo (see servos specs)
*/
void Adafruit_SoftServo::attach(uint8_t pin, long pwmH = 2400, long pwmL = 400){
  servoPin = pin;
  angle = 90;
  isAttached = true;
  pinMode(servoPin, OUTPUT);
  pwmHigh = pwmH;
  pwmLow = pwmL;
}
/**
 * @brief Detach from the supplied pin
 *
 */
void Adafruit_SoftServo::detach(void) {
  isAttached = false;
  pinMode(servoPin, INPUT);
}
/**
 * @brief Get the attachment status of the pin
 *
 * @return boolean true: a pin is attached false: no pin is attached
 */
boolean Adafruit_SoftServo::attached(void) { return isAttached; }
/**
 * @brief Update the servo's angle setting and the corresponding pulse width
 *
 * @param a The target servo angle
 */
void Adafruit_SoftServo::write(uint8_t a) {
  angle = a;

  if (!isAttached)
    return;
  micros = map(a, 0, 180, pwmLow, pwmHigh);
}
/**
 * @brief Pulse the control pin for the amount of time determined when the angle
 * was set with `write`
 *
 */
void Adafruit_SoftServo::refresh(void) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(micros);
  digitalWrite(servoPin, LOW);
}
