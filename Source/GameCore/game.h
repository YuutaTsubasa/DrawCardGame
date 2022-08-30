#ifndef GAME_CORE_GAME_H
#define GAME_CORE_GAME_H
#include <iostream>
#include <memory>
#include <SDL.h>
#include "game_object.h"
using std::shared_ptr;
using std::string;

namespace GameCore
{
    class Game {
        protected:
            shared_ptr<SDL_Window> _window;
            shared_ptr<SDL_Renderer> _renderer;
            SDL_Rect _screenRange;

            shared_ptr<GameObject> _rootGameObject;

            shared_ptr<SDL_Window> createWindow(
                string title,
                int screenWidth,
                int screenHeight);
            shared_ptr<SDL_Renderer> createRenderer(shared_ptr<SDL_Window> window);
            void clearRenderer(shared_ptr<SDL_Renderer> renderer);

        public:
            Game(
                string title, 
                int screenWidth, 
                int screenHeight);
            ~Game();
            void run();

            virtual void handleEvent(SDL_Event& event);
            virtual void update();
            virtual void draw(shared_ptr<SDL_Renderer> renderer);
    };
}
#endif

