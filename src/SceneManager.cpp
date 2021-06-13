#include "SceneManager.h"

void SceneManager::draw(){
    currScene->draw();
}

bool SceneManager::react(){
    if(currScene->react()){
        if(currScene->isQuit()) return true;
        else currScene = currScene->nextScene();
    }
    return false;
}