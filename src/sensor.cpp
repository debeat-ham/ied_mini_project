#include <Arduino.h>

const int DETECTION_THRESHOLD = 500;
const int RESOLUTION_BITS = 10;

//Analog Sensor Pins
int S1 = A1;
int S2 = A2;
int S3 = A3;
int S4 = A4;
int S5 = A5;

// Potentiometer sensor
int P0 = A0;

const int enable_pin = 8;

int last_error;

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

    pinMode(P0, INPUT);
    analogReadResolution(RESOLUTION_BITS);

    pinMode(enable_pin, INPUT_PULLUP);
}


/// @brief Gets the error as detected by the sensors. A negative error means we
///        need to turn to the left, while a positive error means we need to
///        turn to the right.
float get_error() {
    int* sensor_array = read_sensor();
    // Change the readings int either high or low

    bool any_detected = false;

    float error_weights[] = {-2, -1, 0, 1, 2};
    float error = 0;
    for (int i = 0; i < 5; i++) {
        if (sensor_array[i] <= DETECTION_THRESHOLD) {
            any_detected = true;
            error += error_weights[i];
        }
    }

    if (!any_detected)
        return last_error;
    
    last_error = error;
    
    return error;
}

/// @brief Gets the analog reading from the potentiometer
/// @return A float between 0 and 1
float get_potentiometer() {
    return ((float)analogRead(P0)) / (1 << RESOLUTION_BITS);
}

bool car_enabled() {
    return digitalRead(enable_pin) == HIGH;
}