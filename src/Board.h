#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class Board {
public:
    Board(int n, int different_tiles);
    ~Board();
    int** getBoard();
    int getBoardTiles();
    int getBoardFloors();
    int getBoardWidth();
    int getBoardHeight();
    int getBoardEmpty();
    int getBoardTilesNumber();

private:
    void clearBoard();
    int loadBoard(int n);

    int boardEmpty;
    int boardWidth;
    int boardHeight;
    int floors;
    int boardTiles;
    int tiles;
    bool** bFloor;
    int** iFloor;
};