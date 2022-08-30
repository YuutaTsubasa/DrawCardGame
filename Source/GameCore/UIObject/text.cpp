#include <SDL.h>
#include "../AssetsManager/font_assets_manager.h"
#include "text.h"

GameCore::UIObject::Text::Text(
    SDL_Point point,
    string fontId, 
    int fontSize, 
    SDL_Color fontColor) : GameObject(
        SDL_Rect {point.x, point.y, 0, 0}, 
        nullptr, 
        vector<shared_ptr<GameObject>>()){
    _fontId = fontId;
    _fontSize = fontSize;
    _fontColor = fontColor;
    _text = "";
    _isDirty = false;
}

void GameCore::UIObject::Text::setText(string text){
    if (_text == text)
        return;
    
    _text = text;
    _isDirty = true;
}

void GameCore::UIObject::Text::draw(
    const SDL_Rect& parentRange,
    shared_ptr<SDL_Renderer> renderer
) {
    
    if (_isDirty) {
        _texture = 
            GameCore::AssetsManager::FontAssetsManager::getInstance(renderer)
                ->createText(_fontId, _fontSize, _fontColor, _text);

        SDL_Point size;
        SDL_QueryTexture(_texture.get(), NULL, NULL, &size.x, &size.y);
        _range = SDL_Rect {_range.x, _range.y, size.x, size.y};
        _isDirty = false;
    }

    GameObject::draw(parentRange, renderer);
}
