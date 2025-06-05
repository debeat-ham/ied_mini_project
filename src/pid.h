#pragma once

class pid_controller
{
private:
    float p;
    float i;
    float d;
    float accumulation;

public:
    pid_controller(float p, float i, float d): p(p), i(i), d(d) {}
    float execute(float error, float p);
};
