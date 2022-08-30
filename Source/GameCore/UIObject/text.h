#ifndef GAME_CORE_TEXT_H
#define GAME_CORE_TEXT_H
#include <iostream>
#include <SDL.h>
#include "../game_object.h"
using std::string;

namespace GameCore {
    namespace UIObject {
        class Text : public GameObject {
            private:
                string _fontId;
                int _fontSize;
                SDL_Color _fontColor;
                string _text;
                bool _isDirty;

            public:
                Text(SDL_Point point,
                    string fontId, int fontSize, 
                    SDL_Color fontColor);

                void setText(string text);
                virtual void draw(
                    const SDL_Rect& parentRange,
                    shared_ptr<SDL_Renderer> renderer);
        };
    }
}
#endif

