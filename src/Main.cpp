#include <time.h>

#include <cstdlib>

#include "Game.h"

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        Game game;
        while (game.getStatus() == true) {
            game.Update();
        }
    } else {
        printf("SDL_Init error\n");
    }

    SDL_Quit();
    return 1;
}