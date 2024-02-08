#include "Module.h"
#include "Graphics.h"
using namespace sf;


void draw_player(Player* player)
{
	player->UpdatePosition();
	//drawrect или drawsprite и тд (pl->player_position[0], pl->player_position[1]);
}
void draw_lives(Player* player, int delta_health)
{
	player->UpdateLives(delta_health);
}
void draw_score(Player* player)
{
	player->UpdateScore();
}
void draw_full_map(RenderWindow& window, Map* map[])
{
	//отрисовка 4-х текстур классов Map
	for (int i = 0; i < NUMBER_OF_LOCATIONS; i++)
		map[i]->draw_map(window);
}

void Game::Graphics(RenderWindow& window, Player* player, Map* map[])
{
	int delta_health;
	draw_player(player);
	draw_lives(player, delta_health);
	draw_score(player);
	draw_full_map(window, map); //отрисовка всей карты
}

