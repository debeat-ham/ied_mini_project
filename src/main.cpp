#include <Arduino.h>
#include "sensor.h"
#include "motors.h"

// PID parameters
const float kp = 0.1;
const float ki = 0;
const float kd = 0;

void setup() {
  setup_sensor();
  setup_motors();

  //Initialize serial monitor
  Serial.begin(9600);
}

void loop() {
  float error = get_error();
  float turn_factor = 0.5f + error * kp;
  set_left_motor(1 - turn_factor);
  set_right_motor(turn_factor);

  Serial.print("Error: ");
  Serial.print(error);
  Serial.print("\tLeft motor: ");
  Serial.print(1 - turn_factor);
  Serial.print("\tRight motor: ");
  Serial.print(turn_factor);
  Serial.println();
  
}