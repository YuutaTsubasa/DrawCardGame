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

void GameCore::GameObject::handleEvent(SDL_Event& event){
    for(auto& child : _children){
        child->handleEvent(event);
    }
}

void GameCore::GameObject::update(){
    for(auto& child : _children){
        child->update();
    }
}

void GameCore::GameObject::draw(
    const SDL_Rect& parentRange,
    shared_ptr<SDL_Renderer> renderer){
    auto worldRange = SDL_Rect {
        parentRange.x + _range.x, parentRange.y + _range.y,
        _range.w, _range.h
    };
    
    if (_texture != nullptr){
        SDL_RenderCopy(
            renderer.get(),
            _texture.get(),
            nullptr,
            &worldRange
        );
    }

    for(auto& child : _children){
        child->draw(worldRange, renderer);
    }
}