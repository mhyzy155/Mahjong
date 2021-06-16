#include "Scenes.h"

#include <algorithm>

#include "Colors.h"

// MenuMain
SceneMenuMain::SceneMenuMain(Graphics* gfx)
    : graphics{gfx},
      btn_newgame{new Button(new Text("New game", 50, Colors::green), Colors::beige, 20)},
      btn_exit{new Button(new Text("Exit", 50, Colors::red), Colors::beige, 20)} {}

void SceneMenuMain::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();
    btn_newgame->draw(window_width / 2, window_height / 2 - 60, renderer);
    btn_exit->draw(window_width / 2, window_height / 2 + 60, renderer);
}

std::unique_ptr<Scene> SceneMenuMain::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_newgame->getRect())) return std::unique_ptr<Scene>(new SceneMenuTileset(graphics));
    if (mouse->isPressed(btn_exit->getRect())) {
        state.running = false;
    }
    return nullptr;
}

// MenuTileset
SceneMenuTileset::SceneMenuTileset(Graphics* gfx) : graphics{gfx}, tilesets{3}, txt_tileset{new Text("Choose a tileset:", 70, Colors::green)} {
    for (int i = 1; i <= tilesets; i++) {
        std::string btnString = "tileset " + std::to_string(i);
        btns_tileset.push_back(std::make_unique<Button>(new Text(btnString, 50, Colors::green), Colors::beige, 20));
    }
}

void SceneMenuTileset::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();
    txt_tileset->draw(window_width / 2 - txt_tileset->getRect().w / 2, 100, renderer);
    for (int i = 0; i < tilesets; i++) {
        btns_tileset[i]->draw(window_width / 2, 300 + i * 150, renderer);
    }
}

std::unique_ptr<Scene> SceneMenuTileset::react(Mouse* mouse, GameState& state) {
    for (int i = 0; i < tilesets; i++) {
        if (mouse->isPressed(btns_tileset[i]->getRect())) {
            state.tileset_chosen = i + 1;
            return std::unique_ptr<Scene>(new SceneMenuMode(graphics));
        }
    }
    return nullptr;
}

// MenuMode
SceneMenuMode::SceneMenuMode(Graphics* gfx)
    : graphics{gfx},
      txt_mode{new Text("Choose a mode:", 70, Colors::green)},
      btn_original{new Button(new Text("Original", 50, Colors::green), Colors::beige, 20)},
      btn_simple{new Button(new Text("Simplified", 50, Colors::green), Colors::beige, 20)} {}

void SceneMenuMode::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();
    txt_mode->draw(window_width / 2 - txt_mode->getRect().w / 2, 100, renderer);
    btn_original->draw(window_width / 2, window_height / 2 - 60, renderer);
    btn_simple->draw(window_width / 2, window_height / 2 + 60, renderer);
}

std::unique_ptr<Scene> SceneMenuMode::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_original->getRect())) {
        state.mode_original = true;
        return std::unique_ptr<Scene>(new SceneMenuDifficulty(graphics));
    }
    if (mouse->isPressed(btn_simple->getRect())) {
        state.mode_original = false;
        return std::unique_ptr<Scene>(new SceneMenuDifficulty(graphics));
    }
    return nullptr;
}

// MenuDifficulty
SceneMenuDifficulty::SceneMenuDifficulty(Graphics* gfx)
    : graphics{gfx},
      txt_difficulty{new Text("Choose a difficulty:", 70, Colors::green)},
      btn_easy{new Button(new Text("Easy", 50, Colors::green), Colors::beige, 20)},
      btn_medium{new Button(new Text("Medium", 50, Colors::yellow), Colors::beige, 20)},
      btn_hard{new Button(new Text("Hard", 50, Colors::red), Colors::beige, 20)} {}

void SceneMenuDifficulty::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();
    txt_difficulty->draw(window_width / 2 - txt_difficulty->getRect().w / 2, 100, renderer);
    btn_easy->draw(window_width / 2, window_height / 2 - 100, renderer);
    btn_medium->draw(window_width / 2, window_height / 2, renderer);
    btn_hard->draw(window_width / 2, window_height / 2 + 100, renderer);
}

std::unique_ptr<Scene> SceneMenuDifficulty::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_easy->getRect())) {
        return std::unique_ptr<Scene>(new SceneBoard(graphics, state));
    }
    return nullptr;
}

SceneBoard::SceneBoard(Graphics* gfx, const GameState& state) : graphics{gfx}, tile_offset{8}, tile_margin{4}, tile_scale{1.0}, board{state.tileset_chosen, 9}, tiles{board.getBoardTilesNumber()} {
    auto filenames = std::list<std::string>{"background.jpg", "base.png", "pickedtile.png"};
    for (int i = 0; i < 9; i++) {
        filenames.push_back("new_tile" + std::to_string(i) + ".png");
    }
    auto sprites = graphics->loadSprites(filenames);

    spr_bg = sprites.front();
    sprites.pop_front();
    spr_base = sprites.front();
    sprites.pop_front();
    spr_picked = sprites.front();
    sprites.pop_front();
    spr_tiles = std::vector<Sprite*>(sprites.begin(), sprites.end());

    auto tile_rect = spr_tiles[0]->getRect();
    tile_width = tile_rect.w;
    tile_height = tile_rect.h;
}

void SceneBoard::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();
    spr_bg->draw((window_width - spr_bg->getRect().w) / 2, (window_height - spr_bg->getRect().h) / 2, renderer);

    int** board_tiles = board.getBoard();
    int board_empty = board.getBoardEmpty();
    int board_width = board.getBoardWidth();
    int board_height = board.getBoardHeight();
    int board_floors = board.getBoardFloors();

    for (int i = 0; i < board_floors; i++) {
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                int spriteindex = board_tiles[i][y * board_width + x];
                if (spriteindex != board_empty) {
                    spr_base->draw((window_width + tile_scale * spr_tiles[spriteindex]->getRect().w * (2 * x - board_width) - tile_margin * (board_width - 1)) / 2 + (i - 1) * tile_offset * tile_scale + x * tile_margin, (window_height + tile_scale * spr_tiles[spriteindex]->getRect().h * (2 * y - board_height) - tile_margin * (board_height - 1)) / 2 - i * tile_offset * tile_scale + y * tile_margin, tile_scale, renderer);
                }
            }
        }

        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                int spriteindex = board_tiles[i][y * board_width + x];
                if (spriteindex != board_empty) {
                    spr_tiles[spriteindex]->draw((window_width + tile_scale * spr_tiles[spriteindex]->getRect().w * (2 * x - board_width) - tile_margin * (board_width - 1)) / 2 + i * tile_offset * tile_scale + x * tile_margin, (window_height + tile_scale * spr_tiles[spriteindex]->getRect().h * (2 * y - board_height) - tile_margin * (board_height - 1)) / 2 - i * tile_offset * tile_scale + y * tile_margin, tile_scale, renderer);
                    for (const auto& elem : picked_tiles) {
                        if (elem == (y * board_width + x) && i == (board_floors - 1)) {
                            spr_picked->draw((window_width + tile_scale * spr_picked->getRect().w * (2 * x - board_width) - tile_margin * (board_width - 1)) / 2 + i * tile_offset * tile_scale + x * tile_margin, (window_height + tile_scale * spr_picked->getRect().h * (2 * y - board_height) - tile_margin * (board_height - 1)) / 2 - i * tile_offset * tile_scale + y * tile_margin, tile_scale, renderer);
                        } else if (elem == (y * board_width + x) && board_tiles[i + 1][y * board_width + x] == board_empty) {
                            spr_picked->draw((window_width + tile_scale * spr_picked->getRect().w * (2 * x - board_width) - tile_margin * (board_width - 1)) / 2 + i * tile_offset * tile_scale + x * tile_margin, (window_height + tile_scale * spr_picked->getRect().h * (2 * y - board_height) - tile_margin * (board_height - 1)) / 2 - i * tile_offset * tile_scale + y * tile_margin, tile_scale, renderer);
                        }
                    }
                }
            }
        }
    }
}

std::unique_ptr<Scene> SceneBoard::react(Mouse* mouse, GameState& state) {
    int tileXindex = -1;
    int tileYindex = -1;
    
    int mx;
    int my;
    mouse->getMouseState(mx, my);

    int** board_tiles = board.getBoard();
    int board_empty = board.getBoardEmpty();
    int board_width = board.getBoardWidth();
    int board_height = board.getBoardHeight();
    int board_floors = board.getBoardFloors();

    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    int i = board_floors - 1;
    bool tileFound = false;
    while (i >= 0 && !tileFound) {
        //printf("i: %d\n", i);
        float x = (float)board_width / 2.0f + (float)(mx - i * tile_offset * tile_scale) / (float)(tile_scale * tile_width + tile_margin) - (float)(window_width + tile_margin) / (float)(tile_scale * tile_width + tile_margin) / 2.0f;
        float x2 = (window_width + tile_scale * tile_width * (2 * (int)x - board_width) - tile_margin * (board_width - 1)) / 2 + i * tile_offset * tile_scale + (int)x * tile_margin + tile_width * tile_scale;
        float y = (float)board_height / 2.0f + (float)(my + i * tile_offset * tile_scale) / (float)(tile_scale * tile_height + tile_margin) - (float)(window_height + tile_margin) / (float)(tile_scale * tile_height + tile_margin) / 2.0f;
        float y2 = (window_height + tile_scale * tile_height * (2 * (int)y - board_height) - tile_margin * (board_height - 1)) / 2 - i * tile_offset * tile_scale + (int)y * tile_margin + tile_height * tile_scale;
        //printf("y1: %f, y2: %f, my: %d, delta: %f\n", y, y2, my, (y2 - my));

        if (x >= 0 && x < board_width && (x2 - mx) > 0 && y >= 0 && y < board_height && (y2 - my) > 0 && board_tiles[i][(int)y * board_width + (int)x] != board_empty) {
            if (i == (board_floors - 1) && board_tiles[i][(int)y * board_width + (int)x] != board_empty) {
                tileFound = true;
                tileXindex = (int)x;
                tileYindex = (int)y;
                //printf("x: %d, y: %d, floor: %d\n", (int)x, (int)y, i);
            } else if (board_tiles[i][(int)y * board_width + (int)x] != board_empty && board_tiles[i + 1][(int)y * board_width + (int)x] == board_empty) {
                tileFound = true;
                tileXindex = (int)x;
                tileYindex = (int)y;
                //printf("x: %d, y: %d, floor: %d\n", (int)x, (int)y, i);
            }
        }

        if (!tileFound) i--;
    }
    //printf("\n\n");

    //one tile selected
    if (tileXindex >= 0 && tileYindex >= 0 && picked_tiles.size() == 1) {
        int i = board_floors - 1;
        while (i >= 0) {
            if (board_tiles[i][picked_tiles[0]] == board_empty) {
                i--;
            } else
                break;
        }
        int index1 = i;

        i = board_floors - 1;
        while (i >= 0) {
            if (board_tiles[i][tileYindex * board_width + tileXindex] == board_empty) {
                i--;
            } else
                break;
        }
        int index2 = i;

        if (picked_tiles[0] != (tileYindex * board_width + tileXindex) && board_tiles[index1][picked_tiles[0]] == board_tiles[index2][tileYindex * board_width + tileXindex]) {
            if (state.mode_original) {
                if ((tileXindex == 0 || tileXindex == board_width - 1) || (board_tiles[i][tileYindex * board_width + tileXindex - 1] == board_empty || board_tiles[i][tileYindex * board_width + tileXindex + 1] == board_empty)) {
                    board_tiles[index1][picked_tiles[0]] = board_empty;
                    board_tiles[index2][tileYindex * board_width + tileXindex] = board_empty;
                    picked_tiles.clear();
                    tiles -= 2;
                    if (tiles <= 0) return std::unique_ptr<Scene>(new SceneWin(graphics));
                }
            } else {
                board_tiles[index1][picked_tiles[0]] = board_empty;
                board_tiles[index2][tileYindex * board_width + tileXindex] = board_empty;
                picked_tiles.clear();
                tiles -= 2;
                if (tiles <= 0) return std::unique_ptr<Scene>(new SceneWin(graphics));
            }
        } else if (picked_tiles[0] != (tileYindex * board_width + tileXindex)) {
            if (state.mode_original) {
                if ((tileXindex == 0 || tileXindex == board_width - 1) || (board_tiles[i][tileYindex * board_width + tileXindex - 1] == board_empty || board_tiles[i][tileYindex * board_width + tileXindex + 1] == board_empty)) {
                    picked_tiles.clear();
                    picked_tiles.push_back(tileYindex * board_width + tileXindex);
                }
            } else {
                picked_tiles.clear();
                picked_tiles.push_back(tileYindex * board_width + tileXindex);
            }
        }
    } else if (tileXindex >= 0 && tileYindex >= 0) {
        if (state.mode_original) {
            int i = board_floors - 1;
            while (i >= 0) {
                if (board_tiles[i][tileYindex * board_width + tileXindex] == board_empty) {
                    i--;
                } else
                    break;
            }
            if ((tileXindex == 0 || tileXindex == board_width - 1) || (board_tiles[i][tileYindex * board_width + tileXindex - 1] == board_empty || board_tiles[i][tileYindex * board_width + tileXindex + 1] == board_empty)) {
                picked_tiles.clear();
                picked_tiles.push_back(tileYindex * board_width + tileXindex);
            }
        } else {
            picked_tiles.clear();
            picked_tiles.push_back(tileYindex * board_width + tileXindex);
        }
    }
    return nullptr;
}

SceneWin::SceneWin(Graphics* gfx)
    : graphics{gfx},
      txt_win{new Text("You won!", 100, Colors::white)},
      btn_again{new Button(new Text("Play again", 50, Colors::green), Colors::beige, 20)},
      btn_exit{new Button(new Text("Exit", 50, Colors::red), Colors::beige, 20)} {
    auto filenames = std::list<std::string>{"background.jpg"};
    auto sprites = graphics->loadSprites(filenames);
    spr_bg = sprites.front();
}

void SceneWin::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();
    spr_bg->draw((window_width - spr_bg->getRect().w) / 2, (window_height - spr_bg->getRect().h) / 2, renderer);
    txt_win->draw((window_width - txt_win->getRect().w) / 2, (window_height - txt_win->getRect().h) / 2, renderer);
    btn_again->draw(window_width / 2, window_height / 2 + 150, renderer);
    btn_exit->draw(window_width / 2, window_height / 2 + 250, renderer);
}

std::unique_ptr<Scene> SceneWin::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_again->getRect())) return std::unique_ptr<Scene>(new SceneMenuTileset(graphics));
    if (mouse->isPressed(btn_exit->getRect())) state.running = false;
    return nullptr;
}