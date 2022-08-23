#ifndef YUUTA_GAME_PLAY_SCENE_H
#define YUUTA_GAME_PLAY_SCENE_H
#include <memory>
#include <vector>
#include "GameCore\game_object.h"
using std::shared_ptr;
using std::vector;
using GameCore::GameObject;

namespace Yuuta
{
    class GamePlayScene : public GameObject {
        public:
            GamePlayScene(
                SDL_Rect range, 
                shared_ptr<SDL_Texture> texture,
                vector<shared_ptr<GameObject>> children);
    };
}
#endif