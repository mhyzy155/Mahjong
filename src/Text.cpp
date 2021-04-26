#include "Text.h"

size_t Text::count = 0;

Text::Text(std::string txt, int size, Uint8 r, Uint8 g, Uint8 b, Uint8 a) : text(txt), font_size(size), color({r, g, b, a}) {
    count++;
}

Text::Text(std::string txt, int size, SDL_Color col) : text(txt), font_size(size), color(col) {
    count++;
}

Text::Text(const Text &t) : color(t.color), font_size(t.font_size), text(t.text) {
    count++;
}

Text::~Text() {
    count--;
    if (count < 1 && TTF_WasInit()) {
        TTF_Quit();
    }
}

void Text::drawText(int x, int y, SDL_Surface *destination) {
    SDL_Rect coordinates{x, y};
    SDL_Surface *message = getTextSurface();
    if (!message) {
        printf("Text::getTextSurface error\n");
        return;
    }

    SDL_BlitSurface(message, NULL, destination, &coordinates);
    if (SDL_SetColorKey(destination, SDL_TRUE, SDL_MapRGB(destination->format, 0, 0, 0)) < 0) {
        printf("SDL_SetColorKey error: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(message);
}

void Text::drawText(int x, int y, SDL_Renderer *renderer) {
    SDL_Surface *message = getTextSurface();
    if (!message) {
        printf("Text::getTextSurface error\n");
        return;
    }

    SDL_Rect coordinates = message->clip_rect;
    coordinates.x = x;
    coordinates.y = y;

    // OLD WAY?
    /*SDL_Surface* destination = SDL_CreateRGBSurface(0,message->clip_rect.w,message->clip_rect.h,16,0,0,0,255);
	SDL_BlitSurface(message, NULL, destination, &coordinates);
	if (SDL_SetColorKey(destination, SDL_TRUE, SDL_MapRGB(destination->format, 0, 0, 0)) < 0)
	{
		// Unrecoverable error, exit here.
		printf("SDL_Init failed: %s\n", SDL_GetError());
	}
    //SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, destination);
    */
   
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, message);

    SDL_RenderCopy(renderer, texture, NULL, &coordinates);

    SDL_DestroyTexture(texture);
    //SDL_FreeSurface(destination);
    SDL_FreeSurface(message);
}

SDL_Surface *Text::getTextSurface() {
    if (!TTF_WasInit()) {
        if (TTF_Init() < 0) {
            printf("TTF_Init error: %s\n", TTF_GetError());
            return nullptr;
        }
    }

    TTF_Font *font = TTF_OpenFont("../assets/fonts/LiberationSans-Regular.ttf", font_size);
    if (!font) {
        printf("TTF_OpenFont error: %s\n", TTF_GetError());
        return nullptr;
    }

    SDL_Surface *message = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!message) {
        printf("TTF_RenderText_Solid error: %s\n", TTF_GetError());
    }

    TTF_CloseFont(font);
    return message;
}

SDL_Rect Text::getTextRect() {
    SDL_Surface *message = getTextSurface();
    if (!message) {
        printf("Text::getTextSurface error\n");
        return SDL_Rect{0, 0, 0, 0};
    }

    SDL_Rect result = message->clip_rect;

    SDL_FreeSurface(message);
    return result;
}
