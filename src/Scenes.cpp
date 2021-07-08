#include "Scenes.h"

#include <algorithm>

#include "Colors.h"

// Dummy Scene
SceneDummy::SceneDummy(Graphics* gfx) {}

void SceneDummy::draw() {}

std::unique_ptr<Scene> SceneDummy::react(Mouse* mouse, GameState& state) { return std::unique_ptr<Scene>(new SceneDummy()); }

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

// Quick Menu Overlay
OverlayMenuQuick::OverlayMenuQuick(Graphics* gfx)
    : graphics{gfx},
      btn_resume{new Button(new Text("Resume", 50, Colors::green), Colors::beige, 20)},
      btn_settings{new Button(new Text("Settings", 50, Colors::green), Colors::beige, 20)},
      btn_exit{new Button(new Text("Exit", 50, Colors::red), Colors::beige, 20)} {}

void OverlayMenuQuick::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();
    btn_resume->draw(window_width / 2, window_height / 2 - 100, renderer);
    btn_settings->draw(window_width / 2, window_height / 2, renderer);
    btn_exit->draw(window_width / 2, window_height / 2 + 100, renderer);
}

std::unique_ptr<Scene> OverlayMenuQuick::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_resume->getRect())) {
        return std::unique_ptr<Scene>(new SceneDummy());
    } else if (mouse->isPressed(btn_settings->getRect())) {
        return std::unique_ptr<Scene>(new OverlaySettings(graphics, state));
    } else if (mouse->isPressed(btn_exit->getRect())) {
        state.running = false;
        return nullptr;
    }
    return nullptr;
}

// Settings Overlay
OverlaySettings::OverlaySettings(Graphics* gfx, const GameState& state)
    : graphics{gfx},
      txt_texturepack{new Text("Texture pack:", 50, Colors::green)},
      btn_texturepack{new ButtonSwitch({std::string{"default"}, std::string{"alternative"}}, 50, Colors::green, Colors::beige, 20, state.texturepack)},
      btn_return{new Button(new Text("Return", 50, Colors::green), Colors::beige, 20)} {}

void OverlaySettings::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();
    txt_texturepack->draw((window_width - txt_texturepack->getRect().w) / 2, window_height / 2 - 50, renderer);
    btn_texturepack->draw((window_width + btn_texturepack->getRect().w) / 2, window_height / 2, renderer);
    btn_return->draw(window_width / 2, window_height / 2 + 100, renderer);
}

std::unique_ptr<Scene> OverlaySettings::react(Mouse* mouse, GameState& state) {
    if (mouse->isPressed(btn_texturepack->getRect())) {
        state.texturepack = btn_texturepack->changeState();
        graphics->changeTexturepack(state.texturepack);
        return nullptr;
    } else if (mouse->isPressed(btn_return->getRect())) {
        return std::unique_ptr<Scene>(new OverlayMenuQuick(graphics));
    }
    return nullptr;
}

// Board
SceneBoard::SceneBoard(Graphics* gfx, const GameState& state)
    : graphics{gfx}, spr_bg{graphics->loadSprites(std::list<std::string>{"background.jpg"}, true).front()}, board{graphics, state.tileset_chosen, state.mode_original}, btn_overlay{new Button(new Text(".", 20, Colors::green), Colors::beige, 20)}, overlay{nullptr} {}

void SceneBoard::draw() {
    auto window_width = graphics->getWindowWidth();
    auto window_height = graphics->getWindowHeight();
    auto renderer = graphics->getRenderer();
    spr_bg->draw((window_width - spr_bg->getRect().w) / 2, (window_height - spr_bg->getRect().h) / 2, renderer);
    board.draw();
    btn_overlay->draw(0, 0, renderer);
    if (overlay) overlay->draw();
}

std::unique_ptr<Scene> SceneBoard::react(Mouse* mouse, GameState& state) {
    if (overlay) {
        auto overlay_new = overlay->react(mouse, state);
        if (overlay_new) {
            if (dynamic_cast<SceneDummy*>(overlay_new.get())) {
                overlay = nullptr;
            } else {
                overlay.swap(overlay_new);
            }
        }
        return nullptr;
    }

    if (mouse->isPressed(btn_overlay->getRect())) {
        overlay = std::unique_ptr<Scene>(new OverlayMenuQuick(graphics));
        return nullptr;
    }
    int mx;
    int my;
    mouse->getMouseState(mx, my);
    if (board.react(mx, my)) return std::unique_ptr<Scene>(new SceneWin(graphics));
    return nullptr;
}

// Win
SceneWin::SceneWin(Graphics* gfx)
    : graphics{gfx},
      txt_win{new Text("You won!", 100, Colors::white)},
      btn_again{new Button(new Text("Play again", 50, Colors::green), Colors::beige, 20)},
      btn_exit{new Button(new Text("Exit", 50, Colors::red), Colors::beige, 20)} {
    auto filenames = std::list<std::string>{"background.jpg"};
    auto sprites = graphics->loadSprites(filenames, true);
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