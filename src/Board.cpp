#include "Board.h"

Board::Board(int n) {
    loadBoard(n);
    clearBoard();

    int tilecounter = tiles;
    while (tilecounter > 0) {
        int tileindex = rand() % boardTiles;
        int paircounter = 0;
        while (paircounter < 2) {
            int boardindex = rand() % (boardHeight * boardWidth);
            int floor = rand() % floors;
            if (floor == 0) {
                if (bFloor[0][boardindex] == true && iFloor[0][boardindex] == boardEmpty) {
                    iFloor[0][boardindex] = tileindex;
                    paircounter++;
                    tilecounter--;
                }
            } else {
                if (bFloor[floor][boardindex] == true && iFloor[floor][boardindex] == boardEmpty && iFloor[floor - 1][boardindex] != boardEmpty) {
                    iFloor[floor][boardindex] = tileindex;
                    paircounter++;
                    tilecounter--;
                }
            }
        }
    }

    /*for (int i = 0; i < floors; i++) {
		for (int y = 0; y < boardHeight; y++) {
			for (int x = 0; x < boardWidth; x++) {
				printf("%d ", iFloor[i][y*boardWidth + x]);
			}
			printf("\n");
		}
		printf("\n\n");
	}*/
}

Board::Board(int n, int different_tiles) {
    boardTiles = different_tiles;
    loadBoard(n);
    clearBoard();

    int tilecounter = tiles;
    while (tilecounter > 0) {
        int tileindex = rand() % boardTiles;
        int paircounter = 0;
        while (paircounter < 2) {
            int boardindex = rand() % (boardHeight * boardWidth);
            int floor = rand() % floors;
            if (floor == 0) {
                if (bFloor[0][boardindex] == true && iFloor[0][boardindex] == boardEmpty) {
                    iFloor[0][boardindex] = tileindex;
                    paircounter++;
                    tilecounter--;
                }
            } else {
                if (bFloor[floor][boardindex] == true && iFloor[floor][boardindex] == boardEmpty && iFloor[floor - 1][boardindex] != boardEmpty) {
                    iFloor[floor][boardindex] = tileindex;
                    paircounter++;
                    tilecounter--;
                }
            }
        }
    }
}

Board::~Board() {
    for (int i = 0; i < floors; i++) {
        delete[] bFloor[i];
    }
    delete[] bFloor;

    for (int i = 0; i < floors; i++) {
        delete[] iFloor[i];
    }
    delete[] iFloor;
}

int **Board::getBoard() {
    return iFloor;
}

int Board::getBoardTiles() {
    return boardTiles;
}

int Board::getBoardFloors() {
    return floors;
}

int Board::getBoardWidth() {
    return boardWidth;
}

int Board::getBoardHeight() {
    return boardHeight;
}

int Board::getBoardEmpty() {
    return boardEmpty;
}

int Board::getBoardTilesNumber() {
    return tiles;
}

void Board::clearBoard() {
    if (iFloor == nullptr) {
        iFloor = new int *[floors];
        for (int i = 0; i < floors; i++) {
            iFloor[i] = new int[boardWidth * boardHeight];
            for (int y = 0; y < boardHeight; y++) {
                for (int x = 0; x < boardWidth; x++) {
                    iFloor[i][y * boardWidth + x] = boardEmpty;
                }
            }
        }
    }
}

int Board::loadBoard(int n) {
    int err;
    std::string file_number = std::to_string(n);
    std::string file_path = "../assets/tilesets/tileset" + file_number + ".txt";
    FILE *pFile = fopen(file_path.c_str(), "r");
    if (pFile == NULL) {
        printf("Opening tileset error");
        return -1;
    }

    if (pFile) {
        int scanner;
        fscanf(pFile, "%d", &scanner);
        boardWidth = scanner;
        fscanf(pFile, "%d", &scanner);
        boardHeight = scanner;
        fscanf(pFile, "%d", &scanner);
        floors = scanner;

        if (bFloor == nullptr) {
            bFloor = new bool *[floors];
            for (int i = 0; i < floors; i++) {
                bFloor[i] = new bool[boardWidth * boardHeight];
            }
        }

        int floorcounter = 0;
        int tilescounter = 0;
        while (!feof(pFile) && floorcounter < floors) {
            for (int j = 0; j < boardWidth * boardHeight; j++) {
                fscanf(pFile, "%d", &scanner);
                if (scanner == 1) {
                    bFloor[floorcounter][j] = true;
                    tilescounter++;
                } else {
                    bFloor[floorcounter][j] = false;
                }
            }
            floorcounter++;
        }
        tiles = tilescounter;
    }

    err = fclose(pFile);

    return 0;
}
