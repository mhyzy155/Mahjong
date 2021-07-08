#include "SceneManager.h"

SceneManager::SceneManager(Graphics* gfx, GameState& state) : currScene{new SceneMenuMain(gfx)}, g_state{state} {}

void SceneManager::draw(){
    currScene->draw();
}

void SceneManager::reactMBDown(Mouse* mouse, Uint8 m_button){
    auto newScene = currScene->reactMBDown(mouse, m_button, g_state);
    if(newScene) currScene.swap(newScene);
}

void SceneManager::reactKDown(SDL_Keycode k_code){
    auto newScene = currScene->reactKDown(k_code, g_state);
    if(newScene) currScene.swap(newScene);
}