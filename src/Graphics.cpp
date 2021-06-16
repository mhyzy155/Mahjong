#include "Graphics.h"
#include <stdexcept>
#include <algorithm>

//#include <SDL2/SDL_ttf.h>

Graphics::Graphics(int windowW, int windowH): renderer{nullptr}, window{nullptr}, windowWidth{windowW}, windowHeight{windowH}, texture_pack{"default"} {
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

void Graphics::DrawRect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Rect rect{x,y,w,h};

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}

/*
void Graphics::DrawBoardSprites(Board* board) {
    graphicsBackground->draw((windowWidth - graphicsBackground->getRect().w) / 2, (windowHeight - graphicsBackground->getRect().h) / 2, renderer);

    int** TilesBoard = board->getBoard();
    int empty = board->getBoardEmpty();
    int boardWidth = board->getBoardWidth();
    int boardHeight = board->getBoardHeight();

    for (int i = 0; i < board->getBoardFloors(); i++) {
        for (int y = 0; y < boardHeight; y++) {
            for (int x = 0; x < boardWidth; x++) {
                int spriteindex = TilesBoard[i][y * boardWidth + x];
                if (spriteindex != empty) {
                    graphicsBase->draw((windowWidth + tileScale * graphicsTiles[spriteindex]->getRect().w * (2 * x - boardWidth) - tileMargin * (boardWidth - 1)) / 2 + (i - 1) * tileOffset * tileScale + x * tileMargin, (windowHeight + tileScale * graphicsTiles[spriteindex]->getRect().h * (2 * y - boardHeight) - tileMargin * (boardHeight - 1)) / 2 - i * tileOffset * tileScale + y * tileMargin, tileScale, renderer);
                }
            }
        }

        for (int y = 0; y < boardHeight; y++) {
            for (int x = 0; x < boardWidth; x++) {
                int spriteindex = TilesBoard[i][y * boardWidth + x];
                if (spriteindex != empty) {
                    graphicsTiles[spriteindex]->draw((windowWidth + tileScale * graphicsTiles[spriteindex]->getRect().w * (2 * x - boardWidth) - tileMargin * (boardWidth - 1)) / 2 + i * tileOffset * tileScale + x * tileMargin, (windowHeight + tileScale * graphicsTiles[spriteindex]->getRect().h * (2 * y - boardHeight) - tileMargin * (boardHeight - 1)) / 2 - i * tileOffset * tileScale + y * tileMargin, tileScale, renderer);
                    for (std::vector<int>::iterator it = graphicsPickedTiles.begin(); it != graphicsPickedTiles.end(); ++it) {
                        if (*it == (y * boardWidth + x) && i == (board->getBoardFloors() - 1)) {
                            graphicsPicked->draw((windowWidth + tileScale * graphicsPicked->getRect().w * (2 * x - boardWidth) - tileMargin * (boardWidth - 1)) / 2 + i * tileOffset * tileScale + x * tileMargin, (windowHeight + tileScale * graphicsPicked->getRect().h * (2 * y - boardHeight) - tileMargin * (boardHeight - 1)) / 2 - i * tileOffset * tileScale + y * tileMargin, tileScale, renderer);
                        } else if (*it == (y * boardWidth + x) && TilesBoard[i + 1][y * boardWidth + x] == empty) {
                            graphicsPicked->draw((windowWidth + tileScale * graphicsPicked->getRect().w * (2 * x - boardWidth) - tileMargin * (boardWidth - 1)) / 2 + i * tileOffset * tileScale + x * tileMargin, (windowHeight + tileScale * graphicsPicked->getRect().h * (2 * y - boardHeight) - tileMargin * (boardHeight - 1)) / 2 - i * tileOffset * tileScale + y * tileMargin, tileScale, renderer);
                        }
                    }
                }
            }
        }
    }
}

void Graphics::DrawBG() {
    graphicsBackground->draw((windowWidth - graphicsBackground->getRect().w) / 2, (windowHeight - graphicsBackground->getRect().h) / 2, renderer);
} */

//clear the window
void Graphics::StartDraw() {
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) < 0) {
        printf("SDL_SetRenderDrawColor error: %s\n", SDL_GetError());
    }
    SDL_RenderClear(renderer);
}

/*
//clear the window and draw graphics
void Graphics::Draw(Board* board) {
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) < 0) {
        printf("SDL_SetRenderDrawColor error: %s\n", SDL_GetError());
    }
    SDL_RenderClear(renderer);

    graphicsBackground->draw((windowWidth - graphicsBackground->getRect().w) / 2, (windowHeight - graphicsBackground->getRect().h) / 2, renderer);
    DrawBoardSprites(board);

    SDL_RenderPresent(renderer);
} */

//draw graphics
void Graphics::EndDraw() {
    SDL_RenderPresent(renderer);
}

std::list<Sprite*> Graphics::loadSprites(std::list<std::string> filenames){
    sprites.clear();
    for(const auto& filename : filenames){
        sprites.push_back(std::make_unique<Sprite>("../assets/textures/" + texture_pack + "/" + filename, renderer));
    }

    std::list<Sprite*> output;
    std::transform(sprites.begin(), sprites.end(), std::back_inserter(output), [](std::unique_ptr<Sprite> &s){return s.get();});

    return output;
}

SDL_Renderer* const Graphics::getRenderer(){
    return renderer;
}

int Graphics::getWindowWidth() {
    return windowWidth;
}

int Graphics::getWindowHeight() {
    return windowHeight;
}