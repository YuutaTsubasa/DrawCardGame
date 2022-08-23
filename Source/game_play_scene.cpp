#include <vector>
#include <memory>
#include <SDL.h>
#include "game_play_scene.h"
using std::shared_ptr;
using std::vector;

Yuuta::GamePlayScene::GamePlayScene(
    SDL_Rect range, 
    shared_ptr<SDL_Texture> texture,
    vector<shared_ptr<GameObject>> children) : 
        GameObject(range, texture, children){
    
}