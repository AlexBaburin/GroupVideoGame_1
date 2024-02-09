#include "Module.h"
#include "Graphics.h"
using namespace sf;

void draw_enemy(Enemy* enemy, RenderWindow& window)
{
	Sprite enemy_sprite(enemy->enemy_texture);
	enemy_sprite.setPosition(enemy->player_position.x, enemy->player_position.y);
	enemy_sprite.setScale(1, 1);
	window.draw(enemy_sprite);
}

void draw_bonuses(RenderWindow& window, Map* map[])
{
	for (int i = 0; i < NUMBER_OF_LOCATIONS; i++)
		for (int j = 0; j < map[i]->objects_sprite.size(); j++)
			window.draw(map[i]->objects_sprite[j]);
}

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

void Game::Graphics(RenderWindow& window, Player* player, Map* map[], Enemy* enemy)
{
	window.clear();
	int delta_health = 0;
	draw_full_map(window, map); //отрисовка всей карты
	draw_player(player, window);
	draw_enemy(enemy, window);
	draw_bonuses(window, map);
	draw_lives(player, delta_health, window);
	//draw_score(player, window);
	if (dynamic_cast<Player1*>(player)) {
		RectangleShape Fon_map1;
		Fon_map1.setSize(Vector2f(RESOLUTION, RESOLUTION));
		Fon_map1.setFillColor(Color(0, 200, 0, 20));
		Fon_map1.setPosition(0, 0);
		window.draw(Fon_map1);
	}
	if (dynamic_cast<Player2*>(player)) {
		RectangleShape Fon_map2;
		Fon_map2.setSize(Vector2f(RESOLUTION, RESOLUTION));
		Fon_map2.setFillColor(Color(0, 0, 200, 50));
		Fon_map2.setPosition(0, 0);
		window.draw(Fon_map2);
		window.draw(Fon_2);
	}
	if (dynamic_cast<Player3*>(player)) {
		RectangleShape Fon_map3;
		Fon_map3.setSize(Vector2f(RESOLUTION, RESOLUTION));
		Fon_map3.setFillColor(Color(100, 100, 100, 150));
		Fon_map3.setPosition(0, 0);
		window.draw(Fon_map3);
	}
	if (dynamic_cast<Player4*>(player)) {
		RectangleShape Fon_map4;
		Fon_map4.setSize(Vector2f(RESOLUTION, RESOLUTION));
		Fon_map4.setFillColor(Color(200, 0, 0, 70));
		Fon_map4.setPosition(0, 0);
		window.draw(Fon_map4);
		window.draw(Fon_4);
	}
	window.display();
}