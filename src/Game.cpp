#include "Game.h"

Game::Game() : graphics{new Graphics(1600, 900)}, mouse{new Mouse()}, state{true, true, 0, 3}, scene_mgr{graphics} {}

Game::~Game() {
    state.running = false;

    if(mouse) {
        delete mouse;
        mouse = nullptr;
    }

    if (graphics) {
        delete graphics;
        graphics = nullptr;
    }
}

void Game::Update() {
    int dtime = timer.GetDelta();
    SDL_Event event;
    //while (state.running) {
        graphics->StartDraw();
        scene_mgr.draw();
        graphics->EndDraw();

        /*
        ///FPS counter
        if (dtime > 0) {
            printf("FPS: %d\n", 1000 / dtime);
        } else {
            printf("Inf.\n");
        }
        */

        if (SDL_WaitEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    state.running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    scene_mgr.react(mouse, state);
                    break;
            }
        }
    //}
}

bool Game::getStatus() {
    return state.running;
}

void Game::setStatus(bool status) {
    state.running = status;
}
