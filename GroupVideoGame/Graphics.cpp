#include "Module.h"
//#include "Graphics.h"
using namespace sf;

void draw_enemy(Enemy* enemy, RenderWindow& window, int delta_health)
{
	window.draw(enemy->enemy_sprite);
	if (enemy->hp > 0)
	{
		enemy->UpdateLives(delta_health);
		enemy->lives.setPosition(enemy->player_position.x - (WARRIOR_WIDTH / 2 - 15) * (RESOLUTION / 1200.0), enemy->player_position.y - (WARRIOR_HIGHT / 2 + 10) * (RESOLUTION / 1200.0));
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
		enemy->lives.setPosition(enemy->player_position.x - (WARRIOR_WIDTH / 2 - 15) * (RESOLUTION / 1200.0), enemy->player_position.y - (WARRIOR_HIGHT / 2 + 10) * (RESOLUTION / 1200.0));
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
}

void draw_player(Player* player, RenderWindow& window, bool flag_attack)
{
	if (flag_attack) {
		player->player_sprite.setPosition(player->player_position.x, player->player_position.y - RESOLUTION / 25);
	}
	else {
		if (Player::side == 1) player->player_sprite.setPosition(player->player_position.x, player->player_position.y);
		else player->player_sprite.setPosition(player->player_position.x + RESOLUTION / 25, player->player_position.y);
	}
	player->player_sprite.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
	window.draw(player->player_sprite);
}
void draw_lives(Player* player, int delta_health, RenderWindow& window)
{
	player->UpdateLives(delta_health);
	player->lives.setPosition(player->player_position.x + PLAYER_WIDTH / 2, player->player_position.y - 10 * (RESOLUTION / 1200.0));
	player->lives.setString("HP:" + std::to_string(player->hp));
	window.draw(player->lives);
}
void draw_score(RenderWindow& window, Text scoreText)
{
	window.draw(scoreText);
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
void draw_border(RenderWindow& window, Sprite& border)
{
	
	for (int i = 0; i < 1200.0 / SIZE_OF_THORNS; i++)
	{
		for (int j = 0; j < 1200.0 / SIZE_OF_THORNS; j++)
		{
			if ((!i && j) || (i && !j) || (!i && !j) || (i == 1200.0 / SIZE_OF_THORNS - 1 && j) || (j == 1200.0 / SIZE_OF_THORNS - 1 && i))
			{
				border.setPosition(i * SIZE_OF_THORNS * RESOLUTION / 1200.0, j * SIZE_OF_THORNS * RESOLUTION / 1200.0);
				window.draw(border);
			}
		}
	}
}
void Game::Graphics(RenderWindow& window, Player* player, Map* map[], Sprite& border, Sprite& shader, Enemy* enemy, Enemy* boss, Enemy* tank, Sound& boss_punch, bool flag_attack, Text scoreText)
{
	window.clear();
	int delta_health = 0;
	draw_full_map(window, map); //отрисовка всей карты
	draw_border(window, border); //отрисовка границы
	//вычисления для врагов
	Enemy_radius(window, enemy);
	Enemy_radius(window, boss);
	Enemy_radius(window, tank);

	enemy->DeathEnemy(enemy);
	boss->DeathEnemy(boss);
	tank->DeathEnemy(tank);

	enemy->Fight(player, enemy, boss_punch);
	boss->Fight(player, boss, boss_punch);
	tank->Fight(player, tank, boss_punch);
	//отрисовка игрока и врагов
	draw_player(player, window, flag_attack);
	draw_enemy(enemy, window, delta_health);
	draw_enemy(tank, window, delta_health);
	draw_boss(boss, window, delta_health);
	draw_bonuses(window, map);
	if (!dynamic_cast<Player3*>(player))
		draw_lives(player, delta_health, window);
	draw_score(window, scoreText);
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
	window.draw(shader);
	window.display();
}