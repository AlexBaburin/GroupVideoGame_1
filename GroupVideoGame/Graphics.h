#pragma once
#include "Module.h"
using namespace sf;

void draw_player(Player* player, RenderWindow& window, bool flag_attack);
void draw_lives(Player* player, int delta_health, RenderWindow& window);
void draw_score(Player* player, RenderWindow& window);
void draw_full_map(RenderWindow& window, Map* map[]);
void draw_bonuses(RenderWindow& window, Map* map[]);