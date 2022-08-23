#ifndef YUUTA_GAME_H
#define YUUTA_GAME_H
#include <iostream>
#include <SDL.h>
using namespace std;

namespace YuutaGame
{
    class Game {
        private:
            SDL_Window* _window;
            SDL_Renderer* _renderer;
            int _screenWidth;
            int _screenHeight;

            SDL_Window* createWindow(
                string title,
                int screenWidth,
                int screenHeight);
            SDL_Renderer* createRenderer(SDL_Window* window);
            void clearRenderer(SDL_Renderer* renderer);

        public:
            Game(
                string title, 
                int screenWidth, 
                int screenHeight);
            ~Game();
            void run();
    };
}
#endif

