#include <cstdio>
#include <iostream>
#include <algorithm>
#include "card_collection.h"
#include "font_writer.h"
using namespace std;

YuutaGame::CardCollection::CardCollection(
    const vector<string>& cardTexts,
    int screenWidth,
    int screenHeight)
{
    _status = Idle;
    _flipTimes = 0;

    vector<string> duplicateCardTexts;
    for (const auto &cardText : cardTexts){
        duplicateCardTexts.push_back(cardText);
        duplicateCardTexts.push_back(cardText);
    }

    random_shuffle(duplicateCardTexts.begin(), duplicateCardTexts.end());

    for (int i = 0 ; i < duplicateCardTexts.size(); ++i){
        auto card = Card(duplicateCardTexts[i], 
            {screenWidth / 2 + (Card::DEFAULT_WIDTH + 10) * (i % 4 - 1.5f) - 0.5f * Card::DEFAULT_WIDTH,
             screenHeight / 2 + (Card::DEFAULT_HEIGHT + 10) * (i / 4 - 1.5f) - 0.5f * Card::DEFAULT_HEIGHT,
             Card::DEFAULT_WIDTH, Card::DEFAULT_HEIGHT},
             Card::DEFAULT_FRONT_COLOR,
             Card::DEFAULT_BACK_COLOR,
             Card::DEFAULT_FONT_ID,
             Card::DEFAULT_FONT_SIZE,
             Card::DEFAULT_FONT_COLOR);
        _cards.push_back(card);
    }
}

YuutaGame::CardCollection::~CardCollection(){

}

void YuutaGame::CardCollection::update(SDL_Event* event) {
    switch(_status){
        case Idle:
            for(auto &card : _cards) {
                if (!card.isClick(event)) continue;
                if (card.isFront()) continue;

                card.flip();
                _firstFlipCard = &card;
                _status = WaitSecondCard;
            }
            break;
        case WaitSecondCard:
            for(auto &card : _cards) {
                if (!card.isClick(event)) continue;
                if (card.isFront()) continue;
                
                card.flip();
                _secondFlipCard = &card;
                _flipTimes++;
                if (_firstFlipCard->getText() != _secondFlipCard->getText()){
                    _finishJudgeTime = SDL_GetTicks() + JUDGE_DURATION;
                    _status = WaitToFlipBack;
                    break;
                }
                _status = Idle;
            }
            break;
        case WaitToFlipBack:
            if (SDL_GetTicks() < _finishJudgeTime) break;
            _firstFlipCard->flip();
            _secondFlipCard->flip();
            _status = Idle;
            break;
    }
}

void YuutaGame::CardCollection::draw(SDL_Renderer* renderer){    
    for(auto &card : _cards)
        card.draw(renderer);

    string scoreText = "翻牌次數: " + to_string(_flipTimes);
    auto score = FontWriter::getInstance(renderer)
        ->write(
            Card::DEFAULT_FONT_ID,
            Card::DEFAULT_FONT_SIZE,
            SDL_Color { 0xFF, 0xFF, 0xFF, 0xFF },
            scoreText
        );

    auto range = SDL_Rect {
        0, 0, 
        scoreText.length() * 10, Card::DEFAULT_FONT_SIZE * 2
    };

    SDL_RenderCopy(
        renderer,
        score,
        NULL,
        &range
    );

    SDL_DestroyTexture(score);
}