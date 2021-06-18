#include "Board.h"

Board::Board(Graphics *gfx, int tileset, bool mode_original, int different_tiles)
    : mode_original{mode_original}, board_empty{64}, board_width{8}, board_height{10}, board_floors{3}, board_tiles{different_tiles}, bFloor{nullptr}, iFloor{nullptr}, graphics{gfx}, spr_base{nullptr}, spr_picked{nullptr}, tile_offset{8}, tile_margin{4}, tile_scale{1.0}, tile_picked{std::make_pair(-1, 0)} {
    auto filenames = std::list<std::string>{"base.png", "pickedtile.png"};
    for (int i = 0; i < board_tiles; i++) {
        filenames.push_back("new_tile" + std::to_string(i) + ".png");
    }
    auto sprites = graphics->loadSprites(filenames);

    spr_base = sprites.front();
    sprites.pop_front();
    spr_picked = sprites.front();
    sprites.pop_front();
    spr_tiles = std::vector<Sprite *>(sprites.begin(), sprites.end());

    auto tile_rect = spr_tiles[0]->getRect();
    tile_width = tile_rect.w;
    tile_height = tile_rect.h;

    loadBoard(tileset);
    clearBoard();
    fillBoard();
}

Board::~Board() {
    for (int i = 0; i < board_floors; i++) {
        delete[] bFloor[i];
    }
    delete[] bFloor;

    for (int i = 0; i < board_floors; i++) {
        delete[] iFloor[i];
    }
    delete[] iFloor;
}

void Board::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();

    for (int i = 0; i < board_floors; i++) {
        // Draw tile bases
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                int spriteindex = iFloor[i][y * board_width + x];
                if (spriteindex != board_empty) {
                    spr_base->draw((window_width + tile_scale * spr_tiles[spriteindex]->getRect().w * (2 * x - board_width) - tile_margin * (board_width - 1)) / 2 + (i - 1) * tile_offset * tile_scale + x * tile_margin, (window_height + tile_scale * spr_tiles[spriteindex]->getRect().h * (2 * y - board_height) - tile_margin * (board_height - 1)) / 2 - i * tile_offset * tile_scale + y * tile_margin, tile_scale, renderer);
                }
            }
        }

        // Draw tile faces
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                int spriteindex = iFloor[i][y * board_width + x];
                if (spriteindex != board_empty) {
                    spr_tiles[spriteindex]->draw((window_width + tile_scale * spr_tiles[spriteindex]->getRect().w * (2 * x - board_width) - tile_margin * (board_width - 1)) / 2 + i * tile_offset * tile_scale + x * tile_margin, (window_height + tile_scale * spr_tiles[spriteindex]->getRect().h * (2 * y - board_height) - tile_margin * (board_height - 1)) / 2 - i * tile_offset * tile_scale + y * tile_margin, tile_scale, renderer);
                }
            }
        }

        // Draw picked tile
        if (tile_picked.first == i) {
            if (i == (board_floors - 1) || iFloor[i + 1][tile_picked.second] == board_empty) {
                int tile_picked_x = tile_picked.second % board_width;
                int tile_picked_y = tile_picked.second / board_width;
                spr_picked->draw((window_width + tile_scale * spr_picked->getRect().w * (2 * tile_picked_x - board_width) - tile_margin * (board_width - 1)) / 2 + i * tile_offset * tile_scale + tile_picked_x * tile_margin, (window_height + tile_scale * spr_picked->getRect().h * (2 * tile_picked_y - board_height) - tile_margin * (board_height - 1)) / 2 - i * tile_offset * tile_scale + tile_picked_y * tile_margin, tile_scale, renderer);
            }
        }
    }
}

bool Board::react(int mx, int my) {
    int tileXindex = -1;
    int tileYindex = -1;

    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();

    float ax1 = 0.5f * board_width + (mx - 0.5f * (window_width + tile_margin)) / (tile_scale * tile_width + tile_margin);
    float bx1 = tile_scale * tile_offset / (tile_scale * tile_width + tile_margin);
    float ax2 = 0.5f * (window_width - tile_margin * (board_width - 1)) + tile_scale * tile_width;

    float ay1 = 0.5f * board_height + (my - 0.5f * (window_height + tile_margin)) / (tile_scale * tile_height + tile_margin);
    float by1 = tile_scale * tile_offset / (tile_scale * tile_height + tile_margin);
    float ay2 = 0.5f * (window_height - tile_margin * (board_height - 1)) + tile_scale * tile_height;

    int i = board_floors - 1;
    bool tileFound = false;
    while (i >= 0 && !tileFound) {
        //printf("i: %d\n", i);
        float ai = i * tile_scale * tile_offset;
        float x1 = ax1 - i * bx1;
        int x1_int = x1;
        float x2 = ax2 + 0.5f * tile_scale * tile_width * (2 * x1_int - board_width) + x1_int * tile_margin + ai;
        float y1 = ay1 + i * by1;
        int y1_int = y1;
        float y2 = ay2 + 0.5f * tile_scale * tile_height * (2 * y1_int - board_height) + y1_int * tile_margin - ai;

        if (x1 >= 0 && x1 < board_width && (x2 - mx) > 0 && y1 >= 0 && y1 < board_height && (y2 - my) > 0 && iFloor[i][y1_int * board_width + x1_int] != board_empty) {
            if (i == (board_floors - 1) || iFloor[i + 1][y1_int * board_width + x1_int] == board_empty) {
                tileFound = true;
                tileXindex = x1_int;
                tileYindex = y1_int;
            }
        }

        if (!tileFound) i--;
    }

    int index2 = i;
    int pos2 = tileYindex * board_width + tileXindex;

    if (tileXindex >= 0 && tileYindex >= 0 && tile_picked.first >= 0) {  // 1 tile selected
        if (tile_picked.second != pos2 && iFloor[tile_picked.first][tile_picked.second] == iFloor[index2][pos2]) {
            if (mode_original) {
                if ((tileXindex == 0 || tileXindex == board_width - 1) || (iFloor[index2][pos2 - 1] == board_empty || iFloor[index2][pos2 + 1] == board_empty)) {
                    iFloor[tile_picked.first][tile_picked.second] = board_empty;
                    iFloor[index2][pos2] = board_empty;
                    tile_picked.first = -1;
                    tiles_left -= 2;
                    if (tiles_left <= 0) return true;
                }
            } else {
                iFloor[tile_picked.first][tile_picked.second] = board_empty;
                iFloor[index2][pos2] = board_empty;
                tile_picked.first = -1;
                tiles_left -= 2;
                if (tiles_left <= 0) return true;
            }
        } else if (tile_picked.second != pos2) {
            if (mode_original) {
                if ((tileXindex == 0 || tileXindex == board_width - 1) || (iFloor[index2][pos2 - 1] == board_empty || iFloor[index2][pos2 + 1] == board_empty)) {
                    tile_picked = std::make_pair(index2, pos2);
                }
            } else {
                tile_picked = std::make_pair(index2, pos2);
            }
        }
    } else if (tileXindex >= 0 && tileYindex >= 0) {  // 0 tiles selected
        if (mode_original) {
            if ((tileXindex == 0 || tileXindex == board_width - 1) || (iFloor[index2][pos2 - 1] == board_empty || iFloor[index2][pos2 + 1] == board_empty)) {
                tile_picked = std::make_pair(index2, pos2);
            }
        } else {
            tile_picked = std::make_pair(index2, pos2);
        }
    }
    return false;
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
        board_width = scanner;
        fscanf(pFile, "%d", &scanner);
        board_height = scanner;
        fscanf(pFile, "%d", &scanner);
        board_floors = scanner;

        if (bFloor == nullptr) {
            bFloor = new bool *[board_floors];
            for (int i = 0; i < board_floors; i++) {
                bFloor[i] = new bool[board_width * board_height];
            }
        }

        int floorcounter = 0;
        int tilescounter = 0;
        while (!feof(pFile) && floorcounter < board_floors) {
            for (int j = 0; j < board_width * board_height; j++) {
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
        tiles_left = tilescounter;
    }

    err = fclose(pFile);

    return 0;
}

void Board::clearBoard() {
    if (!iFloor) {
        iFloor = new int *[board_floors];
        for (int i = 0; i < board_floors; i++) {
            iFloor[i] = new int[board_width * board_height];
            for (int y = 0; y < board_height; y++) {
                for (int x = 0; x < board_width; x++) {
                    iFloor[i][y * board_width + x] = board_empty;
                }
            }
        }
    }
}

void Board::fillBoard() {
    int tilecounter = tiles_left;
    while (tilecounter > 0) {
        int tileindex = rand() % board_tiles;
        int paircounter = 0;
        while (paircounter < 2) {
            int boardindex = rand() % (board_height * board_width);
            int floor = rand() % board_floors;
            if (floor == 0) {
                if (bFloor[0][boardindex] == true && iFloor[0][boardindex] == board_empty) {
                    iFloor[0][boardindex] = tileindex;
                    paircounter++;
                    tilecounter--;
                }
            } else {
                if (bFloor[floor][boardindex] == true && iFloor[floor][boardindex] == board_empty && iFloor[floor - 1][boardindex] != board_empty) {
                    iFloor[floor][boardindex] = tileindex;
                    paircounter++;
                    tilecounter--;
                }
            }
        }
    }
}