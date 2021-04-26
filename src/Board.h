#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class Board {
public:
    Board(int n);
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

    int boardEmpty = 64;
    int boardTiles = 1;
    int boardWidth = 8;
    int boardHeight = 10;
    int floors = 3;
    int tiles;
    bool** bFloor = nullptr;
    int** iFloor = nullptr;
};