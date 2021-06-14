#include "Graphics.h"

#include <SDL2/SDL_ttf.h>

Graphics::Graphics(SDL_Renderer* gRender, SDL_Window* gWindow, int windowW, int windowH): renderer{gRender}, window{gWindow}, windowWidth{windowW}, windowHeight{windowH} {
    tileOffset = 8;
    tileMargin = 4;
    tileScale = 1;
    std::string texture_path = "default";
    graphicsBackground = new Sprite("../assets/textures/" + texture_path + "/background.jpg", renderer);
    graphicsBase = new Sprite("../assets/textures/" + texture_path + "/base.png", renderer);
    graphicsPicked = new Sprite("../assets/textures/" + texture_path + "/pickedtile.png", renderer);

    for(int i = 0; i < 9; i++){
        graphicsTiles.push_back(new Sprite("../assets/textures/" + texture_path + "/new_tile" + std::to_string(i) + ".png", renderer));
    }
    tileRect = graphicsTiles[0]->getRect();
}

Graphics::~Graphics() {
    delete graphicsBackground;
    delete graphicsBase;
    delete graphicsPicked;
    deleteAllTiles();
}

void Graphics::DrawRect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Rect rect{x,y,w,h};

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}

void Graphics::DrawBoardSprites(Board* board) {
    graphicsBackground->DrawSprite((windowWidth - graphicsBackground->getRect().w) / 2, (windowHeight - graphicsBackground->getRect().h) / 2, renderer);

    int** TilesBoard = board->getBoard();
    int empty = board->getBoardEmpty();
    int boardWidth = board->getBoardWidth();
    int boardHeight = board->getBoardHeight();

    for (int i = 0; i < board->getBoardFloors(); i++) {
        for (int y = 0; y < boardHeight; y++) {
            for (int x = 0; x < boardWidth; x++) {
                int spriteindex = TilesBoard[i][y * boardWidth + x];
                if (spriteindex != empty) {
                    graphicsBase->DrawSprite((windowWidth + tileScale * graphicsTiles[spriteindex]->getRect().w * (2 * x - boardWidth) - tileMargin * (boardWidth - 1)) / 2 + (i - 1) * tileOffset * tileScale + x * tileMargin, (windowHeight + tileScale * graphicsTiles[spriteindex]->getRect().h * (2 * y - boardHeight) - tileMargin * (boardHeight - 1)) / 2 - i * tileOffset * tileScale + y * tileMargin, tileScale, renderer);
                }
            }
        }

        for (int y = 0; y < boardHeight; y++) {
            for (int x = 0; x < boardWidth; x++) {
                int spriteindex = TilesBoard[i][y * boardWidth + x];
                if (spriteindex != empty) {
                    graphicsTiles[spriteindex]->DrawSprite((windowWidth + tileScale * graphicsTiles[spriteindex]->getRect().w * (2 * x - boardWidth) - tileMargin * (boardWidth - 1)) / 2 + i * tileOffset * tileScale + x * tileMargin, (windowHeight + tileScale * graphicsTiles[spriteindex]->getRect().h * (2 * y - boardHeight) - tileMargin * (boardHeight - 1)) / 2 - i * tileOffset * tileScale + y * tileMargin, tileScale, renderer);
                    for (std::vector<int>::iterator it = graphicsPickedTiles.begin(); it != graphicsPickedTiles.end(); ++it) {
                        if (*it == (y * boardWidth + x) && i == (board->getBoardFloors() - 1)) {
                            graphicsPicked->DrawSprite((windowWidth + tileScale * graphicsPicked->getRect().w * (2 * x - boardWidth) - tileMargin * (boardWidth - 1)) / 2 + i * tileOffset * tileScale + x * tileMargin, (windowHeight + tileScale * graphicsPicked->getRect().h * (2 * y - boardHeight) - tileMargin * (boardHeight - 1)) / 2 - i * tileOffset * tileScale + y * tileMargin, tileScale, renderer);
                        } else if (*it == (y * boardWidth + x) && TilesBoard[i + 1][y * boardWidth + x] == empty) {
                            graphicsPicked->DrawSprite((windowWidth + tileScale * graphicsPicked->getRect().w * (2 * x - boardWidth) - tileMargin * (boardWidth - 1)) / 2 + i * tileOffset * tileScale + x * tileMargin, (windowHeight + tileScale * graphicsPicked->getRect().h * (2 * y - boardHeight) - tileMargin * (boardHeight - 1)) / 2 - i * tileOffset * tileScale + y * tileMargin, tileScale, renderer);
                        }
                    }
                }
            }
        }
    }
}

void Graphics::DrawBG() {
    graphicsBackground->DrawSprite((windowWidth - graphicsBackground->getRect().w) / 2, (windowHeight - graphicsBackground->getRect().h) / 2, renderer);
}

//clear the window
void Graphics::StartDraw() {
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) < 0) {
        printf("SDL_SetRenderDrawColor error: %s\n", SDL_GetError());
    }
    SDL_RenderClear(renderer);
}

//clear the window and draw graphics
void Graphics::Draw(Board* board) {
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) < 0) {
        printf("SDL_SetRenderDrawColor error: %s\n", SDL_GetError());
    }
    SDL_RenderClear(renderer);

    graphicsBackground->DrawSprite((windowWidth - graphicsBackground->getRect().w) / 2, (windowHeight - graphicsBackground->getRect().h) / 2, renderer);
    DrawBoardSprites(board);

    SDL_RenderPresent(renderer);
}

//draw graphics
void Graphics::EndDraw() {
    SDL_RenderPresent(renderer);
}

void Graphics::addSprite(Sprite* sprite) {
    graphicsTiles.push_back(sprite);
}

void Graphics::addSprite(Sprite* sprite, int n) {
    std::vector<Sprite*>::iterator it = graphicsTiles.begin();
    for (int i = 2; i <= n; i++) {
        it++;
    }
    graphicsTiles.insert(it, sprite);
}

void Graphics::deleteAllTiles() {
    for (std::vector<Sprite*>::iterator it = graphicsTiles.begin(); it != graphicsTiles.end(); ++it) {
        delete (*it);
    }
    graphicsTiles.clear();
}

void Graphics::grabPickedTiles(const std::vector<int>& vector) {
    graphicsPickedTiles = vector;
}

int Graphics::getOffset() {
    return tileOffset;
}

int Graphics::getMargin() {
    return tileMargin;
}

float Graphics::getScale() {
    return tileScale;
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

int Graphics::getTileWidth() {
    return tileRect.w;
}

int Graphics::getTileHeight() {
    return tileRect.h;
}
