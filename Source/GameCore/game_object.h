#ifndef GAME_CORE_GAME_OBJECT_H
#define GAME_CORE_GAME_OBJECT_H
#include <memory>
#include <vector>
#include <SDL.h>
using std::shared_ptr;
using std::vector;

namespace GameCore
{
    class GameObject {
        protected:
            SDL_Rect _range;
            shared_ptr<SDL_Texture> _texture; 

            vector<shared_ptr<GameObject>> _children;
        public:
            GameObject(
                SDL_Rect range, 
                shared_ptr<SDL_Texture> texture,
                vector<shared_ptr<GameObject>> children);
            virtual void handleEvent(SDL_Event& event);
            virtual void update();
            virtual void draw(
                const SDL_Rect& parentRange,
                shared_ptr<SDL_Renderer> renderer);
    };
}
#endif