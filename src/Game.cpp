#include "Game.h"

Game::Game() : graphics{new Graphics(1600, 900)}, mouse{new Mouse()}, state{true, true, 0, 3}, scene_mgr{graphics} {}

Game::~Game() {
    state.running = false;

    if (mouse) {
        delete mouse;
        mouse = nullptr;
    }

    if (graphics) {
        delete graphics;
        graphics = nullptr;
    }
}

void Game::Update() {
    //int dtime = timer.GetDelta();
    graphics->startDraw();
    scene_mgr.draw();
    graphics->endDraw();

    /*///FPS counter
    if (dtime > 0) {
        printf("FPS: %d\n", 1000 / dtime);
    } else {
        printf("Inf.\n");
    } */

    SDL_Event event;
    while (SDL_WaitEventTimeout(&event, 10)) {
        switch (event.type) {
            case SDL_QUIT:
                state.running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                scene_mgr.react(mouse, state);
                break;
        }
    }
}

bool Game::getStatus() {
    return state.running;
}

void Game::setStatus(bool status) {
    state.running = status;
}
