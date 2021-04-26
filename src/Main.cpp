#include <time.h>

#include <cstdlib>

#include "Game.h"

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    Game game;
    while (game.getStatus() == true) {
		game.Update();
    }

    return 0;
}