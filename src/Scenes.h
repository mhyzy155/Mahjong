#include "Board.h"
#include "Button.h"
#include "Scene.h"

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

class SceneBoard : public Scene {
   public:
    SceneBoard(Graphics* gfx, const GameState& state);
    void draw();
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Graphics* graphics;
    Sprite* spr_bg;
    Sprite* spr_base;
    Sprite* spr_picked;
    std::vector<Sprite*> spr_tiles;
    int tile_offset;
    int tile_margin;
    float tile_scale;
    int tile_width;
    int tile_height;

    Board board;
    int tiles;
    std::vector<int> picked_tiles;
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