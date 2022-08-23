#include "draw_card_game.h"
using Yuuta::DrawCardGame;

int main(int argc, char* args[]){
	auto game = DrawCardGame("Draw Card", 800, 600);
	game.run();
}