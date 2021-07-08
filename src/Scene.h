#pragma once
#include <vector>
#include <memory>

#include "Graphics.h"
#include "Mouse.h"
#include "GameState.h"

class Scene {
   public:
    virtual void draw(){};
    virtual std::unique_ptr<Scene> reactMBDown(Mouse* mouse, Uint8 m_button, GameState& state){return nullptr;};
    virtual std::unique_ptr<Scene> reactKDown(SDL_Keycode k_code, GameState& state){return nullptr;};
    virtual ~Scene(){};
};