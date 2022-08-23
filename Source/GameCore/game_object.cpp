#include <memory>
#include <SDL.h>
#include "game_object.h"
using std::shared_ptr;
using std::vector;

GameCore::GameObject::GameObject(
    SDL_Rect range, 
    shared_ptr<SDL_Texture> texture,
    vector<shared_ptr<GameObject>> children){
    _range = range;
    _texture = texture;
    _children = children;
}

void GameCore::GameObject::handleEvents(SDL_Event& event){
    for(auto& child : _children){
        child->handleEvents(event);
    }
}

void GameCore::GameObject::update(){
    for(auto& child : _children){
        child->update();
    }
}

void GameCore::GameObject::draw(shared_ptr<SDL_Renderer> renderer){
    if (_texture != nullptr){
        SDL_RenderCopy(
            renderer.get(),
            _texture.get(),
            nullptr,
            &_range
        );
    }

    for(auto& child : _children){
        child->draw(renderer);
    }
}