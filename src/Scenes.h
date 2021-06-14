#include "Board.h"
#include "Button.h"
#include "Scene.h"

class SceneMenuMain : public Scene {
   public:
    SceneMenuMain();
    void draw(Graphics* graphics);
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    std::unique_ptr<Button> btn_newgame;
    std::unique_ptr<Button> btn_exit;
};

class SceneMenuTileset : public Scene {
   public:
    SceneMenuTileset();
    void draw(Graphics* graphics);
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    int tilesets;
    std::unique_ptr<Text> txt_tileset;
    std::vector<std::unique_ptr<Button>> btns_tileset;
};

class SceneMenuMode : public Scene {
   public:
    SceneMenuMode();
    void draw(Graphics* graphics);
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    std::unique_ptr<Text> txt_mode;
    std::unique_ptr<Button> btn_original;
    std::unique_ptr<Button> btn_simple;
};

class SceneMenuDifficulty : public Scene {
   public:
    SceneMenuDifficulty();
    void draw(Graphics* graphics);
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    std::unique_ptr<Text> txt_difficulty;
    std::unique_ptr<Button> btn_easy;
    std::unique_ptr<Button> btn_medium;
    std::unique_ptr<Button> btn_hard;
};

class SceneBoard : public Scene {
   public:
    SceneBoard(const GameState& state);
    void draw(Graphics* graphics);
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    Board board;
    int tiles;
    std::vector<int> picked_tiles;
    int tileXindex;
    int tileYindex;
    Graphics* gfx;
};

class SceneWin : public Scene {
   public:
    SceneWin();
    void draw(Graphics* graphics);
    std::unique_ptr<Scene> react(Mouse* mouse, GameState& state);

   private:
    std::unique_ptr<Text> txt_win;
    std::unique_ptr<Button> btn_again;
    std::unique_ptr<Button> btn_exit;
};