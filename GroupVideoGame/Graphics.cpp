#include "Module.h"
#include "Graphics.h"
using namespace sf;

void draw_enemy(Enemy* enemy, RenderWindow& window, int delta_health)
{
	window.draw(enemy->enemy_sprite);
	if (enemy->hp > 0)
	{
		enemy->UpdateLives(delta_health);
		enemy->lives.setPosition(enemy->player_position.x - WARRIOR_WIDTH / 2 + 15, enemy->player_position.y - WARRIOR_HIGHT / 2 - 10);
		enemy->lives.setString("HP:" + std::to_string(enemy->hp));
		window.draw(enemy->lives);
	}
}
void draw_boss(Enemy* enemy, RenderWindow& window, int delta_health)
{
	window.draw(enemy->enemy_sprite);
	if (enemy->hp > 0)
	{
		enemy->UpdateLives(delta_health);
		enemy->lives.setPosition(enemy->player_position.x - WARRIOR_WIDTH / 2 + 15, enemy->player_position.y - WARRIOR_HIGHT / 2 - 10);
		enemy->lives.setString("HP:" + std::to_string(enemy->hp));
		window.draw(enemy->lives);
		window.draw(enemy->text_boss);
	}
}

void draw_bonuses(RenderWindow& window, Map* map[])
{
	for (int i = 0; i < NUMBER_OF_LOCATIONS; i++)
		for (int j = 0; j < map[i]->objects_sprite.size(); j++)
			window.draw(map[i]->objects_sprite[j]);
	for (int i = 0; i < NUMBER_OF_LOCATIONS; i++)
		for (int j = 0; j < map[i]->collisions_sprite.size(); j++)
			window.draw(map[i]->collisions_sprite[j]);
}

void draw_player(Player* player, RenderWindow& window)
{
	Sprite player_sprite(player->player_texture);
	player_sprite.setPosition(player->player_position.x, player->player_position.y);
	player_sprite.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
	window.draw(player_sprite);
}
void draw_lives(Player* player, int delta_health, RenderWindow& window)
{
	player->UpdateLives(delta_health);
	player->lives.setPosition(player->player_position.x + PLAYER_WIDTH / 2, player->player_position.y - 10);
	player->lives.setString("HP:" + std::to_string(player->hp));
	window.draw(player->lives);
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
void Enemy_radius(RenderWindow& window, Enemy* enemy)
{
	if (enemy->hp > 0)
	{
		CircleShape board(RESOLUTION / 6, 400), fieldDamage(RESOLUTION / 12, 400);
		board.setFillColor(Color(0, 0, 0, 50));
		fieldDamage.setFillColor(Color(255, 0, 0, 50));
		board.setOrigin(RESOLUTION / 6, RESOLUTION / 6);
		fieldDamage.setOrigin(RESOLUTION / 12, RESOLUTION / 12);
		board.setPosition(Vector2f(enemy->player_position.x, enemy->player_position.y));
		fieldDamage.setPosition(Vector2f(enemy->player_position.x, enemy->player_position.y));
		window.draw(board);
		window.draw(fieldDamage);
	}
}
void Game::Graphics(RenderWindow& window, Player* player, Map* map[], Enemy* enemy, Enemy* boss, Enemy* tank)
{
	window.clear();
	int delta_health = 0;
	draw_full_map(window, map); //отрисовка всей карты
	//вычисления для врагов
	Enemy_radius(window, enemy);
	Enemy_radius(window, boss);
	Enemy_radius(window, tank);

	enemy->DeathEnemy(enemy);
	boss->DeathEnemy(boss);
	tank->DeathEnemy(tank);

	enemy->Fight(player, enemy);
	boss->Fight(player, boss);
	tank->Fight(player, tank);
	//отрисовка игрока и врагов
	draw_player(player, window);
	draw_enemy(enemy, window, delta_health);
	draw_enemy(tank, window, delta_health);
	draw_boss(boss, window, delta_health);
	draw_bonuses(window, map);
	draw_lives(player, delta_health, window);
	//draw_score(player, window);
	window.display();
}