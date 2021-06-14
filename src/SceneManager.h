#include "Scenes.h"

class SceneManager {
   public:
    SceneManager();
    void draw(Graphics* graphics);
    void react(Mouse* mouse, GameState& state);

   private:
    std::unique_ptr<Scene> currScene;
};