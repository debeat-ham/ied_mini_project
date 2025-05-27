#include <Arduino.h>

const int DETECTION_THRESHOLD = 500;

//Analog Sensor Pins
int S1 = A1;
int S2 = A2;
int S3 = A3;
int S4 = A4;
int S5 = A5;

int sensor_array[5] = {0, 0, 0, 0, 0};

/// @brief Reads the sensor array.
/// @return The 5 sensor readings, where each reading is an int from 0-1000:
///         1000 being a reflection detection (no black line) and 0 being no
///         reflection (there is a black line).
int* read_sensor(){
    sensor_array[0] = analogRead(S1);
    sensor_array[1] = analogRead(S2);
    sensor_array[2] = analogRead(S3);
    sensor_array[3] = analogRead(S4);
    sensor_array[4] = analogRead(S5);

    return sensor_array;
}

/// @brief Do GPIO initialization for the sensor pins
void setup_sensor() {
    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);
    pinMode(S4, INPUT);
    pinMode(S5, INPUT);
}


/// @brief Gets the error as detected by the sensors. A negative error means we
///        need to turn to the left, while a positive error means we need to
///        turn to the right.
float get_error() {
    int* sensor_array = read_sensor();
    // Change the readings int either high or low

    float error_weights[] = {-2, -1, 0, 1, 2};
    float error = 0;
    for (int i = 0; i < 5; i++) {
        if (sensor_array[i] <= DETECTION_THRESHOLD)
            error += error_weights[i];
    }
    return error;
}