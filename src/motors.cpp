#include <Arduino.h>

// PWM Pins

// Motor A - Left
const int enA = 9; // Enable A on PIN9
const int in1 = 2; // Input 1 on PIN2
const int in2 = 3; // Input 2 on PIN3

// Motor B - Right
const int enB = 10; // Enable B on PIN10
const int in3 = 4; // Input 3 on PIN4
const int in4 = 5; // Input 4 on PIN5


/// @brief Don't call this directly, use `set_left_motor` or `set_right_motor`
///        instead.
/// @param percent Any number between -1 and 1, inclusive. -1 Indicates full
///                reverse, 0 indicates a stop, and 1 indicates full forward.
/// @param enable Enable pin
/// @param hb1 H-Bridge pin 1
/// @param hb2 H-Bridge pin 2
void set_motor(float percent, int enable, int hb1, int hb2) {
  if (percent > 0) {
    digitalWrite(hb1, HIGH);
    digitalWrite(hb2, LOW);
  }
  else if (percent < 0) {
    digitalWrite(hb1, LOW);
    digitalWrite(hb2, HIGH);
  }

  percent = max(percent, -percent);
  int int_percent = (int)floor(percent * 255);
  int_percent = min(int_percent, 255); // in case percent was over 1
  analogWrite(enable, int_percent);
}

/// @brief Sets the speed of the left motor.
/// @param percent Any number between -1 and 1, inclusive. -1 Indicates full
///                reverse, 0 indicates a stop, and 1 indicates full forward.
void set_left_motor(float percent) {
  set_motor(percent, enA, in1, in2);
}

/// @brief Sets the speed of the right motor.
/// @param percent Any number between -1 and 1, inclusive. -1 Indicates full
///                reverse, 0 indicates a stop, and 1 indicates full forward.
void set_right_motor(float percent) {
  set_motor(percent, enB, in3, in4);
}

/// @brief Does GPIO initialization for the motor pins
void setup_motors() {
  // Define Motor Pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set Motors to Forward Direction initially
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}