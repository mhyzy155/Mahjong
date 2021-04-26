#include "Timer.h"

#include <SDL2/SDL.h>

Timer::Timer() : timePrev(SDL_GetTicks()) {
}

int Timer::GetDelta() {
    int delta = SDL_GetTicks() - timePrev;
    timePrev = SDL_GetTicks();
    return delta;
}

bool Timer::hasPassed(int ns) {
    int delta = SDL_GetTicks() - timePrev;
    if (delta > ns) {
        timePrev = SDL_GetTicks();
        return true;
    } else
        return false;
}
