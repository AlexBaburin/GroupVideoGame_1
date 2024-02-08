#include <iostream>
#include "Module.h"
#include "Graphics.h"
using namespace sf;

#define SPEED 1

int Player::hp = 100;
Coordinates Player::player_position = { 0, 0 };
int Player::score = 100;

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
        if (event.type == Keyboard::isKeyPressed(Keyboard::Up) || event.type == Keyboard::isKeyPressed(Keyboard::W))
        {
            player_position.y -= SPEED;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Down) || event.type == Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Left) || event.type == Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Right) || event.type == Keyboard::isKeyPressed(Keyboard::D))
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
    Event prev_event;
    while (window.pollEvent(event))
    {
        if (event.type == Keyboard::isKeyPressed(Keyboard::Up) || event.type == Keyboard::isKeyPressed(Keyboard::W))
        {
            prev_event = event;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Down) || event.type == Keyboard::isKeyPressed(Keyboard::S))
        {
            prev_event = event;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Left) || event.type == Keyboard::isKeyPressed(Keyboard::A))
        {
            prev_event = event;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Right) || event.type == Keyboard::isKeyPressed(Keyboard::D))
        {
            prev_event = event;
        }
    }
    if (prev_event.type == Keyboard::isKeyPressed(Keyboard::Up) || prev_event.type == Keyboard::isKeyPressed(Keyboard::W))
    {
        player_position.y -= SPEED;
    }
    else if (prev_event.type == Keyboard::isKeyPressed(Keyboard::Down) || prev_event.type == Keyboard::isKeyPressed(Keyboard::S))
    {
        player_position.y += SPEED;
    }
    else if (prev_event.type == Keyboard::isKeyPressed(Keyboard::Left) || prev_event.type == Keyboard::isKeyPressed(Keyboard::A))
    {
        player_position.x -= SPEED;
    }
    else if (prev_event.type == Keyboard::isKeyPressed(Keyboard::Right) || prev_event.type == Keyboard::isKeyPressed(Keyboard::D))
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
        if (event.type == Keyboard::isKeyPressed(Keyboard::Up) || event.type == Keyboard::isKeyPressed(Keyboard::W))
        {
            player_position.y -= SPEED;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Down) || event.type == Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Left) || event.type == Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Right) || event.type == Keyboard::isKeyPressed(Keyboard::D))
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
        if (event.type == Keyboard::isKeyPressed(Keyboard::Up) || event.type == Keyboard::isKeyPressed(Keyboard::W))
        {
            player_position.y -= SPEED;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Down) || event.type == Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Left) || event.type == Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
        }
        else if (event.type == Keyboard::isKeyPressed(Keyboard::Right) || event.type == Keyboard::isKeyPressed(Keyboard::D))
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
    } while (player->CheckPosition());
}
int main()
{
    srand(time(NULL));
    Game game;
    Map* map[NUMBER_OF_LOCATIONS] = { new Map1(), new Map2(), new Map3(), new Map4() }; //указатель на количество локаций
    Player* Main_player = new Player1();
    GenerateRandomPosition(Main_player); // геенерирование случайной позиции в начальной локации
    Clock cl;
    Event event;
    Image icon;
    RenderWindow window(VideoMode(RESOLUTION, RESOLUTION), "Video game");
    icon.loadFromFile("icon.png");
    window.setIcon(128, 128, icon.getPixelsPtr()); //установка иконки игры (хз, поставил из своей игры, можете поменять)
    while (window.isOpen())
    {
        Main_player->UpdatePosition(window, event); //вывод новой позиции при нажатии клавиши, проверка пересечения 
                             //границ 4-х зон и границ карты (вызывает update lives когда мёртв).
        Main_player->UpdateScore();
        game.Graphics(window, Main_player, map); // отрисовка карты и игрока
        Main_player->score -= cl.getElapsedTime().asSeconds(); //обновляет таймер в секундах.
    }

    return 0;
}