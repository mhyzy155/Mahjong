#include "Scenes.h"

#include "Colors.h"

// MenuMain
SceneMenuMain::SceneMenuMain()
    : btn_newgame{new Button(new Text("New game", 50, Colors::green), Colors::beige, 20)},
      btn_exit{new Button(new Text("Exit", 50, Colors::red), Colors::beige, 20)} {}

void SceneMenuMain::draw(Graphics* graphics) {
    btn_newgame->draw(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2 - 60, graphics->getRenderer());
    btn_exit->draw(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2 + 60, graphics->getRenderer());
}

std::unique_ptr<Scene> SceneMenuMain::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_newgame->getRect())) return std::unique_ptr<Scene>(new SceneMenuTileset());
    if (mouse->isPressed(btn_exit->getRect())) {
        state.running = false;
    }
    return nullptr;
}

// MenuTileset
SceneMenuTileset::SceneMenuTileset() : tilesets{3}, txt_tileset{new Text("Choose a tileset:", 70, Colors::green)} {
    for (int i = 1; i <= tilesets; i++) {
        std::string btnString = "tileset " + std::to_string(i);
        btns_tileset.push_back(std::make_unique<Button>(new Text(btnString, 50, Colors::green), Colors::beige, 20));
    }
}

void SceneMenuTileset::draw(Graphics* graphics) {
    txt_tileset->draw(graphics->getWindowWidth() / 2 - txt_tileset->getRect().w / 2, 100, graphics->getRenderer());
    for (int i = 0; i < tilesets; i++) {
        btns_tileset[i]->draw(graphics->getWindowWidth() / 2, 300 + i * 150, graphics->getRenderer());
    }
}

std::unique_ptr<Scene> SceneMenuTileset::react(Mouse* mouse, GameState& state) {
    for (int i = 0; i < tilesets; i++) {
        if (mouse->isPressed(btns_tileset[i]->getRect())) {
            state.tileset_chosen = i + 1;
            return std::unique_ptr<Scene>(new SceneMenuMode());
        }
    }
    return nullptr;
}

// MenuMode
SceneMenuMode::SceneMenuMode()
    : txt_mode{new Text("Choose a mode:", 70, Colors::green)},
      btn_original{new Button(new Text("Original", 50, Colors::green), Colors::beige, 20)},
      btn_simple{new Button(new Text("Simplified", 50, Colors::green), Colors::beige, 20)} {}

void SceneMenuMode::draw(Graphics* graphics) {
    txt_mode->draw(graphics->getWindowWidth() / 2 - txt_mode->getRect().w / 2, 100, graphics->getRenderer());
    btn_original->draw(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2 - 60, graphics->getRenderer());
    btn_simple->draw(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2 + 60, graphics->getRenderer());
}

std::unique_ptr<Scene> SceneMenuMode::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_original->getRect())) {
        state.mode_original = true;
        return std::unique_ptr<Scene>(new SceneMenuDifficulty());
    }
    if (mouse->isPressed(btn_simple->getRect())) {
        state.mode_original = false;
        return std::unique_ptr<Scene>(new SceneMenuDifficulty());
    }
    return nullptr;
}

// MenuDifficulty
SceneMenuDifficulty::SceneMenuDifficulty()
    : txt_difficulty{new Text("Choose a difficulty:", 70, Colors::green)},
      btn_easy{new Button(new Text("Easy", 50, Colors::green), Colors::beige, 20)},
      btn_medium{new Button(new Text("Medium", 50, Colors::yellow), Colors::beige, 20)},
      btn_hard{new Button(new Text("Hard", 50, Colors::red), Colors::beige, 20)} {}

void SceneMenuDifficulty::draw(Graphics* graphics) {
    txt_difficulty->draw(graphics->getWindowWidth() / 2 - txt_difficulty->getRect().w / 2, 100, graphics->getRenderer());
    btn_easy->draw(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2 - 100, graphics->getRenderer());
    btn_medium->draw(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2, graphics->getRenderer());
    btn_hard->draw(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2 + 100, graphics->getRenderer());
}

std::unique_ptr<Scene> SceneMenuDifficulty::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_easy->getRect())) {
        return std::unique_ptr<Scene>(new SceneBoard(state));
    }
    return nullptr;
}

SceneBoard::SceneBoard(const GameState& state) : board{state.tileset_chosen, 9}, tiles{board.getBoardTilesNumber()} {}

void SceneBoard::draw(Graphics* graphics) {
    gfx = graphics;
    graphics->grabPickedTiles(picked_tiles);
    graphics->DrawBoardSprites(&board);
}

std::unique_ptr<Scene> SceneBoard::react(Mouse* mouse, GameState& state) {
    mouse->buttonDown(gfx, &board, tileXindex, tileYindex);
    int** boardTiles = board.getBoard();
    int empty = board.getBoardEmpty();

    //one tile selected
    if (tileXindex >= 0 && tileYindex >= 0 && picked_tiles.size() == 1) {
        int i = board.getBoardFloors() - 1;
        while (i >= 0) {
            if (boardTiles[i][picked_tiles[0]] == empty) {
                i--;
            } else
                break;
        }
        int index1 = i;

        i = board.getBoardFloors() - 1;
        while (i >= 0) {
            if (boardTiles[i][tileYindex * board.getBoardWidth() + tileXindex] == empty) {
                i--;
            } else
                break;
        }
        int index2 = i;

        if (picked_tiles[0] != (tileYindex * board.getBoardWidth() + tileXindex) && boardTiles[index1][picked_tiles[0]] == boardTiles[index2][tileYindex * board.getBoardWidth() + tileXindex]) {
            if (state.mode_original) {
                if ((tileXindex == 0 || tileXindex == board.getBoardWidth() - 1) || (boardTiles[i][tileYindex * board.getBoardWidth() + tileXindex - 1] == empty || boardTiles[i][tileYindex * board.getBoardWidth() + tileXindex + 1] == empty)) {
                    boardTiles[index1][picked_tiles[0]] = board.getBoardEmpty();
                    boardTiles[index2][tileYindex * board.getBoardWidth() + tileXindex] = board.getBoardEmpty();
                    picked_tiles.clear();
                    tiles -= 2;
                    if (tiles <= 0) return std::unique_ptr<Scene>(new SceneWin());
                }
            } else {
                boardTiles[index1][picked_tiles[0]] = board.getBoardEmpty();
                boardTiles[index2][tileYindex * board.getBoardWidth() + tileXindex] = board.getBoardEmpty();
                picked_tiles.clear();
                tiles -= 2;
                if (tiles <= 0) return std::unique_ptr<Scene>(new SceneWin());
            }
        } else if (picked_tiles[0] != (tileYindex * board.getBoardWidth() + tileXindex)) {
            if (state.mode_original) {
                if ((tileXindex == 0 || tileXindex == board.getBoardWidth() - 1) || (boardTiles[i][tileYindex * board.getBoardWidth() + tileXindex - 1] == empty || boardTiles[i][tileYindex * board.getBoardWidth() + tileXindex + 1] == empty)) {
                    picked_tiles.clear();
                    picked_tiles.push_back(tileYindex * board.getBoardWidth() + tileXindex);
                }
            } else {
                picked_tiles.clear();
                picked_tiles.push_back(tileYindex * board.getBoardWidth() + tileXindex);
            }
        }
    } else if (tileXindex >= 0 && tileYindex >= 0) {
        if (state.mode_original) {
            int i = board.getBoardFloors() - 1;
            while (i >= 0) {
                if (boardTiles[i][tileYindex * board.getBoardWidth() + tileXindex] == empty) {
                    i--;
                } else
                    break;
            }
            if ((tileXindex == 0 || tileXindex == board.getBoardWidth() - 1) || (boardTiles[i][tileYindex * board.getBoardWidth() + tileXindex - 1] == empty || boardTiles[i][tileYindex * board.getBoardWidth() + tileXindex + 1] == empty)) {
                picked_tiles.clear();
                picked_tiles.push_back(tileYindex * board.getBoardWidth() + tileXindex);
            }
        } else {
            picked_tiles.clear();
            picked_tiles.push_back(tileYindex * board.getBoardWidth() + tileXindex);
        }
    }
    return nullptr;
}

SceneWin::SceneWin()
    : txt_win{new Text("You won!", 100, Colors::white)},
      btn_again{new Button(new Text("Play again", 50, Colors::green), Colors::beige, 20)},
      btn_exit{new Button(new Text("Exit", 50, Colors::red), Colors::beige, 20)} {}

void SceneWin::draw(Graphics* graphics) {
    graphics->DrawBG();
    txt_win->draw((graphics->getWindowWidth() - txt_win->getRect().w) / 2, (graphics->getWindowHeight() - txt_win->getRect().h) / 2, graphics->getRenderer());
    btn_again->draw(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2 + 150, graphics->getRenderer());
    btn_exit->draw(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2 + 250, graphics->getRenderer());
}

std::unique_ptr<Scene> SceneWin::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_again->getRect())) return std::unique_ptr<Scene>(new SceneMenuTileset());
    if (mouse->isPressed(btn_exit->getRect())) state.running = false;
    return nullptr;
}