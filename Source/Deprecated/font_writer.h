#ifndef YUUTA_FONT_LOADER_H
#define YUUTA_FONT_LOADER_H
#include <iostream>
#include <map>
#include <SDL_ttf.h>
using namespace std;

namespace YuutaGame {
    class FontWriter {
        private:
            static bool _hasInstance;
            static FontWriter* _instance;
            SDL_Renderer* _renderer;
            map<string, TTF_Font*> _resourceMap;

            FontWriter(SDL_Renderer* renderer);
            ~FontWriter();

        public:
            static FontWriter* getInstance(SDL_Renderer* renderer);
            static void destroyInstance();
            SDL_Texture* write(string fontId, int size, SDL_Color color, string text);
    };
}
#endif