#ifndef YUUTA_CARD_H
#define YUUTA_CARD_H
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;

namespace YuutaGame{
    class Card {
        private:
            string _text;
            SDL_Rect _range;
            SDL_Color _frontColor;
            SDL_Color _backColor;

            string _fontId;
            int _fontSize;
            SDL_Color _fontColor;

            bool _isFront;

        public:
            static const SDL_Color DEFAULT_FRONT_COLOR;
            static const SDL_Color DEFAULT_BACK_COLOR;
            static const int DEFAULT_WIDTH = 40;
            static const int DEFAULT_HEIGHT = 60;
            static const string DEFAULT_FONT_ID;
            static const int DEFAULT_FONT_SIZE = 20;
            static const SDL_Color DEFAULT_FONT_COLOR;

            Card(
                string text, 
                SDL_Rect range, 
                SDL_Color frontColor, 
                SDL_Color backColor,
                string fontId,
                int fontSize,
                SDL_Color fontColor);
            ~Card();

            void Update(SDL_Event* event);
            void Draw(SDL_Renderer* renderer);
    };
}
#endif