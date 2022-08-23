#include <iostream>
#include <string>
#include <memory>
#include <SDL_ttf.h>
#include "font_assets_manager.h"
using std::shared_ptr;
using std::make_shared;
using std::to_string;
using GameCore::AssetsManager::FontAssetsManager;

shared_ptr<FontAssetsManager> FontAssetsManager::_instance = nullptr;

FontAssetsManager::FontAssetsManager(shared_ptr<SDL_Renderer> renderer){
    _renderer = renderer;
}

shared_ptr<FontAssetsManager> FontAssetsManager::getInstance(
    shared_ptr<SDL_Renderer> renderer){
    if (_instance != nullptr)
        return _instance;

    _instance = shared_ptr<FontAssetsManager>(
        new FontAssetsManager(renderer));
    return _instance;
}

shared_ptr<SDL_Texture> FontAssetsManager::createText(
    string fontId, int size, SDL_Color color, string text) {
    string sizeFontId = fontId + "_" + to_string(size);
    if (_resourceMap.find(sizeFontId) == _resourceMap.end())
        _resourceMap[sizeFontId] = shared_ptr<TTF_Font>(
            TTF_OpenFont(("../Resource/" + fontId + ".ttf").c_str(),  size),
            [](auto font) { TTF_CloseFont(font); });

    auto textSurface = shared_ptr<SDL_Surface>(
        TTF_RenderUTF8_Solid(_resourceMap[sizeFontId].get(), text.c_str(), color),
        [](auto surface) { SDL_FreeSurface( surface ); });
    auto textTexture = shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(_renderer.get(), textSurface.get()),
        [](auto texture) { SDL_DestroyTexture(texture); });    
    return textTexture;
}