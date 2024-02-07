#include "Module.h"
#include "Graphics.h"
using namespace sf;


void draw_player(Player* pl, Map* m)
{
	//drawrect или drawsprite и тд (pl->player_position[0], pl->player_position[1]);
}

void draw_full_map()
{
	//отрисовка 4-х текстур классов Map
}

void Game::Graphics(Player* pl)
{
	draw_player(pl);
	draw_full_map(); //отрисовка всей карты
	draw_lives(pl);
	draw_score(pl);
}

