#pragma once
#include <vector>

#include "Board.h"
#include "Sprite.h"

class Graphics {
public:
    Graphics(SDL_Renderer* gRender, SDL_Window* gWindow, int windowW, int windowH);
    ~Graphics();
    void DrawRect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);
    void DrawBoardSprites(Board* board);
    void DrawBG();
    void StartDraw();
    void Draw(Board* board);
    void EndDraw();
    void grabPickedTiles(const std::vector<int>& vector);

    int getOffset();
    int getMargin();
    float getScale();

    int getWindowWidth();
    int getWindowHeight();

    int getTileWidth();
    int getTileHeight();

private:
    void deleteAllTiles();
    void addSprite(Sprite* sprite); //deprecated
    void addSprite(Sprite* sprite, int n); //deprecated
    SDL_Renderer* const renderer;
    SDL_Window* const window;
    int windowWidth;
    int windowHeight;
    int tileOffset;
    int tileMargin;
    float tileScale;

    SDL_Rect tileRect;

    Sprite* graphicsBackground;
    Sprite* graphicsBase;
    Sprite* graphicsPicked;
    std::vector<int> graphicsPickedTiles;
    std::vector<Sprite*> graphicsTiles;
};