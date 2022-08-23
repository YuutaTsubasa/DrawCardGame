#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <memory>
#include <vector>
#include "game.h"
#include "AssetsManager/font_assets_manager.h"
using std::shared_ptr;
using std::make_shared;
using std::vector;
using GameCore::AssetsManager::FontAssetsManager;

GameCore::Game::Game(
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

    _rootGameObject = make_shared<GameObject>(
        SDL_Rect {0, 0, _screenWidth, _screenHeight},
        nullptr,
        vector<shared_ptr<GameObject>>()
    );

    FontAssetsManager::getInstance(_renderer);
}

GameCore::Game::~Game(){
    //FontWriter::destroyInstance();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

shared_ptr<SDL_Window> GameCore::Game::createWindow(
    string title,
    int screenWidth,
    int screenHeight)
{
	return shared_ptr<SDL_Window>(
        SDL_CreateWindow(
            title.c_str(), 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            screenWidth, 
            screenHeight, 
            SDL_WINDOW_SHOWN),
        [](auto window) { SDL_DestroyWindow(window); }
        );
}

shared_ptr<SDL_Renderer> GameCore::Game::createRenderer(shared_ptr<SDL_Window> window) {
	shared_ptr<SDL_Renderer> renderer( 
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
        [](auto renderer) { SDL_DestroyRenderer(renderer); });
	SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderPresent(renderer.get());
	return renderer;
}

void GameCore::Game::clearRenderer(shared_ptr<SDL_Renderer> renderer){
    SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer.get());
}


void GameCore::Game::run(){
    bool isQuit = false;

	while(!isQuit) {
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT){
				isQuit = true;
			}

            handleEvent(event);
		}

        update();

        clearRenderer(_renderer);
        draw(_renderer);
        SDL_RenderPresent(_renderer.get());
	}
}

void GameCore::Game::handleEvent(SDL_Event& event){
    _rootGameObject->handleEvents(event);
}

void GameCore::Game::update(){
    _rootGameObject->update();
}

void GameCore::Game::draw(shared_ptr<SDL_Renderer> renderer){
    _rootGameObject->draw(renderer);
}