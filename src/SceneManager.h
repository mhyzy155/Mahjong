#include "Scenes.h"

class SceneManager {
   public:
    SceneManager(Graphics* gfx, GameState& state);
    void draw();
    void reactMBDown(Mouse* mouse, Uint8 m_button);
    void reactKDown(SDL_Keycode k_code);

   private:
    std::unique_ptr<Scene> currScene;
    GameState& g_state;
};