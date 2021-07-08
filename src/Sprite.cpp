#include "Sprite.h"

Sprite::Sprite(std::string path, SDL_Renderer* renderer) : img_path(path) {
    texture = IMG_LoadTexture(renderer, img_path.c_str());
    if (texture == nullptr) {
        printf("Failed to load texture %s\n\terror : %s \n", img_path.c_str(), SDL_GetError());
    } else
        printf("Image %s loaded\n", img_path.c_str());
        SDL_QueryTexture(texture, NULL, NULL, &img_rect.w, &img_rect.h);
}

Sprite::~Sprite(){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Sprite::draw(int x, int y, SDL_Renderer* renderer) {
    img_rect.x = x;
    img_rect.y = y;
    SDL_RenderCopy(renderer, texture, NULL, &img_rect);
}

void Sprite::draw(int x, int y, float scale, SDL_Renderer* renderer) {
    img_rect.x = x;
    img_rect.y = y;
    SDL_Rect dest_rect = img_rect;
    dest_rect.h = int(img_rect.h * scale);
    dest_rect.w = int(img_rect.w * scale);
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
}

void Sprite::updateTex(std::string path, SDL_Renderer* renderer){
    auto texture_new = IMG_LoadTexture(renderer, path.c_str());
    if (texture_new == nullptr) {
        printf("Failed to load texture %s\n\terror : %s \n", path.c_str(), SDL_GetError());
    } else{
        img_path = path;
        if(texture){
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
        texture = texture_new;
        printf("Image %s loaded\n", img_path.c_str());
        SDL_QueryTexture(texture, NULL, NULL, &img_rect.w, &img_rect.h);
    }
}

SDL_Texture* Sprite::getTex() const {
    return texture;
}

SDL_Rect Sprite::getRect() {
    return img_rect;
}

std::string Sprite::getPath(){
    return img_path;
}