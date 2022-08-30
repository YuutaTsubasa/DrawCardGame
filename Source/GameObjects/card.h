#ifndef YUUTA_CARD_H
#define YUUTA_CARD_H
#include <iostream>
#include <functional>
#include <SDL.h>
#include "../GameCore/game_object.h"
using std::string;
using std::function;
using GameCore::GameObject;

namespace Yuuta {
    namespace GameObjects {
        class Card : public GameObject {
            private:
                string _fontId;
                int _fontSize;
                SDL_Color _fontColor;
                string _text;
                shared_ptr<SDL_Texture> _fontTexture;
                function<bool()> _canFlip;
                function<void(Card&)> _onFlip;

                SDL_Color _frontColor;
                SDL_Color _backColor;

                bool _isFront;
                bool _isDirty;

            public:
                Card(SDL_Rect range,
                    string fontId, int fontSize, 
                    SDL_Color fontColor,
                    SDL_Color frontColor,
                    SDL_Color backColor,
                    function<bool()> canFlip,
                    function<void(Card&)> onFlip);

                void setText(string text);
                string getText();
                void flip();

                virtual void handleEvent(SDL_Event& event);

                virtual void draw(
                    const SDL_Rect& parentRange,
                    shared_ptr<SDL_Renderer> renderer);
        };
    }
}
#endif

