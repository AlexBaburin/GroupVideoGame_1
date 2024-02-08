#include <iostream>
#include "Module.h"
using namespace sf;

int Player::UpdateLives(int delta_health) //delta_health: положительное - исцеление, отрицательное - урон
{
    hp += delta_health;
    return hp;
}
void Player::UpdateScore()
{
    score += value; //value описать
}
void Player1::UpdatePosition(RenderWindow& window, Event& event)
{
    while (window.pollEvent(event))
    {

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