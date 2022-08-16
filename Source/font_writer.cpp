#include <iostream>
#include <string>
#include "font_writer.h"
using namespace std;

bool YuutaGame::FontWriter::_hasInstance = false;
YuutaGame::FontWriter* YuutaGame::FontWriter::_instance = NULL;

YuutaGame::FontWriter::FontWriter(SDL_Renderer* renderer){
    _renderer = renderer;
}

YuutaGame::FontWriter::~FontWriter(){
    for(auto &pair : _resourceMap){
        TTF_CloseFont(pair.second);
    }
}

YuutaGame::FontWriter* YuutaGame::FontWriter::getInstance(SDL_Renderer* renderer){
    if (_hasInstance)
        return _instance;

    _instance = new FontWriter(renderer);
    _hasInstance = true;
    return _instance;
}

void YuutaGame::FontWriter::destroyInstance(){
    delete _instance;
    _hasInstance = false;
}

SDL_Texture* YuutaGame::FontWriter::write(string fontId, int size, SDL_Color color, string text) {
    string sizeFontId = fontId + "_" + to_string(size);
    if (_resourceMap.find(sizeFontId) == _resourceMap.end())
        _resourceMap[sizeFontId] = 
            TTF_OpenFont(("../Resource/" + fontId + ".ttf").c_str(),  size);

    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(_resourceMap[sizeFontId], text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface );    
    SDL_FreeSurface( textSurface );
    return textTexture;
}