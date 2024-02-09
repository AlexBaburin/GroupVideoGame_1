#include <iostream>
#include <vector>
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
void Warrior::GenerateRandomPosition(Map* map[])
{
    player_position.x = rand() % (RESOLUTION / 2 - PLAYER_WIDTH) + map[3]->position.x;
    player_position.y = rand() % (RESOLUTION / 2 - PLAYER_HIGHT) + map[3]->position.y;
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
            prev_event = Keyboard::Up;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
            prev_event = Keyboard::Down;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
            prev_event = Keyboard::Left;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player_position.x += SPEED;
            prev_event = Keyboard::Right;
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
            prev_event = Keyboard::Up;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
            prev_event = Keyboard::Down;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
            prev_event = Keyboard::Left;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player_position.x += SPEED;
            prev_event = Keyboard::Right;
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
            prev_event = Keyboard::Up;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
            prev_event = Keyboard::Down;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
            prev_event = Keyboard::Left;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player_position.x += SPEED;
            prev_event = Keyboard::Right;
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

void GenerateRandomPosition(Player* player, Map* map[])
{
    player->player_position.x = rand() % (RESOLUTION / 2 - PLAYER_WIDTH) + map[0]->position.x;
    player->player_position.y = rand() % (RESOLUTION / 2 - PLAYER_HIGHT) + map[0]->position.y;
}

void IsBonusPickedUp(Player* player, Map* map[])
{
    FloatRect rect1(player->player_position.x, player->player_position.y, PLAYER_WIDTH, PLAYER_HIGHT);
    std::vector<FloatRect> rect2[NUMBER_OF_LOCATIONS];
    for (int i = 0; i < NUMBER_OF_LOCATIONS; i++)
        for (int j = 0; j < map[i]->objects_sprite.size(); j++)
        {
            rect2[i].push_back(FloatRect(map[i]->objects_sprite[j].getPosition().x, map[i]->objects_sprite[j].getPosition().y,
                map[i]->objects_sprite[j].getTexture()->getSize().x, map[i]->objects_sprite[j].getTexture()->getSize().y));
            if (rect1.intersects(rect2[i][j]))
            {
                player->UpdateScore();
                map[i]->objects_sprite.erase(map[i]->objects_sprite.begin() +  j);
            }
        }
}

int main()
{
    bool flag;
    bool flag_EndGame;
    do {
        flag = false;
        flag_EndGame = false;
        srand(time(NULL));
        Game game;
        Map* map[NUMBER_OF_LOCATIONS] = { new Map1(), new Map2(), new Map3(), new Map4() }; //указатель на количество локаций

        std::vector<std::vector<int>> map_randomizer = { {0,0},{0, RESOLUTION / 2}, {RESOLUTION / 2, 0}, {RESOLUTION / 2, RESOLUTION / 2} };

        for (int i = 0; i < NUMBER_OF_LOCATIONS; i++)
        {
            int j = rand() % map_randomizer.size();
            map[i]->position.x = map_randomizer[j][0];
            map[i]->position.y = map_randomizer[j][1];
            map_randomizer.erase(map_randomizer.begin() + j);
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < map[i]->objects_sprite.size(); j++)
            {
                map[i]->objects_sprite[j].setPosition(map[i]->position.x + (rand() %
                    (RESOLUTION / 2 - map[i]->objects_sprite[j].getTexture()->getSize().x)), map[i]->position.y + (rand() %
                        (RESOLUTION / 2 - map[i]->objects_sprite[j].getTexture()->getSize().y)));
                for (int k = 0; k < j; ++k)
                {
                    FloatRect rect1(map[i]->objects_sprite[j].getPosition().x - map[i]->objects_sprite[j].getTexture()->getSize().x,
                        map[i]->objects_sprite[j].getPosition().y - map[i]->objects_sprite[j].getTexture()->getSize().x,
                        map[i]->objects_sprite[j].getTexture()->getSize().x * 3,
                        map[i]->objects_sprite[j].getTexture()->getSize().y + map[i]->objects_sprite[j].getTexture()->getSize().x * 2);
                    FloatRect rect2(map[i]->objects_sprite[k].getPosition().x - map[i]->objects_sprite[k].getTexture()->getSize().x,
                        map[i]->objects_sprite[k].getPosition().y - map[i]->objects_sprite[k].getTexture()->getSize().x,
                        map[i]->objects_sprite[k].getTexture()->getSize().x * 3,
                        map[i]->objects_sprite[k].getTexture()->getSize().y + map[i]->objects_sprite[k].getTexture()->getSize().x * 2);

                    if (rect1.intersects(rect2))
                    {
                        j--;
                        break;
                    }
                }
            }
        }
        Player* Main_player = new Player1();
        Enemy* enemy = new Warrior();
        GenerateRandomPosition(Main_player, map); // генерирование случайной позиции в начальной локации
        enemy->GenerateRandomPosition(map); // генерирование случайной позиции врагов
        Clock cl, limiter, time_button, helper;
        Event event;
        Image icon;
        RenderWindow window(VideoMode(RESOLUTION, RESOLUTION), "Video game");
        icon.loadFromFile("icon.png");
        window.setIcon(128, 128, icon.getPixelsPtr()); //установка иконки игры (хз, поставил из своей игры, можете поменять)
        cl.restart();
        while (window.isOpen())
        {
            if (!game.Is_player_dead(Main_player->hp, Main_player->score)) {
                limiter.restart();
                while (limiter.getElapsedTime().asMilliseconds() <= 10)
                {
                }
                Main_player->UpdatePosition(window, event); //вывод новой позиции при нажатии клавиши, проверка пересечения 
                //границ 4-х зон и границ карты (вызывает update lives когда мёртв).
                if ((Main_player->player_position.x + PLAYER_WIDTH / 2) < (map[0]->position.x + RESOLUTION / 2) &&
                    (Main_player->player_position.x + PLAYER_WIDTH / 2) > (map[0]->position.x) &&
                    (Main_player->player_position.y + PLAYER_HIGHT / 2) < (map[0]->position.y + RESOLUTION / 2) &&
                    (Main_player->player_position.y + PLAYER_HIGHT / 2) > (map[0]->position.y) &&
                    !dynamic_cast<Player1*>(Main_player))
                {
                    delete Main_player;
                    Main_player = new Player1;
                }
                if ((Main_player->player_position.x + PLAYER_WIDTH / 2) < (map[1]->position.x + RESOLUTION / 2) &&
                    (Main_player->player_position.x + PLAYER_WIDTH / 2) > (map[1]->position.x) &&
                    (Main_player->player_position.y + PLAYER_HIGHT / 2) < (map[1]->position.y + RESOLUTION / 2) &&
                    (Main_player->player_position.y + PLAYER_HIGHT / 2) > (map[1]->position.y) &&
                    !dynamic_cast<Player2*>(Main_player))
                {
                    delete Main_player;
                    Main_player = new Player2;
                }
                if ((Main_player->player_position.x + PLAYER_WIDTH / 2) < (map[2]->position.x + RESOLUTION / 2) &&
                    (Main_player->player_position.x + PLAYER_WIDTH / 2) > (map[2]->position.x) &&
                    (Main_player->player_position.y + PLAYER_HIGHT / 2) < (map[2]->position.y + RESOLUTION / 2) &&
                    (Main_player->player_position.y + PLAYER_HIGHT / 2) > (map[2]->position.y) &&
                    !dynamic_cast<Player3*>(Main_player))
                {
                    delete Main_player;
                    Main_player = new Player3;
                }
                if ((Main_player->player_position.x + PLAYER_WIDTH / 2) < (map[3]->position.x + RESOLUTION / 2) &&
                    (Main_player->player_position.x + PLAYER_WIDTH / 2) > (map[3]->position.x) &&
                    (Main_player->player_position.y + PLAYER_HIGHT / 2) < (map[3]->position.y + RESOLUTION / 2) &&
                    (Main_player->player_position.y + PLAYER_HIGHT / 2) > (map[3]->position.y) &&
                    !dynamic_cast<Player4*>(Main_player))
                {
                    delete Main_player;
                    Main_player = new Player4;
                }
                //Main_player->UpdateScore();
                IsBonusPickedUp(Main_player, map);
                game.Graphics(window, Main_player, map, enemy); // отрисовка карты и игрока
                if (cl.getElapsedTime().asSeconds() >= 1) {
                    Main_player->score--;//обновляет таймер в секундах.
                    cl.restart();
                }
            }
            else {
                //Экран пройгрыша
                Texture Game_over_texture;
                Game_over_texture.loadFromFile("Game_over.png");
                Sprite Game_over;
                Game_over.setTexture(Game_over_texture);
                Game_over.setPosition(0, 0);

                //Инициализация кнопки и его состояний
                Texture Button_texture, Button_texture2;
                Button_texture.loadFromFile("Button1.png");//первое состояние кнопки
                Button_texture2.loadFromFile("Button2.png");//второе состояние кнопки
                Sprite Button, Button2;
                Button.setTexture(Button_texture);
                Button.setPosition(200, 800);

                //Шрифт для вывода оставшегося времени
                Font font;
                font.loadFromFile("Text.ttf");
                Text text("", font, 50);
                text.setStyle(Text::Italic);
                text.setFillColor(Color(230, 230, 230));
                text.setString(L"Оставшееся время: " + std::to_string(Main_player->score) + L" сек");
                text.setPosition(100, 600);

                //Анимация экрана окончания
                if (!flag_EndGame) {
                    RectangleShape Black_helper;
                    for (int i = 255; i >= 0; i--) {
                        helper.restart();
                        Black_helper.setFillColor(Color(0, 0, 0, i));
                        Black_helper.setSize(Vector2f(1200, 300));
                        Black_helper.setPosition(0, 100);
                        window.clear();
                        window.draw(Game_over);
                        window.draw(Black_helper);
                        Black_helper.setFillColor(Color(0, 0, 0));
                        Black_helper.setPosition(0, 400);
                        window.draw(Black_helper);
                        window.display();
                        while (helper.getElapsedTime().asMilliseconds() <= 5) {};
                    }
                    for (int i = 255; i >= 0; i--) {
                        helper.restart();
                        Black_helper.setFillColor(Color(0, 0, 0, i));
                        Black_helper.setSize(Vector2f(1200, 300));
                        Black_helper.setPosition(0, 400);
                        window.clear();
                        window.draw(Game_over);
                        window.draw(Black_helper);
                        window.display();
                        while (helper.getElapsedTime().asMilliseconds() <= 5) {};
                    }
                    flag_EndGame=true;
                }

                window.clear();
                window.draw(Game_over);
                window.draw(text);
                window.draw(Button);
                window.display();
                //Обработка нажатия кнопки + перезапуск игры
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        window.close();
                    }
                    else if (event.type == Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == Mouse::Left)
                        {
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;
                            if (Button.getGlobalBounds().contains(x, y)) {
                                Button2.setTexture(Button_texture2);
                                Button2.setPosition(200, 800);

                                window.clear();
                                window.draw(Game_over);
                                window.draw(text);
                                window.draw(Button2);
                                window.display();
                                time_button.restart();
                                while (time_button.getElapsedTime().asMilliseconds() <= 200) {};
                                Main_player->hp = 100;
                                Main_player->score = 100;
                                Main_player->player_position = { 0,0 };
                                flag = true;
                                break;
                            }
                        }
                    }
                }
                if (flag)break;
            }
        }
    } while (flag);

    return 0;
}