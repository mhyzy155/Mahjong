#include <vector>
#include <memory>

#include "Graphics.h"
#include "Mouse.h"
#include "GameState.h"

class Scene {
   public:
    virtual void draw() = 0;
    virtual std::unique_ptr<Scene> react(Mouse* mouse, GameState& state) = 0;
    virtual ~Scene(){};
};