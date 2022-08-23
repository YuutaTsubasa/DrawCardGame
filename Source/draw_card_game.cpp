#include <memory>
#include <vector>
#include "draw_card_game.h"
#include "game_play_scene.h"
using std::make_shared;
using std::shared_ptr;
using std::vector;
using Yuuta::GamePlayScene;

Yuuta::DrawCardGame::DrawCardGame(
    string title, 
    int screenWidth, 
    int screenHeight) : Game(title, screenWidth, screenHeight) {
    
    _rootGameObject = make_shared<GamePlayScene>(
        SDL_Rect {0, 0, screenWidth, screenHeight},
        nullptr,
        vector<shared_ptr<GameObject>>()
    );
}