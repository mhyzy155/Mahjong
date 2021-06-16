#include "SceneManager.h"

SceneManager::SceneManager(Graphics* gfx) : currScene{new SceneMenuMain(gfx)} {}

void SceneManager::draw(){
    currScene->draw();
}

void SceneManager::react(Mouse* mouse, GameState& state){
    auto newScene = currScene->react(mouse, state);
    if(newScene) currScene.swap(newScene);
}