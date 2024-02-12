#pragma once
#include "Module.h"
using namespace sf;

void draw_player(Player* player, RenderWindow& window, bool flag_attack);
void draw_lives(Player* player, int delta_health, RenderWindow& window);
void draw_score(RenderWindow& window, Text scoreText);
void draw_full_map(RenderWindow& window, Map* map[]);
void draw_bonuses(RenderWindow& window, Map* map[]);
void draw_border(RenderWindow& window, Sprite& border);
void draw_enemy(Enemy* enemy, RenderWindow& window, int delta_health);