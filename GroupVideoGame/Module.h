#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

#define DIMENSIONS 2

class Player //��������, ��, ����, �� �����������
{
public:
	static int hp;
	static int score; //score - ��� �����
	//static int damage;
	static int player_position[DIMENSIONS];
	Texture player_texture;

	virtual void UpdatePosition() = 0;
	void UpdateScore();
	int UpdateLives(int delta_health);
};

class Player1 : public Player //����������� ��������
{
public:
	void UpdatePosition();
	Player1()
	{
		player_texture.loadFromImage.loadFromFile("player_1.png");
	}
};
class Player2 : public Player //��������� ��������
{
public:
	void UpdatePosition();
	Player2()
	{
		player_texture.loadFromImage.loadFromFile("player_2.png");
	}
};
class Player3 : public Player //���������
{
public:
	void UpdatePosition();
	Player3()
	{
		player_texture.loadFromImage.loadFromFile("player_3.png");
	}
};
class Player4 : public Player //�����
{
public:
	void UpdatePosition();
	Player4()
	{
		player_texture.loadFromImage.loadFromFile("player_4.png");
	}
};

class Game
{
public:
	void Graphics(Player* pl);
	bool Is_player_dead(int hp);
};

class Map
{
public:
	Texture map_texture;
	//��������� ��������� ����� � ������
};

class Map1 : public Map //����������� ��������
{
public:

};
class Map2 : public Map //��������� ��������
{
public:

};
class Map3 : public Map //���������
{
public:

};
class Map4 : public Map //�����
{
public:

};
int Player::hp = 100;
int Player::player_position[DIMENSIONS] = {0, 0};
int Player::score = 0;