﻿#include <iostream>
#include "Module.h"
#include "Graphics.h"
using namespace sf;

#define SPEED 5

int Player::hp = 100;
Coordinates Player::player_position = { 0, 0 };
int Player::score = 100;
Keyboard::Key prev_event = Keyboard::Key::T;

void Warrior::Fight(Player* player)
{
    if (time_of_frame > 6)
        time_of_frame -= 6;
    else
        time_of_frame += 0.005;
    if ((player->player_position.x - player_position.x <= field_of_sight) &&
        (player->player_position.y - player_position.y <= field_of_sight))
    {
        enemy_sprite.setTextureRect(IntRect(PLAYER_WIDTH * time_of_frame + PLAYER_WIDTH, PLAYER_HIGHT, PLAYER_WIDTH, PLAYER_HIGHT));
        if ((player->player_position.x - player_position.x <= field_of_sight / 10) &&
            (player->player_position.y - player_position.y <= field_of_sight / 10) && time_of_frame == 3)
            player->UpdateLives(-damage);
    }
    else
        enemy_sprite.setTextureRect(IntRect(PLAYER_WIDTH * time_of_frame + PLAYER_WIDTH, PLAYER_HIGHT, PLAYER_WIDTH, PLAYER_HIGHT));
}
bool Warrior::CheckPosition()
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
        player_position.x = rand() % (RESOLUTION / 2) + RESOLUTION;
        player_position.y = rand() % (RESOLUTION / 2) + PLAYER_HIGHT;
    } while (!CheckPosition());
}

bool Player1::CheckPosition()
{
    if ((player_position.x <= RESOLUTION / 2) && player_position.y >= RESOLUTION / 2 - PLAYER_HIGHT)
        if ((player_position.x >= SIZE_OF_THORNS) && (player_position.y <= RESOLUTION - SIZE_OF_THORNS))
            return true;
    return false;
}
int Player::UpdateLives(int delta_health) //delta_health: положительное - исцеление, отрицательное - урон
{
    hp += delta_health;
    return hp;
}
void Player::UpdateScore()
{
    score += 10; //value описать
}
bool Player::IsPlayerOutOfBounds()
{
    if (player_position.x > 0 && player_position.x < RESOLUTION && player_position.y > 0 && player_position.y < RESOLUTION)
        return false;
    return true;
}
void Player1::UpdatePosition(RenderWindow& window, Event& event)
{
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
        {
            player_position.y -= SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player_position.x += SPEED;
        }
    }
    if (IsPlayerOutOfBounds())
    {
        UpdateLives(-1000);
    }
}
void Player2::UpdatePosition(RenderWindow& window, Event& event)
{
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
        {
            prev_event = Keyboard::Up;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            prev_event = Keyboard::Down;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            prev_event = Keyboard::Left;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            prev_event = Keyboard::Right;
        }
    }
    if (prev_event == Keyboard::Up)
    {
        player_position.y -= SPEED;
    }
    else if (prev_event == Keyboard::Down)
    {
        player_position.y += SPEED;
    }
    else if (prev_event == Keyboard::Left)
    {
        player_position.x -= SPEED;
    }
    else if (prev_event == Keyboard::Right)
    {
        player_position.x += SPEED;
    }
    if (IsPlayerOutOfBounds())
    {
        UpdateLives(-1000);
    }
}
void Player3::UpdatePosition(RenderWindow& window, Event& event)
{
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
        {
            player_position.y -= SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player_position.x += SPEED;
        }
    }
    if (IsPlayerOutOfBounds())
    {
        UpdateLives(-1000);
    }
}
void Player4::UpdatePosition(RenderWindow& window, Event& event)
{
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
        {
            player_position.y -= SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player_position.x += SPEED;
        }
    }
    if (IsPlayerOutOfBounds())
    {
        UpdateLives(-1000);
    }
}

bool Game::Is_player_dead(int hp, int score)
{
    if (hp <= 0 || score <= 0)
        return true;
    return false;
}

void GenerateRandomPosition(Player* player)
{
    do
    {
        player->player_position.x = rand() % (RESOLUTION / 2) - PLAYER_WIDTH;
        player->player_position.y = rand() % (RESOLUTION / 2) + RESOLUTION / 2;
    } while (!player->CheckPosition());
}

int main()
{
    srand(time(NULL));
    Game game;
    Map* map[NUMBER_OF_LOCATIONS] = { new Map1(), new Map2(), new Map3(), new Map4() }; //указатель на количество локаций
    Player* Main_player = new Player1();
    Enemy* enemy = new Warrior();
    GenerateRandomPosition(Main_player); // геенерирование случайной позиции в начальной локации
    Clock cl, limiter;
    Event event;
    Image icon;
    RenderWindow window(VideoMode(RESOLUTION, RESOLUTION), "Video game");
    icon.loadFromFile("icon.png");
    window.setIcon(128, 128, icon.getPixelsPtr()); //установка иконки игры (хз, поставил из своей игры, можете поменять)
    while (window.isOpen())
    {
        limiter.restart();
        while (limiter.getElapsedTime().asMilliseconds() <= 10)
        {
        }
        Main_player->UpdatePosition(window, event); //вывод новой позиции при нажатии клавиши, проверка пересечения 
        //границ 4-х зон и границ карты (вызывает update lives когда мёртв).
        if (Main_player->player_position.x < RESOLUTION / 2 && Main_player->player_position.y > RESOLUTION / 2 &&
            !dynamic_cast<Player1*>(Main_player))
        {
            delete Main_player;
            Main_player = new Player1;
        }
        if (Main_player->player_position.x > RESOLUTION / 2 && Main_player->player_position.y > RESOLUTION / 2 &&
            !dynamic_cast<Player2*>(Main_player))
        {
            delete Main_player;
            Main_player = new Player2;
        }
        if (Main_player->player_position.x < RESOLUTION / 2 && Main_player->player_position.y < RESOLUTION / 2 &&
            !dynamic_cast<Player3*>(Main_player))
        {
            delete Main_player;
            Main_player = new Player3;
        }
        if (Main_player->player_position.x > RESOLUTION / 2 && Main_player->player_position.y < RESOLUTION / 2 &&
            !dynamic_cast<Player4*>(Main_player))
        {
            delete Main_player;
            Main_player = new Player4;
        }
        //Main_player->UpdateScore();
        game.Graphics(window, Main_player, map, enemy); // отрисовка карты и игрока
        Main_player->score -= cl.getElapsedTime().asSeconds(); //обновляет таймер в секундах.
    }

    return 0;
}