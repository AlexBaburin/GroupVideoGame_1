#include "Module.h"
#include "Graphics.h"
using namespace sf;


void draw_player(Player* pl, Map* m)
{
	//drawrect ��� drawsprite � �� (pl->player_position[0], pl->player_position[1]);
}

void draw_full_map()
{
	//��������� 4-� ������� ������� Map
}

void Game::Graphics(Player* pl)
{
	draw_player(pl);
	draw_full_map(); //��������� ���� �����
	draw_lives(pl);
	draw_score(pl);
}

