#pragma once
#include <SDL2/SDL.h>

class Timer {
public:
    Timer();
    int GetDelta();
    bool hasPassed(int ms);

private:
    Uint32 timePrev;
};