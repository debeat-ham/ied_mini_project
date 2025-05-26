#include <Arduino.h>

#define onboard 13

//Analog Sensor Pins
int S1 = A1;
int S2 = A2;
int S3 = A3;
int S4 = A4;
int S5 = A5;

// PWM Pins

// Motor A - Left
const int enA = 9; // Enable A on PIN9
const int in1 = 2; // Input 1 on PIN2
const int in2 = 3; // Iput 2 on PIN3

// Motor B - Right
const int enB = 10; // Enable B on PIN10
const int in3 = 4; // Input 3 on PIN4
const int in4 = 5; // Input 4 on PIN5




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

  //Initialize serial monitor
  Serial.begin(9600);
}

void loop() {
  //Code to continuously display sensor readings
  int* sensor_array = read_sensors();
  delay(200);

  // Set Speed via PWM using analogWrite(); Values range from 0-255
  analogWrite(enA, 255); // Motor A speed
  analogWrite(enB, 255); // Motor B speed

  delay(1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}
