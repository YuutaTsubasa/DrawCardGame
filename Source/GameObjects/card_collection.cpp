#include "card.h"
#include "card_collection.h"
#include "../GameCore/game_object.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <memory>
using std::random_shuffle;
using std::function;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;
using GameCore::GameObject;
using Yuuta::GameObjects::Card;

Yuuta::GameObjects::CardCollection::CardCollection(
    SDL_Rect range,
    const vector<string>& cardTexts,
    function<void()> onFlipTwoCards) : 
        GameObject(range, nullptr, vector<shared_ptr<GameObject>>()){
    _status = Idle;
    vector<string> duplicateCardTexts;
    for (const auto &cardText : cardTexts){
        duplicateCardTexts.push_back(cardText);
        duplicateCardTexts.push_back(cardText);
    }
    random_shuffle(duplicateCardTexts.begin(), duplicateCardTexts.end());

    auto defaultFontId = "SweiB2SugarCJKtc-Black";
    auto defaultFontSize = 20;
    auto defaultFrontColor = SDL_Color {0xFF, 0xFF, 0xFF, 0xFF};
    auto defaultBackColor = SDL_Color  {0x33, 0x33, 0x33, 0xFF};

    for (int i = 0 ; i < duplicateCardTexts.size(); ++i){
        auto card = make_shared<Card>(SDL_Rect {
            range.w / 2 + (40 + 10) * (i % 4 - 1.5f) - 0.5f * 40,
            range.h / 2 + (60 + 10) * (i / 4 - 1.5f) - 0.5f * 60,
            40, 60 },
            defaultFontId,
            defaultFontSize,
            SDL_Color {0x00, 0x00, 0x00, 0xFF},
            defaultFrontColor,
            defaultBackColor,
            [&]() { return _status != WaitToFlipBack; },
            [&, onFlipTwoCards](Card& card){
                switch(_status){
                    case Idle:
                        _firstFlipCard = &card;
                        _status = WaitSecondCard;
                        break;
                    case WaitSecondCard:
                        _secondFlipCard = &card;
                        onFlipTwoCards();

                        if (_firstFlipCard->getText() != _secondFlipCard->getText()){
                            _finishJudgeTime = SDL_GetTicks() + 1000;
                            _status = WaitToFlipBack;
                            break;
                        }
                        _status = Idle;
                        break;
                }
            });

        card->setText(duplicateCardTexts[i]);
        _cards.push_back(card);
        _children.push_back(card);
    }
}

void Yuuta::GameObjects::CardCollection::update(){
    GameObject::update();

    if (_status != WaitToFlipBack)
        return;

    if (SDL_GetTicks() < _finishJudgeTime) 
        return;

    _status = Idle;
    _firstFlipCard->flip();
    _secondFlipCard->flip();
}