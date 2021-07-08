#include "ButtonSwitch.h"

#include <algorithm>

ButtonSwitch::ButtonSwitch(std::initializer_list<std::string> list_str, int txt_size, SDL_Color col_txt, SDL_Color col_bg, int margin, int btn_state) : state{btn_state} {
    for(const auto& s : list_str){
        buttons.emplace_back(new Text(s, txt_size, col_txt), col_bg, margin);
    }

    // Set the same size for all buttons
    std::vector<SDL_Rect> vec_rect(buttons.size());
    std::transform(buttons.begin(), buttons.end(), vec_rect.begin(), [](Button& b) { return b.getRect(); });
    SDL_Rect rect_max{0, 0, 0, 0};
    auto rect_max_w = *std::max_element(vec_rect.begin(), vec_rect.end(), [](auto a, auto b) { return a.w < b.w; });
    auto rect_max_h = *std::max_element(vec_rect.begin(), vec_rect.end(), [](auto a, auto b) { return a.h < b.h; });
    rect_max.w = rect_max_w.w;
    rect_max.h = rect_max_h.h;
    for(auto& b : buttons){
        b.setRect(rect_max);
    }
}

void ButtonSwitch::draw(int x, int y, SDL_Renderer *renderer) {
    buttons[state].draw(x, y, renderer);
}

SDL_Rect ButtonSwitch::getRect() {
    return buttons[state].getRect();
}

int ButtonSwitch::changeState() {
    ++state;
    if (state == buttons.size()) state = 0;
    return state;
}

ButtonSwitch& ButtonSwitch::operator++() {
    ++state;
    if (state == buttons.size()) state = 0;
    return *this;
}