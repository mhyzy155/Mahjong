#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "Graphics.h"

class Board {
   public:
    Board(Graphics* gfx, int tileset, bool mode_original, int different_tiles = 9);
    ~Board();
    void draw();
    bool react(int mx, int my);

   private:
    int loadBoard(int n);
    void clearBoard();
    void fillBoard();

    bool mode_original;
    int board_empty;
    int board_width;
    int board_height;
    int board_floors;
    int board_tiles;
    int tiles_left;
    bool** bFloor;
    int** iFloor;

    Graphics* graphics;
    Sprite* spr_base;
    Sprite* spr_picked;
    std::vector<Sprite*> spr_tiles;
    int tile_offset;
    int tile_margin;
    float tile_scale;
    int tile_width;
    int tile_height;

    std::pair<int, int> tile_picked;
};