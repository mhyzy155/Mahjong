#include "Text.h"
#include "Font.h"

size_t Text::count = 0;

Text::Text(std::string txt, int size, Uint8 r, Uint8 g, Uint8 b, Uint8 a) : text{txt}, font_size{size}, color{r, g, b, a}, surface{nullptr} {
    count++;
    updateSurface();
}

Text::Text(std::string txt, int size, SDL_Color col) : text{txt}, font_size{size}, color{col}, surface{nullptr} {
    count++;
    updateSurface();
}

Text::Text(const Text &t) : color{t.color}, font_size{t.font_size}, text{t.text}, surface{nullptr} {
    count++;
    updateSurface();
}

Text::~Text() {
    count--;
    if(surface){
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if (count < 1 && TTF_WasInit()) {
        TTF_Quit();
    }
}

void Text::drawText(int x, int y, SDL_Surface *destination) {
    SDL_Rect coordinates{x, y};
    if (!surface) {
        printf("Text::drawText error: missing textSurface\n");
        return;
    }

    SDL_BlitSurface(surface, NULL, destination, &coordinates);
    if (SDL_SetColorKey(destination, SDL_TRUE, SDL_MapRGB(destination->format, 0, 0, 0)) < 0) {
        printf("SDL_SetColorKey error: %s\n", SDL_GetError());
    }
}

void Text::drawText(int x, int y, SDL_Renderer *renderer) {
    if (!surface) {
        printf("Text::drawText error: missing textSurface\n");
        return;
    }

    SDL_Rect coordinates = surface->clip_rect;
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
   
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, &coordinates);
    SDL_DestroyTexture(texture);
    //SDL_FreeSurface(destination);
}

void Text::updateSurface() {
    if (!TTF_WasInit()) {
        if (TTF_Init() < 0) {
            printf("TTF_Init error: %s\n", TTF_GetError());
            return;
        }
    }

    Font font("../assets/fonts/LiberationSans-Regular.ttf", font_size);
    if(!font){
        printf("Text::updateSurface error creating a font\n");
        return;
    }

    if(surface){
        SDL_FreeSurface(surface);
        surface = nullptr;
    }

    surface = TTF_RenderText_Solid(font.getFont(), text.c_str(), color);
    if (!surface) {
        printf("TTF_RenderText_Solid error: %s\n", TTF_GetError());
    }
}

SDL_Rect Text::getTextRect() {
    if (!surface) {
        printf("Text::getTextRect error: missing textSurface\n");
        return SDL_Rect{0, 0, 0, 0};
    }

    SDL_Rect result = surface->clip_rect;
    return result;
}
