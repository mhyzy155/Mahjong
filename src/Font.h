#pragma once

#include <SDL2/SDL_ttf.h>

class Font {
public:
	Font(const char* path, int size);
    ~Font();
    TTF_Font* getFont() const;
    operator bool() const;

private:
    TTF_Font *font;
};