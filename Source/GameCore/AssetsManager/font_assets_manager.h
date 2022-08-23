#ifndef GAME_CORE_FONT_ASSETS_MANAGER_H
#define GAME_CORE_FONT_ASSETS_MANAGER_H
#include <iostream>
#include <map>
#include <memory>
#include <SDL_ttf.h>
using std::shared_ptr;
using std::map;
using std::string;

namespace GameCore {
    namespace AssetsManager{
        class FontAssetsManager {
            private:
                static shared_ptr<FontAssetsManager> _instance;
                shared_ptr<SDL_Renderer> _renderer;
                map<string, shared_ptr<TTF_Font>> _resourceMap;

                FontAssetsManager(shared_ptr<SDL_Renderer> renderer);
            public:
                static shared_ptr<FontAssetsManager> getInstance(shared_ptr<SDL_Renderer> renderer);
                shared_ptr<SDL_Texture> createText(string fontId, int size, SDL_Color color, string text);
        };
    }
}
#endif