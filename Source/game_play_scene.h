#ifndef YUUTA_GAME_PLAY_SCENE_H
#define YUUTA_GAME_PLAY_SCENE_H
#include <memory>
#include <vector>
#include "GameCore\game_object.h"
#include "GameCore\UIObject\text.h"
using std::shared_ptr;
using std::vector;
using GameCore::GameObject;
using GameCore::UIObject::Text;

namespace Yuuta
{
    class GamePlayScene : public GameObject {
        private:
            shared_ptr<Text> _scoreText;
            int _flipTimes;

        public:
            GamePlayScene(
                SDL_Rect range, 
                shared_ptr<SDL_Texture> texture);

            virtual void update();
    };
}
#endif