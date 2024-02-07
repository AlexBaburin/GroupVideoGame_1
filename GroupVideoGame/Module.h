#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

#define DIMENSIONS 2

class Player //движение, хп, счёт, мб невидимость
{
public:
	static int hp;
	static int score; //score - это время
	//static int damage;
	static int player_position[DIMENSIONS];
	Texture player_texture;

	virtual void UpdatePosition() = 0;
	void UpdateScore();
	int UpdateLives(int delta_health);
};

class Player1 : public Player //статическое движение
{
public:
	void UpdatePosition();
	Player1()
	{
		player_texture.loadFromImage.loadFromFile("player_1.png");
	}
};
class Player2 : public Player //векторное движение
{
public:
	void UpdatePosition();
	Player2()
	{
		player_texture.loadFromImage.loadFromFile("player_2.png");
	}
};
class Player3 : public Player //невидимка
{
public:
	void UpdatePosition();
	Player3()
	{
		player_texture.loadFromImage.loadFromFile("player_3.png");
	}
};
class Player4 : public Player //враги
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
	//рандомная генерация оцчов и врагов
};

class Map1 : public Map //статическое движение
{
public:

};
class Map2 : public Map //векторное движение
{
public:

};
class Map3 : public Map //невидимка
{
public:

};
class Map4 : public Map //враги
{
public:

};
int Player::hp = 100;
int Player::player_position[DIMENSIONS] = {0, 0};
int Player::score = 0;