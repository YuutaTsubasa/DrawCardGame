#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "game.h"
#include "card_collection.h"
#include "font_writer.h"
using namespace std;

YuutaGame::Game::Game(
    string title, 
    int screenWidth, 
    int screenHeight
){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    _window = createWindow(title, screenWidth, screenHeight);
    _renderer = createRenderer(_window);

    FontWriter::getInstance(_renderer);
}

YuutaGame::Game::~Game(){
    FontWriter::destroyInstance();
    SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

SDL_Window* YuutaGame::Game::createWindow(
    string title,
    int screenWidth,
    int screenHeight)
{
	return SDL_CreateWindow(
        title.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        screenWidth, 
        screenHeight, 
        SDL_WINDOW_SHOWN);
}

SDL_Renderer* YuutaGame::Game::createRenderer(SDL_Window* window) {
	SDL_Renderer* renderer = 
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderPresent(renderer);
	return renderer;
}

void YuutaGame::Game::clearRenderer(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
}


void YuutaGame::Game::run(){
    bool isQuit = false;

    vector<string> cardTexts = 
        {"悠", "太", "翼", "寫", "程", "式", "語", "言"};
    
    CardCollection cardCollection(
        cardTexts, 
        _screenWidth, 
        _screenHeight);

	while(!isQuit) {
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT){
				isQuit = true;
			}

            cardCollection.update(&event);
		}

        cardCollection.update(&event);

        clearRenderer(_renderer);
        cardCollection.draw(_renderer);
        SDL_RenderPresent(_renderer);
	}
}