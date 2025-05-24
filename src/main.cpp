#include <Arduino.h>

#define onboard 13

//Analog Sensor Pins
int S1 = A1;
int S2 = A2;
int S3 = A3;
int S4 = A4;
int S5 = A5;

//Function to read sensors, display results in serial monitor and return array of sensor values.
int* read_sensors(){
    int* sensor_array = new int[5];

    sensor_array[0] = analogRead(S1);
    sensor_array[1] = analogRead(S2);
    sensor_array[2] = analogRead(S3);
    sensor_array[3] = analogRead(S4);
    sensor_array[4] = analogRead(S5);

    Serial.print("Sensor Readings: ");
    Serial.print(sensor_array[0]);
    Serial.print(" ");
    Serial.print(sensor_array[1]);
    Serial.print(" ");
    Serial.print(sensor_array[2]);
    Serial.print(" ");
    Serial.print(sensor_array[3]);
    Serial.print(" ");
    Serial.println(sensor_array[4]);

    return sensor_array;
}

void setup() {
  //Define sensor array as an input
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  //Initialize serial monitor
  Serial.begin(9600);
}

void loop() {
  //Code to continuously display sensor readings
  int* sensor_array = read_sensors();
  delay(200);
}
