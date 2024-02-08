#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
class Player //движение, хп, счёт, мб невидимость
{
public:
	static int hp;
	static int score; //score - это время
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
class Player1 : public Player //статическое движение
{
public:
	Player1()
	{
		player_texture.loadFromFile("player_1.png");
	}
	void UpdatePosition(RenderWindow& window, Event& event);
	bool CheckPosition(); //проверка позиции объекта
};
class Player2 : public Player //векторное движение
{
public:
	void UpdatePosition(RenderWindow& window, Event& event);
	bool CheckPosition() { return true; }
	Player2()
	{
		player_texture.loadFromFile("player_1.png");
	}
};
class Player3 : public Player //невидимка
{
public:
	void UpdatePosition(RenderWindow& window, Event& event);
	bool CheckPosition() { return true; }
	Player3()
	{
		player_texture.loadFromFile("player_invisible.png");
	}
};
class Player4 : public Player //враги
{
public:
	void UpdatePosition(RenderWindow& window, Event& event);
	bool CheckPosition() { return true; }
	Player4()
	{
		player_texture.loadFromFile("player_1.png");
	}
};

class Map
{
protected:
	Sprite map_sprite, objects_sprite, collisions_sprite;
	Texture map_texture, objects_texture, collisions_texture;
public:
	Coordinates position;
	RectangleShape objects[OBJ_NUMBER];
	virtual void draw_map(RenderWindow& window) = 0; //отрисовка карты
	//рандомная генерация очков и врагов
	//virtual void GenerateRandomScores() = 0;
	void GenerateEnemy();
};

class Map1 : public Map //статическое движение
{
public:
	Map1()
	{
		map_texture.loadFromFile("Map1.png");
		objects_texture.loadFromFile("bonus.png");
		collisions_texture.loadFromFile("");
		map_sprite.setTexture(map_texture);
		objects_sprite.setTexture(objects_texture);
		collisions_sprite.setTexture(collisions_texture);
	}
	void draw_map(RenderWindow& window)
	{
		map_sprite.setPosition(position.x, position.y);
		window.draw(map_sprite);
		//window.draw(objects_sprite);
		//window.draw(collisions_sprite);
	}
	//void GenerateRandomScores();
};
class Map2 : public Map //векторное движение
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
		map_sprite.setPosition(position.x, position.y);
		window.draw(map_sprite);
		window.draw(objects_sprite);
		window.draw(collisions_sprite);
	}
	//void GenerateRandomScores();
};
class Map3 : public Map //невидимка
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
		map_sprite.setPosition(position.x, position.y);
		window.draw(map_sprite);
		window.draw(objects_sprite);
		window.draw(collisions_sprite);
	}
	//void GenerateRandomScores();
};
class Map4 : public Map //враги
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
		map_sprite.setPosition(position.x, position.y);
		window.draw(map_sprite);
		window.draw(objects_sprite);
		window.draw(collisions_sprite);
	}
};
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
	virtual void GenerateRandomPosition(Map* map[]) = 0;
};
class Warrior : public Enemy
{
public:
	Warrior()
	{
		enemy_texture.loadFromFile("");
		enemy_sprite.setTexture(enemy_texture);
		hp = 100;
		damage = 10;
		field_of_sight = 100;
		time_of_frame = 6;
	}
	void Fight(Player* player);
	void GenerateRandomPosition(Map* map[]);
	bool CheckPosition();
};

//class Witcher : public Enemy
//{
//
//};
//class Bomber : public Enemy
//{
//
//};

class Game
{
public:
	void Graphics(RenderWindow& window, Player* player, Map* map[], Enemy* enemy);
	bool Is_player_dead(int hp, int score);
};