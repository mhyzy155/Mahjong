#pragma once
#include <vector>

#include "Board.h"
#include "Sprite.h"

class Graphics {
public:
    Graphics(SDL_Renderer* gRender, SDL_Window* gWindow, int windowW, int windowH);
    ~Graphics();
    void DrawRect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);
    void DrawSprites(Board* board);
    void DrawBG();
    void StartDraw();
    void Draw(Board* board);
    void EndDraw();
    void addSprite(Sprite* sprite);
    void addSprite(Sprite* sprite, int n);
    void deleteAllSprites();

    void grabPickedTiles(std::vector<int> vector);

    int getOffset();
    int getMargin();
    float getScale();

    int getWindowWidth();
    int getWindowHeight();

    int getTileWidth();
    int getTileHeight();

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    int windowWidth;
    int windowHeight;
    int tileOffset;
    int tileMargin;
    float tileScale;

    int tileWidth;
    int tileHeight;

    Sprite* graphicsBackground;
    Sprite* graphicsBase;
    Sprite* graphicsPicked;
    std::vector<int> graphicsPickedTiles;
    std::vector<Sprite*> graphicsTiles;
};