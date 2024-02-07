#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define DIMENSIONS 2

class Game
{

};

class Player
{
protected:
	static int hp;
	static int score;
	static int player_position[DIMENSIONS];
public:
	virtual void UpdatePosition() = 0;
	virtual void UpdateScore() = 0;
	virtual void UpdateLives() = 0;
	virtual void DealDamage() = 0;
};

class Map1
{

};
class Map2
{

};
class Map3
{

};
class Map4
int Player::hp = 100;
int Player::player_position[DIMENSIONS] = {0, 0};
int Player::score = 0;