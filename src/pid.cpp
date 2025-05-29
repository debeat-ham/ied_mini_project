#include "pid.h"

float decay = 0.9f;

/// @brief Get the next output of the pid controller.
/// @note This function must be called at a regular time interval
/// @param error The measured error to input
/// @return PID output
float pid_controller::execute(float error) {
    float p_term = p * error;
    accumulation = accumulation * decay + error;
    float i_term = i * accumulation;
    // We probably don't have a smooth enough input to justify a d term
    float d_term = 0;

    return p_term + i_term + d_term;
}