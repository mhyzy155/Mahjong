#include "Game.h"

Game::Game() : state{true, true, 0, 3}, scene_mgr{}, mouse{nullptr}, gfx{nullptr}, window{nullptr}, renderer{nullptr} {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        timer = new Timer();

        //windowWidth = 1280;
        //windowHeight = 720;
        windowWidth = 1600;
        windowHeight = 900;

        mouse = new Mouse();

        printf("Creating a window... ");
        if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer) == 0) {
            printf("- OK\n");
            gfx = new Graphics(renderer, window, windowWidth, windowHeight);
        } else {
            printf("- error!\n");
        }
    } else {
        printf("SDL_Init error\n");
        state.running = false;
    }
}

Game::~Game() {
    state.running = false;

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }

    printf("Closing a window... ");

    if (gfx != nullptr) {
        delete gfx;
        gfx = nullptr;
    }

    delete mouse;
    mouse = nullptr;
    delete timer;
    timer = nullptr;

    SDL_Quit();

    printf("- OK\n");
}

void Game::Update() {
    SDL_Event event;
    int dtime = timer->GetDelta();
    while (state.running) {
        gfx->StartDraw();
        scene_mgr.draw(gfx);
        gfx->EndDraw();

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
    }
}

bool Game::getStatus() {
    return state.running;
}

void Game::setStatus(bool status) {
    state.running = status;
}
