#ifndef YUUTA_CARD_COLLECTION_H
#define YUUTA_CARD_COLLECTION_H
#include <iostream>
#include <memory>
#include <vector>
#include <SDL.h>
#include "card.h"
using std::function;
using std::string;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;
using GameCore::GameObject;

namespace Yuuta {
    namespace GameObjects {
        enum CardCollectionStatus {
            Idle, WaitSecondCard, WaitToFlipBack, Finished
        };

        class CardCollection : public GameObject {
            private:
                vector<shared_ptr<Card>> _cards;
                CardCollectionStatus _status;
                Card* _firstFlipCard;
                Card* _secondFlipCard;
                Uint32 _finishJudgeTime;

            public:
                CardCollection(
                    SDL_Rect range,
                    const vector<string>& cardTexts,
                    function<void()> onFlipTwoCards);

                virtual void update();
        };
    }
}
#endif
