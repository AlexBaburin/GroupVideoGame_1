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
class Player //движение, хп, счёт, мб невидимость
{
public:
	static int hp;
	static int score; //score - это время
	static int damage;
	//static int player_position[DIMENSIONS];
	static Coordinates player_position;
	Texture player_texture;

	virtual void UpdatePosition(RenderWindow&, Event&);
	virtual bool CheckPosition() = 0;
	void UpdateScore();
	int UpdateLives(int delta_health);
};
class Player1 : public Player //статическое движение
{
public:
	Player1()
	{
		player_texture.loadFromImage.loadFromFile("player_1.png");
	}
	void UpdatePosition(RenderWindow&, Event&);
	bool CheckPosition() override; //проверка позиции объекта
};
bool Player1::CheckPosition()
{
	if ((player_position.x <= RESOLUTION / 2) && player_position.y >= RESOLUTION / 2 - PLAYER_HIGHT)
		if((player_position.x >= SIZE_OF_THORNS) && (player_position.y <= RESOLUTION - SIZE_OF_THORNS))
			return true;
	return false;
}
class Player2 : public Player //векторное движение
{
public:
	void UpdatePosition();
	bool CheckPosition() override;
	Player2()
	{
		player_texture.loadFromImage.loadFromFile("player_2.png");
	}
};
class Player3 : public Player //невидимка
{
public:
	void UpdatePosition();
	bool CheckPosition() override;
	Player3()
	{
		player_texture.loadFromImage.loadFromFile("player_3.png");
	}
};
class Player4 : public Player //враги
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
	void Graphics(RenderWindow& window, Player* player, Map* map[]); //отрисовка игрока, карты, здоровья и т.д.
	bool Is_player_dead(int hp, int score);
};

class Map
{
protected:
	Texture* map_texture, *objects_texture, *collisions_texture;
public:
	RectangleShape objects[OBJ_NUMBER];
	virtual void draw_map(RenderWindow& window) = 0; //отрисовка карты
	//рандомная генерация очков и врагов
	virtual void GenerateRandomScores();
	void GenerateEnemy();
};

class Map1 : public Map //статическое движение
{
public:
	Map1()
	{
		map_texture = (new Texture()); map_texture->loadFromFile("");
		objects_texture = (new Texture()); objects_texture->loadFromFile("");
		collisions_texture = (new Texture()); collisions_texture->loadFromFile("");
	}
	void draw_map(RenderWindow& window)
	{
		window.draw(map_texture);
		window.draw(objects_texture);
		window.draw(collisions_texture);
	}
	void GenerateRandomScores();
};
class Map2 : public Map //векторное движение
{
public:
	Map2()
	{
		map_texture = (new Texture()); map_texture->loadFromFile("");
		objects_texture = (new Texture()); objects_texture->loadFromFile("");
		collisions_texture = (new Texture()); collisions_texture->loadFromFile("");
	}
	void draw_map(RenderWindow& window)
	{
		window.draw(map_texture);
		window.draw(objects_texture);
		window.draw(collisions_texture);
	}
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
Coordinates Player::player_position = { 0, 0 };
int Player::score = 100;