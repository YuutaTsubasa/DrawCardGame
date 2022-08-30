#include <SDL.h>
#include "../GameCore/AssetsManager/font_assets_manager.h"
#include "card.h"

Yuuta::GameObjects::Card::Card(
    SDL_Rect range,
    string fontId, int fontSize, 
    SDL_Color fontColor,
    SDL_Color frontColor,
    SDL_Color backColor,
    function<bool()> canFlip,
    function<void(Card&)> onFlip) : GameObject(
        range, 
        nullptr, 
        vector<shared_ptr<GameObject>>()){
    _fontId = fontId;
    _fontSize = fontSize;
    _fontColor = fontColor;
    _text = "";
    _canFlip = canFlip;
    _onFlip = onFlip;

    _frontColor = frontColor;
    _backColor = backColor;

    _isFront = false;
    _isDirty = false;
}

void Yuuta::GameObjects::Card::setText(string text){
    if (_text == text)
        return;
    
    _text = text;
    _isDirty = true;
}

string Yuuta::GameObjects::Card::getText(){
    return _text;
}

void Yuuta::GameObjects::Card::flip(){
    if (!_canFlip())
        return;

    _isFront = !_isFront;
}

void Yuuta::GameObjects::Card::handleEvent(SDL_Event& event){
    if( event.type != SDL_MOUSEBUTTONUP )
        return;

    int x, y;
    SDL_GetMouseState( &x, &y );

    if (x >= _range.x && x <= _range.x + _range.w &&
        y >= _range.y && y <= _range.y + _range.h &&
        !_isFront){
        flip();
        _onFlip(*this);
    }
}

void Yuuta::GameObjects::Card::draw(
    const SDL_Rect& parentRange,
    shared_ptr<SDL_Renderer> renderer
) {
    auto worldRange = SDL_Rect {
        parentRange.x + _range.x, parentRange.y + _range.y,
        _range.w, _range.h
    };

    if (_isDirty) {
        _fontTexture = 
            GameCore::AssetsManager::FontAssetsManager::getInstance(renderer)
                ->createText(_fontId, _fontSize, _fontColor, _text);
        _isDirty = false;
    }

    auto currentColor = _isFront ? _frontColor : _backColor;
    SDL_SetRenderDrawColor( 
        renderer.get(), 
        currentColor.r, 
        currentColor.g, 
        currentColor.b, 
        currentColor.a);        

    SDL_RenderFillRect(renderer.get(), &worldRange );

    _texture = _isFront ? _fontTexture : nullptr;
    GameObject::draw(parentRange, renderer);
}
