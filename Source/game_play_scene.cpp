#include <vector>
#include <memory>
#include <SDL.h>
#include "game_play_scene.h"
#include "GameCore/UIObject/text.h"
#include "GameObjects/card.h"
#include "GameObjects/card_collection.h"
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::to_string;
using GameCore::UIObject::Text;
using Yuuta::GameObjects::Card;
using Yuuta::GameObjects::CardCollection;

Yuuta::GamePlayScene::GamePlayScene(
    SDL_Rect range, 
    shared_ptr<SDL_Texture> texture) : 
        GameObject(range, texture, vector<shared_ptr<GameObject>>()){
    auto defaultColor = SDL_Color {0xFF, 0xFF, 0xFF, 0xFF};
    auto defaultFontId = "SweiB2SugarCJKtc-Black";
    auto defaultFontSize = 20;
    auto defaultFrontColor = SDL_Color {0xFF, 0xFF, 0xFF, 0xFF};
    auto defaultBackColor = SDL_Color  {0x33, 0x33, 0x33, 0xFF};
    
    vector<string> cardTexts = 
        {"悠", "太", "翼", "寫", "程", "式", "語", "言"};

    _flipTimes = 0;

    _scoreText = make_shared<Text>(
        SDL_Point {0, 0},
        defaultFontId,
        defaultFontSize,
        defaultColor);

    auto cardCollection = make_shared<CardCollection>(
        range,
        cardTexts,
        [&](){ ++_flipTimes; });

    _children.push_back(_scoreText);
    _children.push_back(cardCollection);
}

void Yuuta::GamePlayScene::update(){
    _scoreText->setText("翻牌次數：" + to_string(_flipTimes));

    GameObject::update();
}