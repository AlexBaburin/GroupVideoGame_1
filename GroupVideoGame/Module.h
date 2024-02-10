#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace sf;

#define DIMENSIONS 2
#define OBJ_NUMBER 5
#define FIELD_OF_SIGHT 200

#define WARRIOR_HP 150
#define WARRIOR_WIDTH 100
#define WARRIOR_HIGHT 125
#define WARRIOR_AVERAGE_DAMAGE 15

#define BOSS_WIDTH 110
#define BOSS_HIGHT 110
#define BOSS_AVERAGE_DAMAGE 25

#define TANK_HP 350
#define TANK_WIDTH 90
#define TANK_HIGHT 100
#define TANK_AVERAGE_DAMAGE 7

extern int RESOLUTION;
extern int PLAYER_HIGHT;
extern int PLAYER_WIDTH;
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
	Text lives;
	Font font;
	Player()
	{
		font.loadFromFile("Text.ttf");
		lives.setFillColor(Color::Red);
		lives.setString("HP:" + std::to_string(hp));
		lives.setFont(font);
		lives.setCharacterSize(10);
		lives.setPosition(player_position.x + PLAYER_WIDTH / 6, player_position.y - 10);
	}

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
	Sprite map_sprite;
	Texture map_texture, objects_texture, collisions_texture;
public:
	std::vector<Sprite> objects_sprite;
	std::vector<Sprite> collisions_sprite;
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
		map_texture.loadFromFile("Room1_floor.png");
		objects_texture.loadFromFile("time.png");
		collisions_texture.loadFromFile("wall.png");
		map_sprite.setTexture(map_texture);
		map_sprite.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
		Sprite tmp;
		tmp.setTexture(objects_texture);
		for (int i = 0; i < (rand() % OBJ_NUMBER + 1); i++)
		{
			objects_sprite.push_back(tmp);
			objects_sprite[i].setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
		}
	}
	void draw_map(RenderWindow& window)
	{
		map_sprite.setPosition(position.x, position.y);
		window.draw(map_sprite);
	}
	//void GenerateRandomScores();
};
class Map2 : public Map //векторное движение
{
public:
	Map2()
	{
		map_texture.loadFromFile("Room2_floor.png");
		objects_texture.loadFromFile("time.png");
		collisions_texture.loadFromFile("");
		map_sprite.setTexture(map_texture);
		map_sprite.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
		Sprite tmp;
		tmp.setTexture(objects_texture);
		for (int i = 0; i < (rand() % OBJ_NUMBER + 1); i++)
		{
			objects_sprite.push_back(tmp);
			objects_sprite[i].setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
		}
	}
	void draw_map(RenderWindow& window)
	{
		map_sprite.setPosition(position.x, position.y);
		window.draw(map_sprite);
	}
	//void GenerateRandomScores();
};
class Map3 : public Map //невидимка
{
public:
	Map3()
	{
		map_texture.loadFromFile("Room3_floor.png");
		objects_texture.loadFromFile("coin.png");
		collisions_texture.loadFromFile("");
		map_sprite.setTexture(map_texture);
		map_sprite.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
		Sprite tmp;
		tmp.setTexture(objects_texture);
		for (int i = 0; i < (rand() % OBJ_NUMBER + 1); i++)
		{
			objects_sprite.push_back(tmp);
			objects_sprite[i].setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
		}
	}
	void draw_map(RenderWindow& window)
	{
		map_sprite.setPosition(position.x, position.y);
		window.draw(map_sprite);
	}
	//void GenerateRandomScores();
};
class Map4 : public Map //враги
{
public:
	Map4()
	{
		map_texture.loadFromFile("Room4_Boss_floor.png");
		objects_texture.loadFromFile("");
		collisions_texture.loadFromFile("");
		map_sprite.setTexture(map_texture);
		map_sprite.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
		Sprite tmp;
		tmp.setTexture(objects_texture);
		for (int i = 0; i < (rand() % OBJ_NUMBER + 1); i++)
		{
			objects_sprite.push_back(tmp);
			objects_sprite[i].setScale(RESOLUTION/1200.0, RESOLUTION / 1200.0);
		}
	}
	void draw_map(RenderWindow& window)
	{
		map_sprite.setPosition(position.x, position.y);
		window.draw(map_sprite);
	}
};
class Enemy
{
public:
	Sprite enemy_sprite;
	Texture enemy_texture;
	Font font;
	Text lives;
	Clock time;
	int hp;
	int damage;
	int field_of_sight;
	double time_of_frame;
	bool flag;
	bool toggle;
	bool death;
	int ratio;
	int delay;
	std::vector <std::string> NamesImagesWarrior = { "Hell-Monster-Sprite-Boss-Minion-getDamage.png" , "Hell-Monster-Sprite-Boss-Minion-Attack.png",
		"Hell-Monster-Sprite-Boss-Minion.png", "Hell-Monster-Sprite-Boss-Minion-death.png" };
	std::vector <std::string> NamesImagesTank = { "Mob2-Sprite-Hurt.png" , "Mob2-Sprite-Atack1.png",
		"Mob2-Sprite-Idle.png", "Mob2-Sprite-Death.png" };
	std::vector <std::string> NamesImagesBoss = { "Hell-Boss-Sprite-Damage.png" , "Hell-Boss-Sprite-Atack.png",
		"Hell-Boss-Sprite-Stand.png", "Hell-Boss-Sprite-Death.png" };
	int index;
	int prev_index;
	Coordinates player_position;
public:
	virtual void Fight(Player* player, Enemy* enemy) = 0;
	virtual void GenerateRandomPosition(Map* map[]) = 0;
	virtual void DeathEnemy(Enemy* enemy) = 0;
	virtual int GetRandomDamage() = 0;
	int UpdateLives(int delta_health);
};
class Warrior : public Enemy
{
public:

	Warrior(Map* map[])
	{
		enemy_texture.loadFromFile(NamesImagesWarrior[0], IntRect(0, 0, WARRIOR_WIDTH, WARRIOR_HIGHT));
		enemy_sprite.setTexture(enemy_texture);
		GenerateRandomPosition(map);
		enemy_sprite.setPosition(Vector2f(player_position.x, player_position.y));
		enemy_sprite.setOrigin(Vector2f(WARRIOR_WIDTH / 2, WARRIOR_HIGHT / 2));
		hp = WARRIOR_HP;
		font.loadFromFile("Text.ttf");
		lives.setFillColor(Color::Red);
		lives.setString("HP:" + std::to_string(hp));
		lives.setFont(font);
		lives.setCharacterSize(10);
		lives.setPosition(player_position.x - 10, player_position.y - 50);
		damage = WARRIOR_AVERAGE_DAMAGE;
		field_of_sight = FIELD_OF_SIGHT * RESOLUTION / 1200.0;
		time_of_frame = 4.01;
		delay = 0;
		ratio = 0;
		index = prev_index = 1;
		flag = false;
		toggle = true;
		death = false;
	}
	void Fight(Player* player, Enemy* enemy);
	void DeathEnemy(Enemy* enemy);
	void GenerateRandomPosition(Map* map[]);
	bool CheckPosition();
	int GetRandomDamage();
};
class Tank : public Enemy
{
public:
	Tank(Map* map[])
	{
		enemy_texture.loadFromFile(NamesImagesTank[0], IntRect(0, 0, BOSS_WIDTH, BOSS_HIGHT));
		enemy_sprite.setTexture(enemy_texture);
		GenerateRandomPosition(map);
		enemy_sprite.setPosition(Vector2f(player_position.x, player_position.y));
		enemy_sprite.setOrigin(Vector2f(BOSS_WIDTH / 2, BOSS_HIGHT / 2));
		hp = TANK_HP;
		font.loadFromFile("Text.ttf");
		lives.setFillColor(Color::Red);
		lives.setString("HP:" + std::to_string(hp));
		lives.setFont(font);
		lives.setCharacterSize(10);
		lives.setPosition(player_position.x - 10, player_position.y - 50);
		damage = BOSS_AVERAGE_DAMAGE;
		field_of_sight = FIELD_OF_SIGHT * RESOLUTION / 1200.0;
		time_of_frame = 4.01;
		delay = 0;
		ratio = 0;
		index = prev_index = 1;
		flag = false;
		toggle = true;
		death = false;
	}
	void Fight(Player* player, Enemy* enemy);
	void DeathEnemy(Enemy* enemy);
	void GenerateRandomPosition(Map* map[]);
	bool CheckPosition();
	int GetRandomDamage();
};
class Boss : public Enemy
{
public:
	Boss(Map* map[])
	{
		enemy_texture.loadFromFile(NamesImagesBoss[0], IntRect(0, 0, BOSS_WIDTH, BOSS_HIGHT));
		enemy_sprite.setTexture(enemy_texture);
		GenerateRandomPosition(map);
		enemy_sprite.setPosition(Vector2f(player_position.x, player_position.y));
		enemy_sprite.setOrigin(Vector2f(BOSS_WIDTH / 2, BOSS_HIGHT / 2));
		hp = RESOLUTION;
		font.loadFromFile("Text.ttf");
		lives.setFillColor(Color::Red);
		lives.setString("HP:" + std::to_string(hp));
		lives.setFont(font);
		lives.setCharacterSize(10);
		lives.setPosition(player_position.x - 10, player_position.y - 50);
		damage = BOSS_AVERAGE_DAMAGE;
		field_of_sight = FIELD_OF_SIGHT * RESOLUTION / 1200.0;
		time_of_frame = 4.01;
		delay = 0;
		ratio = 0;
		index = prev_index = 1;
		flag = false;
		toggle = true;
		death = false;
	}
	void Fight(Player* player, Enemy* enemy);
	void DeathEnemy(Enemy* enemy);
	void GenerateRandomPosition(Map* map[]);
	bool CheckPosition();
	int GetRandomDamage();
};

class Game
{
public:
	void Graphics(RenderWindow& window, Player* player, Map* map[], Enemy* enemy, Enemy* boss, Enemy* tank);
	bool Is_player_dead(int hp, int score);
};