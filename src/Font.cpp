#include "Font.h"

Font::Font(const char* path, int size){
    font = TTF_OpenFont(path, size);
    if (!font) printf("TTF_OpenFont error: %s\n", TTF_GetError());
}

Font::~Font(){
    if(font){
        TTF_CloseFont(font);
        font = nullptr;
    }
}

TTF_Font* Font::getFont() const {
    return font;
}

Font::operator bool() const {
    if(font) return true;
    else return false;
}