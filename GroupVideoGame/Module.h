#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

using namespace sf;

#define DIMENSIONS 2
#define OBJ_NUMBER 5
#define RESOLUTION 1200
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

	virtual void UpdatePosition(RenderWindow& window, Event& event) = 0;
	virtual bool CheckPosition() = 0;
	void UpdateScore();
	int UpdateLives(int delta_health);
	bool IsPlayerOutOfBounds();
};
class Player1 : public Player //����������� ��������
{
public:
	Player1()
	{
		player_texture.loadFromFile("player_1.png");
	}
	void UpdatePosition(RenderWindow& window, Event& event);
	bool CheckPosition(); //�������� ������� �������
};
class Player2 : public Player //��������� ��������
{
public:
	void UpdatePosition(RenderWindow& window, Event& event);
	bool CheckPosition();
	Player2()
	{
		player_texture.loadFromFile("player_2.png");
	}
};
class Player3 : public Player //���������
{
public:
	void UpdatePosition(RenderWindow& window, Event& event);
	bool CheckPosition();
	Player3()
	{
		player_texture.loadFromFile("player_3.png");
	}
};
class Player4 : public Player //�����
{
public:
	void UpdatePosition(RenderWindow& window, Event& event);
	bool CheckPosition();
	Player4()
	{
		player_texture.loadFromFile("player_4.png");
	}
};

class Map
{
protected:
	Sprite map_sprite, objects_sprite, collisions_sprite;
	Texture map_texture, objects_texture, collisions_texture;
public:
	RectangleShape objects[OBJ_NUMBER];
	virtual void draw_map(RenderWindow& window) = 0; //��������� �����
	//��������� ��������� ����� � ������
	//virtual void GenerateRandomScores() = 0;
	void GenerateEnemy();
};

class Map1 : public Map //����������� ��������
{
public:
	Map1()
	{
		map_texture.loadFromFile("Map1.png");
		objects_texture.loadFromFile("");
		collisions_texture.loadFromFile("");
		map_sprite.setTexture(map_texture);
		objects_sprite.setTexture(objects_texture);
		collisions_sprite.setTexture(collisions_texture);
		map_sprite.setPosition(0, RESOLUTION / 2);
	}
	void draw_map(RenderWindow& window)
	{
		map_sprite.setPosition(0, RESOLUTION / 2);
		window.draw(map_sprite);
		//window.draw(objects_sprite);
		//window.draw(collisions_sprite);
	}
	//void GenerateRandomScores();
};
class Map2 : public Map //��������� ��������
{
public:
	Map2()
	{
		map_texture.loadFromFile("Map2.png");
		objects_texture.loadFromFile("");
		collisions_texture.loadFromFile("");
		map_sprite.setTexture(map_texture);
		objects_sprite.setTexture(objects_texture);
		collisions_sprite.setTexture(collisions_texture);
	}
	void draw_map(RenderWindow& window)
	{
		map_sprite.setPosition(RESOLUTION / 2, RESOLUTION / 2);
		window.draw(map_sprite);
		window.draw(objects_sprite);
		window.draw(collisions_sprite);
	}
	//void GenerateRandomScores();
};
class Map3 : public Map //���������
{
public:
	Map3()
	{
		map_texture.loadFromFile("Map3.png");
		objects_texture.loadFromFile("");
		collisions_texture.loadFromFile("");
		map_sprite.setTexture(map_texture);
		objects_sprite.setTexture(objects_texture);
		collisions_sprite.setTexture(collisions_texture);
	}
	void draw_map(RenderWindow& window)
	{
		map_sprite.setPosition(0, 0);
		window.draw(map_sprite);
		window.draw(objects_sprite);
		window.draw(collisions_sprite);
	}
	//void GenerateRandomScores();
};
class Map4 : public Map //�����
{
public:
	Map4()
	{
		map_texture.loadFromFile("Map4.png");
		objects_texture.loadFromFile("");
		collisions_texture.loadFromFile("");
		map_sprite.setTexture(map_texture);
		objects_sprite.setTexture(objects_texture);
		collisions_sprite.setTexture(collisions_texture);
	}
	void draw_map(RenderWindow& window)
	{
		map_sprite.setPosition(RESOLUTION / 2, 0);
		window.draw(map_sprite);
		window.draw(objects_sprite);
		window.draw(collisions_sprite);
	}
};
int Player::hp = 100;
Coordinates Player::player_position = { 0, 0 };
int Player::score = 100;
class Enemy
{
public:
	Sprite enemy_sprite;
	Texture enemy_texture;
	int hp;
	int damage;
	int field_of_sight;
	double time_of_frame;
	Coordinates player_position;
public:
	virtual void Fight(Player* player) = 0;
	virtual void GenerateRandomPosition() = 0;
	bool CheckPosition();
};
class Warrior : public Enemy
{
private:
	int Enemy::hp = 100;
	int Enemy::damage = 10;
	int Enemy::field_of_sight = 100;
	double Enemy::time_of_frame = 6;
public:
	Warrior()
	{
		enemy_texture.loadFromFile("");
		enemy_sprite.setTexture(enemy_texture);
	}
	void Fight(Player* player);
	void GenerateRandomPosition();
};
void Warrior::Fight(Player* player)
{
	if (time_of_frame > 6)
		time_of_frame -= 6;
	else
		time_of_frame += 0.005;
	if ((player->player_position.x - Enemy::player_position.x <= Enemy::field_of_sight) &&
		(player->player_position.y - Enemy::player_position.y <= Enemy::field_of_sight))
	{
		enemy_sprite.setTextureRect(IntRect(PLAYER_WIDTH * time_of_frame + PLAYER_WIDTH, PLAYER_HIGHT, PLAYER_WIDTH, PLAYER_HIGHT));
		if ((player->player_position.x - Enemy::player_position.x <= Enemy::field_of_sight / 10) &&
			(player->player_position.y - Enemy::player_position.y <= Enemy::field_of_sight / 10) && time_of_frame == 3)
			player->UpdateLives(-Enemy::damage);
	}
	else
		enemy_sprite.setTextureRect(IntRect(PLAYER_WIDTH * time_of_frame + PLAYER_WIDTH, PLAYER_HIGHT, PLAYER_WIDTH, PLAYER_HIGHT));
}
bool Warrior::Enemy::CheckPosition()
{
	if ((player_position.x >= RESOLUTION / 2) && (player_position.x <= RESOLUTION - PLAYER_WIDTH))
		if ((player_position.y <= RESOLUTION / 2 - PLAYER_HIGHT))
			return true;
	return false;
}
void Warrior::GenerateRandomPosition()
{
	do
	{
		Enemy::player_position.x = rand() % (RESOLUTION / 2) + RESOLUTION;
		Enemy::player_position.y = rand() % (RESOLUTION / 2) + PLAYER_HIGHT;
	} while (!Enemy::CheckPosition());
}
class Witcher : public Enemy
{

};
class Bomber : public Enemy
{

};
