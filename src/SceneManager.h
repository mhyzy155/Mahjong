#include "Scenes.h"

class SceneManager {
   public:
    SceneManager(Graphics* gfx);
    void draw();
    void react(Mouse* mouse, GameState& state);

   private:
    std::unique_ptr<Scene> currScene;
};