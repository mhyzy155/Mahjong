#include "Board.h"
#include "ButtonSwitch.h"
#include "Scene.h"

class SceneDummy : public Scene {
    public:
    SceneDummy(Graphics* gfx = nullptr);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);
};

class SceneMenuMain : public Scene {
   public:
    SceneMenuMain(Graphics* gfx);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Graphics* graphics;
    std::unique_ptr<Button> btn_newgame;
    std::unique_ptr<Button> btn_exit;
};

class SceneMenuTileset : public Scene {
   public:
    SceneMenuTileset(Graphics* gfx);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Graphics* graphics;
    int tilesets;
    std::unique_ptr<Text> txt_tileset;
    std::vector<std::unique_ptr<Button>> btns_tileset;
};

class SceneMenuMode : public Scene {
   public:
    SceneMenuMode(Graphics* gfx);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Graphics* graphics;
    std::unique_ptr<Text> txt_mode;
    std::unique_ptr<Button> btn_original;
    std::unique_ptr<Button> btn_simple;
};

class SceneMenuDifficulty : public Scene {
   public:
    SceneMenuDifficulty(Graphics* gfx);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Graphics* graphics;
    std::unique_ptr<Text> txt_difficulty;
    std::unique_ptr<Button> btn_easy;
    std::unique_ptr<Button> btn_medium;
    std::unique_ptr<Button> btn_hard;
};

class OverlayMenuQuick : public Scene {
   public:
    OverlayMenuQuick(Graphics* gfx);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Graphics* graphics;
    std::unique_ptr<Button> btn_resume;
    std::unique_ptr<Button> btn_settings;
    std::unique_ptr<Button> btn_exit;
};

class OverlaySettings : public Scene {
   public:
    OverlaySettings(Graphics* gfx, const GameState& state);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Graphics* graphics;
    std::unique_ptr<Text> txt_texturepack;
    std::unique_ptr<ButtonSwitch> btn_texturepack;
    std::unique_ptr<Button> btn_return;
};

class SceneBoard : public Scene {
   public:
    SceneBoard(Graphics* gfx, const GameState& state);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Graphics* graphics;
    Sprite* spr_bg;
    Board board;
    std::unique_ptr<Button> btn_overlay;
    std::unique_ptr<Scene> overlay;
};

class SceneWin : public Scene {
   public:
    SceneWin(Graphics* gfx);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Graphics* graphics;
    Sprite* spr_bg;
    std::unique_ptr<Text> txt_win;
    std::unique_ptr<Button> btn_again;
    std::unique_ptr<Button> btn_exit;
};