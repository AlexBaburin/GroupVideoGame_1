#include "Module.h"
#include "Graphics.h"
using namespace sf;


void draw_player(Player* player, RenderWindow& window)
{
	Sprite player_sprite(player->player_texture);
	player_sprite.setPosition(player->player_position.x, player->player_position.y);
	player_sprite.setScale(1, 1);
	window.draw(player_sprite);
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
	window.clear();
	int delta_health = 0;
	draw_full_map(window, map); //отрисовка всей карты
	draw_player(player, window);
	draw_lives(player, delta_health, window);
	draw_score(player, window);
	window.display();
}