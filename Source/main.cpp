#include <memory.h>
#include "draw_card_game.h"
using Yuuta::DrawCardGame;
using std::make_shared;

int main(int argc, char* args[]){
	auto game = make_shared<DrawCardGame>("Draw Card", 800, 600);
	game->run();
}