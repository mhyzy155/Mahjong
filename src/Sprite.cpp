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

void Sprite::DrawSprite(int x, int y, SDL_Renderer* renderer) {
    img_rect.x = x;
    img_rect.y = y;
    SDL_RenderCopy(renderer, texture, NULL, &img_rect);
}

void Sprite::DrawSprite(int x, int y, float scale, SDL_Renderer* renderer) {
    img_rect.x = x;
    img_rect.y = y;
    SDL_Rect dest_rect = img_rect;
    dest_rect.h = int(img_rect.h * scale);
    dest_rect.w = int(img_rect.w * scale);
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
}

SDL_Texture* Sprite::getTex() {
    return texture;
}

SDL_Rect Sprite::getRect() {
    return img_rect;
}
