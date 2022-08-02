#include <cstdio>
#include <iostream>
#include <SDL.h>
#include "card.h"
#include "font_writer.h"
using namespace std;

const SDL_Color YuutaGame::Card::DEFAULT_FRONT_COLOR = {0xFF, 0xFF, 0xFF, 0xFF};
const SDL_Color YuutaGame::Card::DEFAULT_BACK_COLOR = {0x33, 0x33, 0x33, 0xFF};
const string YuutaGame::Card::DEFAULT_FONT_ID = "SweiB2SugarCJKtc-Black";
const SDL_Color YuutaGame::Card::DEFAULT_FONT_COLOR = {0x00, 0x00, 0x00, 0xFF};

YuutaGame::Card::Card(
    string text, 
    SDL_Rect range,
    SDL_Color frontColor, 
    SDL_Color backColor,
    string fontId,
    int fontSize,
    SDL_Color fontColor)
{
    _text = text;
    _range = range;
    _frontColor = frontColor;
    _backColor = backColor;
    _fontId = fontId;
    _fontSize = fontSize;
    _fontColor = fontColor;
    _isFront = false;
}

YuutaGame::Card::~Card(){

}

void YuutaGame::Card::Update(SDL_Event* event) {
    if( event->type != SDL_MOUSEBUTTONUP )
        return;

    int x, y;
    SDL_GetMouseState( &x, &y );

    if (x >= _range.x && x <= _range.x + _range.w &&
        y >= _range.y && y <= _range.y + _range.h){
        _isFront = !_isFront;
    }
}

void YuutaGame::Card::Draw(SDL_Renderer* renderer){
    SDL_Color currentColor = _isFront ? _frontColor : _backColor;
    SDL_SetRenderDrawColor( 
        renderer, 
        currentColor.r, 
        currentColor.g, 
        currentColor.b, 
        currentColor.a);        

    SDL_RenderFillRect( renderer, &_range );

    if (_isFront){
        SDL_RenderCopy(renderer, 
            FontWriter::getInstance(renderer)->write(
                _fontId, _fontSize, _fontColor, _text
            ), NULL, &_range);
    }
}