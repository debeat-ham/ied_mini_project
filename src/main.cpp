#include <Arduino.h>
#include "sensor.h"
#include "motors.h"
#include "pid.h"

// PID parameters
const float kp = 0.3; // Measured during testing, can retest
const float ki = 0;
const float kd = 0;


pid_controller controller(kp, ki, kd);

void setup() {
  setup_sensor();
  setup_motors();

  //Initialize serial monitor
  Serial.begin(9600);
}

void loop() {
  /* =================== Tunable Constants =================== */
  /* Note: Only one constant is tunable at a time,
   * i.e. you can only have one get_potentiometer uncommented. */
  
   // float p_val = get_potentiometer() * 0.3f; // Can be made higher if base_factor is lower
  float p_val = kp;
  
  float base_factor = 0.4f;
  // float base_factor = get_potentiometer();

  float speed = get_potentiometer() * -2;
  // float speed = -2;

  /* ================= End Tunable Constants ================= */
  float error = get_error();
  float res = controller.execute(error, p_val);
  float r_turn_factor = base_factor - res;
  float l_turn_factor = base_factor + res;
  
  if (car_enabled()) {
    set_left_motor(r_turn_factor * speed);
    set_right_motor(l_turn_factor  * speed);
  } else {
    set_left_motor(0);
    set_right_motor(0);
  }
  
  Serial.print("P value: ");
  Serial.print(p_val);
  Serial.print("\tSpeed: ");
  Serial.print(speed);
  Serial.print("\tBase factor");
  Serial.print(base_factor);
  Serial.println();

  // The PID mus tbe evaluated at a regular interval, so we delay a little.
  delay(20);
}