#include <iostream>
#include "Module.h"
using namespace sf;

#define resolution 800

int Player::UpdateLives(int delta_health) //delta_health: положительное - исцеление, отрицательное - урон
{
    hp += delta_health;
    return hp;
}
void Player::UpdateScore()
{
    score += value; //value описать
}
void Player1::UpdatePosition()
{

}
bool Game::Is_player_dead(int hp)
{
    if (hp <= 0)
        return true;
    return false;
}

int main()
{
    Game game;
    Player* pl;
    Event event;
    RenderWindow win(VideoMode(resolution, resolution), "Video game");
    while (win.isOpen())
    {
        pl->UpdatePosition(); //вывод новой позиции при нажатии клавиши, проверка пересечения 
                              //границ 4-х зон и границ карты (вызывает update lives когда мёртв).

        game.Graphics(pl);
    }

    return 0;
}