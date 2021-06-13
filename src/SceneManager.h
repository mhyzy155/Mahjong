#include "Scene.h"

class SceneManager {
   public:
    void draw();
    bool react();

   private:
    std::unique_ptr<Scene> currScene;
};