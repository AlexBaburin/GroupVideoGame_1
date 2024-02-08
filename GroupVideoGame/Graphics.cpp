#include "Module.h"
#include "Graphics.h"
using namespace sf;


void draw_player(Player* player, RenderWindow& window)
{
	
}
void draw_lives(Player* player, int delta_health, RenderWindow& window)
{
	player->UpdateLives(delta_health);
}
void draw_score(Player* player, RenderWindow& window)
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
	int delta_health = 1;
	draw_player(player, window);
	draw_lives(player, delta_health, window);
	draw_score(player, window);
	draw_full_map(window, map); //отрисовка всей карты
}