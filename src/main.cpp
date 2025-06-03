#include <Arduino.h>
#include "sensor.h"
#include "motors.h"
#include "pid.h"

// PID parameters
const float kp = 0.1;
const float ki = 0;
const float kd = 0;

const float speed = -1;

pid_controller controller(kp, ki, kd);

void setup() {
  setup_sensor();
  setup_motors();

  //Initialize serial monitor
  Serial.begin(9600);
}

void loop() {
  float error = get_error();
  float p_val = get_potentiometer() * 0.3f;
  float turn_factor = 0.5f + controller.execute(error, p_val);
  
  if (car_enabled()) {
    set_left_motor((1- turn_factor) * speed);
    set_right_motor((turn_factor)  * speed);
  } else {
    set_left_motor(0);
    set_right_motor(0);
  }
  
  Serial.print("P value: ");
  Serial.print(p_val);
  // Serial.print("\tLeft motor: ");
  // Serial.print(1 - turn_factor);
  // Serial.print("\tRight motor: ");
  // Serial.print(turn_factor);
  Serial.println();

  // The PID mus tbe evaluated at a regular interval, so we delay a little.
  delay(20);
}