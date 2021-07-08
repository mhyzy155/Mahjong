#include <initializer_list>

#include "Button.h"

class ButtonSwitch : public Drawable {
   public:
    ButtonSwitch(std::initializer_list<std::string> list_str, int txt_size, SDL_Color col_txt, SDL_Color col_bg, int margin = 0, int btn_state = 0);
    void draw(int x, int y, SDL_Renderer* renderer);
    SDL_Rect getRect();
    int changeState();
    ButtonSwitch& operator++();

   private:
    std::vector<Button> buttons;
    int state;

};