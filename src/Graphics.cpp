#include "Graphics.h"

#include <algorithm>
#include <filesystem>
#include <stdexcept>

Graphics::Graphics(int windowW, int windowH) : renderer{nullptr}, window{nullptr}, windowWidth{windowW}, windowHeight{windowH}, texture_pack{"default"} {
    if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer) == -1) {
        throw std::runtime_error("SDL_CreateWindowAndRenderer");
    }
}

Graphics::~Graphics() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
}

void Graphics::drawRect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Rect rect{x, y, w, h};

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}

//clear the window
void Graphics::startDraw() {
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) < 0) {
        printf("SDL_SetRenderDrawColor error: %s\n", SDL_GetError());
    }
    SDL_RenderClear(renderer);
}

//draw graphics
void Graphics::endDraw() {
    SDL_RenderPresent(renderer);
}

std::list<Sprite*> Graphics::loadSprites(std::list<std::string> filenames, bool clear) {
    if (clear) sprites.clear();
    std::list<Sprite*> output;
    for (const auto& filename : filenames) {
        auto path = "../assets/textures/" + texture_pack + "/" + filename;
        auto result = std::find_if(sprites.begin(), sprites.end(), [&path](const auto& s) { return s->getPath() == path; });
        if (result == sprites.end()) {
            sprites.push_back(std::make_unique<Sprite>(path, renderer));
            output.push_back(sprites.back().get());
        } else {
            output.push_back(result->get());
        }
    }

    //std::list<Sprite*> output;
    //std::transform(sprites.end() - filenames.size(), sprites.end(), std::back_inserter(output), [](std::unique_ptr<Sprite>& s) { return s.get(); });

    return output;
}

void Graphics::changeTexturepack(int id) {
    switch (id) {
        case 0:
            texture_pack = "default";
            break;
        case 1:
            texture_pack = "alternative";
            break;
        default:
            return;
    }

    for (auto& sprite : sprites) {
        sprite->updateTex("../assets/textures/" + texture_pack + "/" + std::filesystem::path(sprite->getPath()).filename().c_str(), renderer);
    }
}

SDL_Renderer* const Graphics::getRenderer() {
    return renderer;
}

int Graphics::getWindowWidth() {
    return windowWidth;
}

int Graphics::getWindowHeight() {
    return windowHeight;
}