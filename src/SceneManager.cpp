#include "SceneManager.h"

SceneManager::SceneManager() : currScene{new SceneMenuMain()} {}

void SceneManager::draw(Graphics* graphics){
    currScene->draw(graphics);
}

void SceneManager::react(Mouse* mouse, GameState& state){
    auto newScene = currScene->react(mouse, state);
    if(newScene) currScene.swap(newScene);
}