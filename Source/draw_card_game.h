#ifndef YUUTA_DRAW_CARD_GAME_H
#define YUUTA_DRAW_CARD_GAME_H
#include <iostream>
#include <memory>
#include "GameCore/game.h"
using std::shared_ptr;
using std::string;
using GameCore::Game;

namespace Yuuta
{
    class DrawCardGame: public Game {
        public:
            DrawCardGame(
                string title, 
                int screenWidth, 
                int screenHeight);
    };
}
#endif

