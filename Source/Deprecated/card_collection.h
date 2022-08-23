#ifndef YUUTA_CARD_COLLECTION_H
#define YUUTA_CARD_COLLECTION_H
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Card.h"
using namespace std;

namespace YuutaGame{
    enum CardCollectionStatus {
        Idle, WaitSecondCard, WaitToFlipBack, Finished
    };

    class CardCollection {
        private:
            vector<Card> _cards;
            CardCollectionStatus _status;
            Card* _firstFlipCard;
            Card* _secondFlipCard;
            Uint32 _finishJudgeTime;

            int _flipTimes;

        public:
            static const int JUDGE_DURATION = 1000;

            CardCollection(
                const vector<string>& cardTexts,
                int screenWidth,
                int screenHeight);
            ~CardCollection();

            void update(SDL_Event* event);
            void draw(SDL_Renderer* renderer);
    };
}
#endif