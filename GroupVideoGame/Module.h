#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

#define DIMENSIONS 2
#define OBJ_NUMBER 5
#define RESOLUTION 800
#define PLAYER_HIGHT 40
#define PLAYER_WIDTH 20
#define SIZE_OF_THORNS 50
#define NUMBER_OF_LOCATIONS 4
struct Coordinates
{
	int x;
	int y;
};
class Player //��������, ��, ����, �� �����������
{
public:
	static int hp;
	static int score; //score - ��� �����
	static int damage;
	//static int player_position[DIMENSIONS];
	static Coordinates player_position;
	Texture player_texture;

	virtual void UpdatePosition() = 0;
	virtual bool CheckPosition() = 0;
	void UpdateScore();
	int UpdateLives(int delta_health);
};
class Player1 : public Player //����������� ��������
{
public:
	Player1()
	{
		player_texture.loadFromImage.loadFromFile("player_1.png");
	}
	void UpdatePosition() override;
	bool CheckPosition() override; //�������� ������� �������
};
bool Player1::CheckPosition()
{
	if ((player_position.x <= RESOLUTION / 2) && player_position.y >= RESOLUTION / 2 - PLAYER_HIGHT)
		if((player_position.x >= SIZE_OF_THORNS) && (player_position.y <= RESOLUTION - SIZE_OF_THORNS))
			return true;
	return false;
}
class Player2 : public Player //��������� ��������
{
public:
	void UpdatePosition();
	bool CheckPosition() override;
	Player2()
	{
		player_texture.loadFromImage.loadFromFile("player_2.png");
	}
};
class Player3 : public Player //���������
{
public:
	void UpdatePosition();
	bool CheckPosition() override;
	Player3()
	{
		player_texture.loadFromImage.loadFromFile("player_3.png");
	}
};
class Player4 : public Player //�����
{
public:
	void UpdatePosition();
	bool CheckPosition() override;
	Player4()
	{
		player_texture.loadFromImage.loadFromFile("player_4.png");
	}
};

class Game
{
public:
	void Graphics(Player* player, Map* map[]); //��������� ������, �����, �������� � �.�.
	bool Is_player_dead(int hp, int score);
};

class Map
{
public:
	Texture map_texture;
	RectangleShape objects[OBJ_NUMBER];
	virtual void draw_map(); //��������� �����
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
Coordinates Player::player_position = { 0, 0 };
int Player::score = 100;