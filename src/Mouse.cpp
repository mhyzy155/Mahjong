#include "Mouse.h"

void Mouse::buttonDown(Graphics* gfx, Board* board, int& xindex, int& yindex) {
    xindex = -1;
    yindex = -1;
    SDL_GetMouseState(&mx, &my);
    int i = board->getBoardFloors() - 1;
    int** boardTiles = board->getBoard();
    bool tileFound = false;
    while (i >= 0 && !tileFound) {
        //printf("i: %d\n", i);
        float x = (float)board->getBoardWidth() / 2.0f + (float)(mx - i * gfx->getOffset() * gfx->getScale()) / (float)(gfx->getScale() * gfx->getTileWidth() + gfx->getMargin()) - (float)(gfx->getWindowWidth() + gfx->getMargin()) / (float)(gfx->getScale() * gfx->getTileWidth() + gfx->getMargin()) / 2.0f;
        float x2 = (gfx->getWindowWidth() + gfx->getScale() * gfx->getTileWidth() * (2 * (int)x - board->getBoardWidth()) - gfx->getMargin() * (board->getBoardWidth() - 1)) / 2 + i * gfx->getOffset() * gfx->getScale() + (int)x * gfx->getMargin() + gfx->getTileWidth() * gfx->getScale();
        float y = (float)board->getBoardHeight() / 2.0f + (float)(my + i * gfx->getOffset() * gfx->getScale()) / (float)(gfx->getScale() * gfx->getTileHeight() + gfx->getMargin()) - (float)(gfx->getWindowHeight() + gfx->getMargin()) / (float)(gfx->getScale() * gfx->getTileHeight() + gfx->getMargin()) / 2.0f;
        float y2 = (gfx->getWindowHeight() + gfx->getScale() * gfx->getTileHeight() * (2 * (int)y - board->getBoardHeight()) - gfx->getMargin() * (board->getBoardHeight() - 1)) / 2 - i * gfx->getOffset() * gfx->getScale() + (int)y * gfx->getMargin() + gfx->getTileHeight() * gfx->getScale();
        //printf("y1: %f, y2: %f, my: %d, delta: %f\n", y, y2, my, (y2 - my));

        if (x >= 0 && x < board->getBoardWidth() && (x2 - mx) > 0 && y >= 0 && y < board->getBoardHeight() && (y2 - my) > 0 && boardTiles[i][(int)y * board->getBoardWidth() + (int)x] != board->getBoardEmpty()) {
            if (i == (board->getBoardFloors() - 1) && boardTiles[i][(int)y * board->getBoardWidth() + (int)x] != board->getBoardEmpty()) {
                tileFound = true;
                xindex = (int)x;
                yindex = (int)y;
                //printf("x: %d, y: %d, floor: %d\n", (int)x, (int)y, i);
            } else if (boardTiles[i][(int)y * board->getBoardWidth() + (int)x] != board->getBoardEmpty() && boardTiles[i + 1][(int)y * board->getBoardWidth() + (int)x] == board->getBoardEmpty()) {
                tileFound = true;
                xindex = (int)x;
                yindex = (int)y;
                //printf("x: %d, y: %d, floor: %d\n", (int)x, (int)y, i);
            }
        }

        if (!tileFound) i--;
    }
    //printf("\n\n");
}

bool Mouse::isPressed(SDL_Rect rect) {
    SDL_GetMouseState(&mx, &my);
    return (mx >= rect.x && mx < (rect.x + rect.w) && my >= rect.y && my < (rect.y + rect.h)) ? true : false;
}
