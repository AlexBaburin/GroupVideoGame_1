#include <iostream>
#include <vector>
#include "Module.h"
//#include "Graphics.h"
using namespace sf;

int RESOLUTION = 1200;
int SPEED = RESOLUTION / 320;
int PLAYER_HIGHT = RESOLUTION / 12;
int PLAYER_WIDTH = int(RESOLUTION * 85.0 / 1200);
#define THROW 75
int SIZE_OF_THORNS = 50 * RESOLUTION / 1200.0;
int Player::hp = 100;
int Player::side = 1;//1=смотрит вправо; 2=смотрит влево;
Coordinates Player::player_position = { 0, 0 };
int Player::score = 30;
int Player::damage = 500;
Keyboard::Key prev_event = Keyboard::Key::T;
Keyboard::Key attack_delay = Keyboard::Key::T;

void FuncOfTrow(Player* player, Enemy* boss)
{
    if ((abs(player->player_position.y + PLAYER_HIGHT / 2 - boss->player_position.y - BOSS_HIGHT / 2) <= BOSS_HIGHT * 2) &&
        (abs(player->player_position.x + PLAYER_WIDTH / 2 - boss->player_position.x - BOSS_WIDTH / 2) >= BOSS_WIDTH))
        if ((player->player_position.x + PLAYER_WIDTH / 2 < boss->player_position.x + BOSS_WIDTH / 2))
            player->player_position.x -= THROW;
        else
            player->player_position.x += THROW;
    else
        if (abs(player->player_position.x + PLAYER_WIDTH / 2 - boss->player_position.x - BOSS_WIDTH / 2) <= BOSS_WIDTH)
            if ((player->player_position.y + PLAYER_HIGHT / 2 < boss->player_position.y + BOSS_HIGHT / 2))
                player->player_position.y -= THROW;
            else
                player->player_position.y += THROW;
}
void Boss::Fight(Player* player, Enemy* boss, Sound& boss_punch)
{
    if (time_of_frame > 4)
    {
        time_of_frame -= 4;
    }
    else
        time_of_frame += 0.05;
    Event event;
    ratio = 1.18 * BOSS_WIDTH * int(time_of_frame);
    if ((1.18 * BOSS_WIDTH * time_of_frame) > 500)
        ratio = 390;
    if (!death)
    {
        int distance_x = abs(player->player_position.x + PLAYER_WIDTH / 2 - player_position.x);
        int distance_y = abs(player->player_position.y + PLAYER_HIGHT / 2 - player_position.y);
        if (sqrt(distance_x * distance_x + distance_y * distance_y) <= field_of_sight)
        {
            if (flag)
            {
                index = 0;
                if (time_of_frame > 4)
                {
                    flag = false;
                }
            }
            else
            {
                index = 1;
            }
            if ((sqrt(distance_x * distance_x + distance_y * distance_y) <= (field_of_sight * 0.7)) && (time_of_frame > 3.96))
            {
                std::cout << "You got a damage!\n";
                if ((attack_delay == Keyboard::E) && (time.getElapsedTime().asMilliseconds() > delay))
                {
                    std::cout << "E\n";
                    flag = true;
                    delay = 10000;
                    boss->UpdateLives(-(player->damage));
                    time.restart();
                }
                if (time.getElapsedTime().asSeconds() > 2) 
                    delay = 0;
                
                if (!flag && time_of_frame > 4 && time.getElapsedTime().asSeconds() > 2)
                {
                    boss_punch.play();
                    player->UpdateLives(-GetRandomDamage());
                    FuncOfTrow(player, boss);
                }
            }
        }
        else
        {
            index = 2;
        }
    }
    else
        if (time_of_frame >= 4)
            time_of_frame = 4;
    if(prev_index != index)
        boss->enemy_texture.loadFromFile(NamesImagesBoss[index]);
    if (index == 1)
        enemy_sprite.setTextureRect(IntRect(ratio - 22, 0, BOSS_WIDTH + 20, BOSS_HIGHT + 10));
    else
        enemy_sprite.setTextureRect(IntRect(ratio, 0, BOSS_WIDTH, BOSS_HIGHT));
    enemy_sprite.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
    if (player->player_position.x > player_position.x)
        enemy_sprite.setScale(-RESOLUTION / 1200.0, RESOLUTION / 1200.0);
    prev_index = index;
}
int Boss::GetRandomDamage()
{
    return (rand() % BOSS_AVERAGE_DAMAGE) + BOSS_AVERAGE_DAMAGE / 2;
}
void Boss::DeathEnemy(Enemy* enemy)
{
    if (enemy->hp <= 0)
    {
        if (!enemy->death)
            time_of_frame = 0.01;
        enemy->death = true;
        index = 3;
    }
}
bool Boss::CheckPosition(Map* map[])
{
    //std::cout << map[3]->position.x << "   " << map[3]->position.y << std::endl;
    if ((player_position.x > map[3]->position.x) && (player_position.x + BOSS_WIDTH < map[3]->position.x + RESOLUTION ))
        if ((player_position.y + BOSS_HIGHT < map[3]->position.y + RESOLUTION) && (player_position.y > map[3]->position.y))
            return true;
    return false;
}
void Boss::GenerateRandomPosition(Map* map[])
{
    do
    {
        player_position.x = rand() % (RESOLUTION / 8 - int((BOSS_WIDTH + 10) * (RESOLUTION / 1200.0) + SIZE_OF_THORNS)) + map[3]->position.x + int(BOSS_WIDTH * (RESOLUTION / 1200.0)) + RESOLUTION / 4;
        player_position.y = rand() % (RESOLUTION / 2 - int(BOSS_HIGHT * (RESOLUTION / 1200.0) + SIZE_OF_THORNS)) + map[3]->position.y;
        //std::cout << CheckPosition(map) << "   " << player_position.x << "   " << player_position.y << std::endl;
    } while (!CheckPosition(map));
}

void Warrior::Fight(Player* player, Enemy* enemy, Sound& boss_punch)
{
    if (time_of_frame > 4)
    {
        time_of_frame -= 4;
    }
    else
        time_of_frame += 0.08;
    Event event;
    ratio = 1.5 * WARRIOR_WIDTH * int(time_of_frame);
    if ((1.5 * WARRIOR_WIDTH * time_of_frame) >= 548)
        ratio = 448;
    if (!death)
    {
        int distance_x = abs(player->player_position.x + PLAYER_WIDTH / 2 - player_position.x);
        int distance_y = abs(player->player_position.y + PLAYER_HIGHT / 2 - player_position.y);
        if (sqrt(distance_x * distance_x + distance_y * distance_y) <= field_of_sight)
        {
            if (flag)
            {
                index = 0;
                if (time_of_frame > 4)
                {
                    flag = false;
                }
            }
            else
            {
                index = 1;
            }
            if ((sqrt(distance_x * distance_x + distance_y * distance_y) <= (field_of_sight * 0.7)) && (time_of_frame > 3.96))
            {
                if (attack_delay == Keyboard::E)
                {
                    std::cout << "E\n";
                    if ((time.getElapsedTime().asMilliseconds() > delay))
                    {
                        flag = true;
                        delay = 10000;
                        enemy->UpdateLives(-(player->damage));
                        time.restart();
                    }
                }
                if (time.getElapsedTime().asSeconds() > 2)
                    delay = 0;
                if (!flag && time_of_frame > 4 && time.getElapsedTime().asSeconds() > 2)
                {
                    std::cout << "You got a damage!\n";
                    player->UpdateLives(-GetRandomDamage());
                }
            }
        }
        else
        {
            index = 2;
        }
    }
    else
        if (time_of_frame >= 4)
            time_of_frame = 4;
    if (prev_index != index)
        enemy->enemy_texture.loadFromFile(NamesImagesWarrior[index]);
    enemy_sprite.setTextureRect(IntRect(ratio, 0, WARRIOR_WIDTH, WARRIOR_HIGHT));
    enemy_sprite.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
    if (player->player_position.x > player_position.x)
        enemy_sprite.setScale(-RESOLUTION / 1200.0, RESOLUTION / 1200.0);
    prev_index = index;
}
int Warrior::GetRandomDamage()
{
    return (rand() % BOSS_AVERAGE_DAMAGE) + BOSS_AVERAGE_DAMAGE / 2;
}
void Warrior::DeathEnemy(Enemy* enemy)
{
    if (enemy->hp <= 0)
    {
        if (!enemy->death)
            time_of_frame = 0.01;
        enemy->death = true;
        index = 3;
    }
}
bool Warrior::CheckPosition(Map* map[])
{
    if ((player_position.x > map[3]->position.x) && (player_position.x + WARRIOR_WIDTH < map[3]->position.x + RESOLUTION))
        if ((player_position.y + WARRIOR_HIGHT < map[3]->position.y + RESOLUTION) && (player_position.y > map[3]->position.y))
            return true;
    return false;
}
void Warrior::GenerateRandomPosition(Map* map[])
{
    do
    {
        player_position.x = rand() % (RESOLUTION / 8 - int((WARRIOR_WIDTH + 10) * (RESOLUTION / 1200.0) + SIZE_OF_THORNS)) + map[3]->position.x + int(WARRIOR_WIDTH * (RESOLUTION / 1200.0)) + RESOLUTION / 8;
        player_position.y = rand() % (RESOLUTION / 2 - int(WARRIOR_HIGHT * (RESOLUTION / 1200.0) + SIZE_OF_THORNS)) + map[3]->position.y;
    } while (!CheckPosition(map));
}

void Tank::Fight(Player* player, Enemy* tank, Sound& boss_punch)
{
    if (time_of_frame > 4)
    {
        time_of_frame -= 4;
    }
    else
        time_of_frame += 0.05;
    Event event;
    ratio = 1.89 * TANK_WIDTH * int(time_of_frame);
    if ((1.89 * TANK_HIGHT * time_of_frame) >= 600)
        ratio = 510;
    if (!death)
    {
        int distance_x = abs(player->player_position.x + PLAYER_WIDTH / 2 - player_position.x);
        int distance_y = abs(player->player_position.y + PLAYER_HIGHT / 2 - player_position.y);
        if (sqrt(distance_x * distance_x + distance_y * distance_y) <= field_of_sight)
        {
            if (flag)
            {
                index = 0;
                if (time_of_frame > 4)
                {
                    flag = false;
                }
            }
            else
            {
                index = 1;
            }
            if ((sqrt(distance_x * distance_x + distance_y * distance_y) <= (field_of_sight * 0.7)) && (time_of_frame > 3.96))
            {
                if (attack_delay == Keyboard::E)
                {
                    std::cout << "E\n";
                    if ((time.getElapsedTime().asMilliseconds() > delay))
                    {
                        flag = true;
                        delay = 10000;
                        tank->UpdateLives(-(player->damage));
                        time.restart();
                    }
                }
                if (time.getElapsedTime().asSeconds() > 2)
                    delay = 0;
                if (!flag && time_of_frame > 4 && time.getElapsedTime().asSeconds() > 2)
                {
                    std::cout << "You got a damage!\n";
                    player->UpdateLives(-GetRandomDamage());
                }
            }
        }
        else
        {
            index = 2;
        }
    }
    else
        if (time_of_frame >= 4)
            time_of_frame = 4;
    if (prev_index != index)
        tank->enemy_texture.loadFromFile(NamesImagesTank[index]);

    if (index == 1)
        enemy_sprite.setTextureRect(IntRect(ratio - 60, 0, TANK_WIDTH + 50, TANK_HIGHT+ 50));
    else
        enemy_sprite.setTextureRect(IntRect(ratio, 0, TANK_WIDTH, TANK_HIGHT));
    if (index == 3)
        enemy_sprite.setTextureRect(IntRect(ratio + 25, 0, TANK_WIDTH + 20, TANK_HIGHT + 20));
    enemy_sprite.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
    if (player->player_position.x > player_position.x)
        enemy_sprite.setScale(-RESOLUTION / 1200.0, RESOLUTION / 1200.0);
    prev_index = index;
}
int Tank::GetRandomDamage()
{
    return (rand() % TANK_AVERAGE_DAMAGE) + TANK_AVERAGE_DAMAGE / 2;
}
void Tank::DeathEnemy(Enemy* enemy)
{
    if (enemy->hp <= 0)
    {
        if (!enemy->death)
            time_of_frame = 0.01;
        enemy->death = true;
        index = 3;
    }
}
bool Tank::CheckPosition(Map* map[])
{
    if ((player_position.x > map[3]->position.x) && (player_position.x + TANK_WIDTH < map[3]->position.x + RESOLUTION))
        if ((player_position.y + TANK_HIGHT < map[3]->position.y + RESOLUTION) && (player_position.y > map[3]->position.y))
            return true;
    return false;
}
void Tank::GenerateRandomPosition(Map* map[])
{
    do
    {
        player_position.x = rand() % (RESOLUTION / 8 - int((TANK_WIDTH + 20) * (RESOLUTION / 1200.0) + SIZE_OF_THORNS)) + map[3]->position.x + int(TANK_WIDTH * (RESOLUTION / 1200.0));
        player_position.y = rand() % (RESOLUTION / 2 - int(TANK_HIGHT * (RESOLUTION / 1200.0) + SIZE_OF_THORNS)) + map[3]->position.y;
    } while (!CheckPosition(map));
}

int Enemy::UpdateLives(int delta_health)
{
    hp += delta_health;
    return hp;
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
    if (player_position.x > SIZE_OF_THORNS - 60 * (RESOLUTION / 1200.0) &&
        player_position.x + PLAYER_WIDTH < RESOLUTION - SIZE_OF_THORNS + 20 * (RESOLUTION / 1200.0) &&
        player_position.y > SIZE_OF_THORNS - 20 * (RESOLUTION / 1200.0) &&
        player_position.y + PLAYER_HIGHT < RESOLUTION - SIZE_OF_THORNS + 20 * (RESOLUTION / 1200.0))
        return false;
    return true;
}
void Player1::UpdatePosition(RenderWindow& window, Event& event, float time, float current_frame, bool& flag_attack)
{
    while (window.pollEvent(event))
    {
        if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
        {
            player_position.y -= SPEED;
            prev_event = Keyboard::Up;
            if (side == 1) player_sprite.setTextureRect(IntRect(current_frame * (int)time, 370, 80, 100));
            else  player_sprite.setTextureRect(IntRect(current_frame * (int)time + 80, 370, -80, 100));
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
            prev_event = Keyboard::Down;
            if (side == 1) player_sprite.setTextureRect(IntRect(current_frame * (int)time, 370, 80, 100));
            else  player_sprite.setTextureRect(IntRect(current_frame * (int)time + 80, 370, -80, 100));
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
            prev_event = Keyboard::Left;
            player_sprite.setTextureRect(IntRect(current_frame*(int)time+ 80, 370, -80, 100));
            side = 2;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player_position.x += SPEED;
            prev_event = Keyboard::Right;
            player_sprite.setTextureRect(IntRect(current_frame * (int)time, 370, 80, 100));
            side = 1;
        }
        else {
            if(side==1)player_sprite.setTextureRect(IntRect(185, 45, 80, 100));
            else player_sprite.setTextureRect(IntRect(265, 45, -80, 100));
        }
    }
    if (IsPlayerOutOfBounds())
    {
        UpdateLives(-1000);
    }
}
void Player2::UpdatePosition(RenderWindow& window, Event& event, float time, float current_frame, bool& flag_attack)
{
    while (window.pollEvent(event))
    {
        if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
        {
            ice_walking.play();
            prev_event = Keyboard::Up;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            ice_walking.play();
            prev_event = Keyboard::Down;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            ice_walking.play();
            prev_event = Keyboard::Left;
            side = 2;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            ice_walking.play();
            prev_event = Keyboard::Right;
            side = 1;
        }
    }
    if (prev_event == Keyboard::Up)
    {
        player_position.y -= SPEED;
        if(side==1) player_sprite.setTextureRect(IntRect(0, 45, 70, 90));
        else player_sprite.setTextureRect(IntRect(70, 45, -70, 90));
    }
    else if (prev_event == Keyboard::Down)
    {
        player_position.y += SPEED;
        if (side == 1) player_sprite.setTextureRect(IntRect(0, 45, 70, 90));
        else player_sprite.setTextureRect(IntRect(70, 45, -70, 90));
    }
    else if (prev_event == Keyboard::Left)
    {
        player_position.x -= SPEED;
        if (side == 1) player_sprite.setTextureRect(IntRect(00, 45, 70, 90));
        else player_sprite.setTextureRect(IntRect(70, 45, -70, 90));
    }
    else if (prev_event == Keyboard::Right)
    {
        player_position.x += SPEED;
        if (side == 1) player_sprite.setTextureRect(IntRect(0, 45, 70, 90));
        else player_sprite.setTextureRect(IntRect(70, 45, -70, 90));
    }
    if (IsPlayerOutOfBounds())
    {
        UpdateLives(-1000);
    }
}
void Player3::UpdatePosition(RenderWindow& window, Event& event, float time, float current_frame, bool& flag_attack)
{
    while (window.pollEvent(event))
    {
        if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
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
void Player4::UpdatePosition(RenderWindow& window, Event& event, float time, float current_frame, bool& flag_attack)
{
    while (window.pollEvent(event))
    {
        if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
        {
            player_position.y -= SPEED;
            if (side == 1) player_sprite.setTextureRect(IntRect(current_frame * (int)time, 370, 80, 100));
            else  player_sprite.setTextureRect(IntRect(current_frame * (int)time + 80, 370, -80, 100));
            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                attack_delay = Keyboard::E;
            }
            else
            {
                attack_delay = Keyboard::T;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player_position.y += SPEED;
            if (side == 1) player_sprite.setTextureRect(IntRect(current_frame * (int)time, 370, 80, 100));
            else  player_sprite.setTextureRect(IntRect(current_frame * (int)time + 80, 370, -80, 100));
            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                attack_delay = Keyboard::E;
                
            }
            else
            {
                attack_delay = Keyboard::T;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player_position.x -= SPEED;
            player_sprite.setTextureRect(IntRect(current_frame * (int)time + 80, 370, -80, 100));
            side = 2;
            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                attack_delay = Keyboard::E;
                
            }
            else
            {
                attack_delay = Keyboard::T;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player_position.x += SPEED;
            player_sprite.setTextureRect(IntRect(current_frame * (int)time, 370, 80, 100));
            side = 1;
            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                attack_delay = Keyboard::E;
                
            }
            else
            {
                attack_delay = Keyboard::T;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::E))
        {
            attack_delay = Keyboard::E;
            flag_attack = true;
        }
        else
        {
            if (side == 1)player_sprite.setTextureRect(IntRect(185, 45, 80, 100));
            else player_sprite.setTextureRect(IntRect(265, 45, -80, 100));
            attack_delay = Keyboard::T;
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
    player->player_position.x = rand() % (RESOLUTION / 2 - PLAYER_WIDTH * 2 - SIZE_OF_THORNS * 2) + map[0]->position.x + PLAYER_WIDTH + 
        SIZE_OF_THORNS;
    player->player_position.y = rand() % (RESOLUTION / 2 - PLAYER_HIGHT * 2 - SIZE_OF_THORNS * 2) + map[0]->position.y + PLAYER_HIGHT +
        SIZE_OF_THORNS;
}

void IsBonusPickedUp(Player* player, Map* map[], std::vector<int> checker[], Sound& bomb_sound, Sound& hp_sound, Sound& time_sound)
{
    Texture bomb_texture;
    bomb_texture.loadFromFile("bomb.png");
    FloatRect rect1(player->player_position.x, player->player_position.y, PLAYER_WIDTH, PLAYER_HIGHT);
    std::vector<FloatRect> rect2[NUMBER_OF_LOCATIONS];
    for (int i = 0; i < NUMBER_OF_LOCATIONS; i++)
        for (int j = 0; j < map[i]->objects_sprite.size(); j++)
        {
            rect2[i].push_back(FloatRect(map[i]->objects_sprite[j].getPosition().x, map[i]->objects_sprite[j].getPosition().y,
                map[i]->objects_sprite[j].getTexture()->getSize().x * RESOLUTION / 1200.0, 
                map[i]->objects_sprite[j].getTexture()->getSize().y * RESOLUTION / 1200.0));
            if (rect1.intersects(rect2[i][j]) && checker[i][j] <= 1)
            {
                if (dynamic_cast<Player3*>(player) && checker[i][j] == 0)
                {
                    hp_sound.play();
                    player->UpdateLives(10);
                    map[i]->objects_sprite.erase(map[i]->objects_sprite.begin() + j);
                    checker[i].erase(checker[i].begin() + j);
                }
                else if (checker[i][j] == 0)
                {
                    time_sound.play();
                    player->UpdateScore();
                    map[i]->objects_sprite.erase(map[i]->objects_sprite.begin() + j);
                    checker[i].erase(checker[i].begin() + j);
                }
                else if (checker[i][j] == 1)
                {
                    bomb_sound.play();
                    player->UpdateLives(-50);
                    map[i]->explode(map[i]->objects_sprite[j]);
                    checker[i][j]++;
                }
            }
            else if (checker[i][j] > 1)
            {
                checker[i][j]++;
                if (checker[i][j] % 10 == 0)
                    map[i]->objects_sprite[j].setTextureRect(IntRect(OBJ_SIZE * checker[i][j] / 10,
                        0, OBJ_SIZE, OBJ_SIZE));
                if (checker[i][j] == 100)
                {
                    map[i]->objects_sprite.erase(map[i]->objects_sprite.begin() + j);
                    checker[i].erase(checker[i].begin() + j);
                }
            }
        }
}
bool CheckOverlap(std::vector<Sprite> sprites, std::vector<Sprite> sprites2, int j)
{
    for (int k = 0; k < j; ++k)
    {
        FloatRect rect1(sprites[j].getPosition().x,
            sprites[j].getPosition().y,
            sprites[j].getTexture()->getSize().x * RESOLUTION / 1200.0,
            sprites[j].getTexture()->getSize().y * RESOLUTION / 1200.0);
        FloatRect rect2(sprites2[k].getPosition().x,
            sprites2[k].getPosition().y,
            sprites2[k].getTexture()->getSize().x * RESOLUTION / 1200.0,
            sprites2[k].getTexture()->getSize().y * RESOLUTION / 1200.0);

        if (rect1.intersects(rect2))
        {
            return true;
        }
    }
    return false;
}
void Transition_to_a_new_zone(Player*& Main_player, Map* map[])
{
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
}
bool Game::Screen_Of_Win(RenderWindow& window, Player* Main_player, Enemy* boss, int score, bool& flag_music)
{
    if (boss->hp <= 0)
    {
        bool flag = false;
        Clock time_button;

        Texture texture_background, texture_button1, texture_button2;
        Sprite background, button1, button2;
        texture_background.loadFromFile("win.png");
        texture_button1.loadFromFile("Button1.png");
        texture_button2.loadFromFile("Button2.png");
        background.setTexture(texture_background);
        button1.setTexture(texture_button1);
        button2.setTexture(texture_button2);
        background.setPosition(0, 0);
        background.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
        button1.setPosition(RESOLUTION / 6, RESOLUTION / 1.5);
        button1.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
        button2.setPosition(RESOLUTION / 6, RESOLUTION / 1.5);
        button2.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);

        Font font;
        font.loadFromFile("Text.ttf");
        Text text_score(L"Оставшееся время: " + std::to_string(score) + L" сек", font, 50);
        text_score.setStyle(Text::Style::Italic && Text::Style::Bold);
        text_score.setScale((float)RESOLUTION / texture_background.getSize().x, (float)RESOLUTION / texture_background.getSize().y);
        text_score.setPosition(RESOLUTION / 6, RESOLUTION / 1.7);

        if (!flag_music) {
            StopMusic_background();
            victory_music.play();
            flag_music = true;
        }

        Event event;
        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                    window.close();
                if (event.type == Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        if (button1.getGlobalBounds().contains(x, y)) 
                        {

                            window.clear();
                            window.draw(background);
                            window.draw(text_score);
                            window.draw(button2);
                            window.display();
                            while (time_button.getElapsedTime().asMilliseconds() <= 400) {};
                            Main_player->hp = 100;
                            Main_player->score = 30;
                            Main_player->player_position = { 0,0 };
                            flag = true;
                            victory_music.stop();
                            return false;
                        }
                    }
                }
            }
            window.clear();

            window.draw(background);
            window.draw(text_score);
            window.draw(button1);

            window.display();
        }
    }
    return true;
}

int main()
{
    bool flag;
    bool flag_EndGame;
    bool lever;
    do {
        flag = false;
        flag_EndGame = false;
        lever = true;

        srand(time(NULL));
        Game game;
        Map* map[NUMBER_OF_LOCATIONS] = { new Map1(), new Map2(), new Map3(), new Map4() }; //указатель на количество локаций

        bool flag_music = false;

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
                    (RESOLUTION / 2 - int(map[i]->objects_sprite[j].getTexture()->getSize().x * RESOLUTION / 1200.0) - SIZE_OF_THORNS * 2) +
                    SIZE_OF_THORNS),
                    map[i]->position.y + (rand() %
                        (RESOLUTION / 2 - int(map[i]->objects_sprite[j].getTexture()->getSize().y * RESOLUTION / 1200.0) - SIZE_OF_THORNS * 2)
                        + SIZE_OF_THORNS));
                if (CheckOverlap(map[i]->objects_sprite, map[i]->objects_sprite, j))
                    j--;
            }
        }
        std::vector<int> collision_checker[NUMBER_OF_LOCATIONS];
        for (int i = 0; i < NUMBER_OF_LOCATIONS; i++)
            for (int j = 0; j < map[i]->objects_sprite.size(); j++)
            {
                if (j < map[i]->objects_sprite.size() / 2 && (i == 1 || i == 2))
                    collision_checker[i].push_back(0);
                else if (j >= map[i]->objects_sprite.size() / 2 && (i == 1 || i == 2))
                    collision_checker[i].push_back(1);
                else collision_checker[i].push_back(0);
            }
        Player* Main_player = new Player1(), *memory_player;
        Enemy* enemy = new Warrior(map);
        Enemy* boss = new Boss(map);
        Enemy* tank = new Tank(map);
        GenerateRandomPosition(Main_player, map); // генерирование случайной позиции в начальной локации

        Texture texture_border;
        texture_border.loadFromFile("border.png");
        Sprite border;
        border.setTexture(texture_border);
        border.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);
        Texture texture_shader;
        texture_shader.loadFromFile("shader.png");
        Sprite shader;
        shader.setTexture(texture_shader);
        shader.setScale(RESOLUTION / 1200.0, RESOLUTION / 1200.0);

        //Звуки
        std::vector<SoundBuffer> buffer(5);
        /*
        0-удар самурая
        1-удар босса
        2-взрыв бомбы
        3-подбор жизней
        4-подбор времени
        */
        buffer[0].loadFromFile("SamuraiPunch.wav");
        buffer[1].loadFromFile("BossPunch.wav");
        buffer[2].loadFromFile("Bomb.wav");
        buffer[3].loadFromFile("HP_Sound.wav");
        buffer[4].loadFromFile("Time_Sound.wav");
        Sound samurai_punch, boss_punch, bomb_sound, hp_sound, time_sound;
        samurai_punch.setBuffer(buffer[0]);
        boss_punch.setBuffer(buffer[1]);
        bomb_sound.setBuffer(buffer[2]);
        hp_sound.setBuffer(buffer[3]);
        time_sound.setBuffer(buffer[4]);

        Clock cl, limiter, GameOver_time;
        Event event;
        Font score_font;
        score_font.loadFromFile("Text.ttf");
        Text scoreText("Time: " + std::to_string(Main_player->score), score_font, RESOLUTION / 30);
        scoreText.setPosition(RESOLUTION / 2 - SIZE_OF_THORNS * 2, SIZE_OF_THORNS);
        Image icon;
        float time_frame = 1, current_frame = 185;
        bool flag_attack = false;
        RenderWindow window(VideoMode(RESOLUTION, RESOLUTION), "Video game");
        icon.loadFromFile("icon.png");
        window.setIcon(128, 128, icon.getPixelsPtr()); //установка иконки игры (хз, поставил из своей игры, можете поменять)
        cl.restart();
        game.PlayMusic_background(Main_player);
        while (window.isOpen())
        {
            lever = game.Screen_Of_Win(window, Main_player, boss, Main_player->score, flag_music);
            if (!game.Is_player_dead(Main_player->hp, Main_player->score) && lever) {
                limiter.restart();
                while (limiter.getElapsedTime().asMicroseconds() <= 10000)
                {
                }
                if (time_frame > 6) {
                    time_frame = 1;
                    current_frame = 185;
                }
                else time_frame += 0.3;
                Main_player->UpdatePosition(window, event, time_frame, current_frame, flag_attack); //вывод новой позиции при нажатии клавиши, проверка пересечения 

                if (flag_attack) {
                    samurai_punch.play();
                    time_frame = 1;
                    do {
                        time_frame += 0.05;
                        if (Player::side == 1) Main_player->player_sprite.setTextureRect(IntRect(current_frame * (int)time_frame, 620, 130, 150));
                        else  Main_player->player_sprite.setTextureRect(IntRect(current_frame * (int)time_frame + 130, 620, -130, 150));
                        game.Graphics(window, Main_player, map, border, shader, enemy, boss, tank, boss_punch, flag_attack, scoreText); // отрисовка карты и игрока
                    } while (time_frame <= 6);
                    flag_attack = false;
                    if (Player::side == 1)Main_player->player_sprite.setTextureRect(IntRect(185, 45, 80, 100));
                    else Main_player->player_sprite.setTextureRect(IntRect(265, 45, -80, 100));
                }
                //границ 4-х зон и границ карты (вызывает update lives когда мёртв)
                Transition_to_a_new_zone(Main_player, map);
                //Main_player->UpdateScore();
                IsBonusPickedUp(Main_player, map, collision_checker);
                game.Graphics(window, Main_player, map, border, shader, enemy, boss, tank, flag_attack); // отрисовка карты и игрока
                if (cl.getElapsedTime().asSeconds() >= 1) {
                    Main_player->score--;//обновляет таймер в секундах.
                    std::cout << Main_player->score << "\n";
                    cl.restart();
                }
            }
            else {
                if (!lever)
                {
                    flag = true;
                }
                if (!flag)
                {
                    if (!flag_music) {
                        game.StopMusic_background();
                        game.PlayMusic_end();
                        flag_music = true;
                    }
                    //Экран пройгрыша
                    Texture Game_over_texture;
                    Game_over_texture.loadFromFile("Game_over.png");
                    Sprite Game_over;
                    Game_over.setScale((float)RESOLUTION / Game_over_texture.getSize().x, (float)RESOLUTION / Game_over_texture.getSize().y);
                    Game_over.setTexture(Game_over_texture);
                    Game_over.setPosition(0, 0);

                    //Инициализация кнопки и его состояний
                    Texture Button_texture, Button_texture2;

                    Button_texture.loadFromFile("Button1.png");//первое состояние кнопки
                    Button_texture2.loadFromFile("Button2.png");//второе состояние кнопки

                    Sprite Button, Button2;

                    Button.setScale((float)RESOLUTION / Game_over_texture.getSize().x, (float)RESOLUTION / Game_over_texture.getSize().y);
                    Button.setTexture(Button_texture);
                    Button.setPosition(RESOLUTION / 6, RESOLUTION / 1.5);

                    Button2.setScale((float)RESOLUTION / Game_over_texture.getSize().x, (float)RESOLUTION / Game_over_texture.getSize().y);
                    Button2.setTexture(Button_texture2);
                    Button2.setPosition(RESOLUTION / 6, RESOLUTION / 1.5);

                    //Шрифт для вывода оставшегося времени
                    Font font;
                    font.loadFromFile("Text.ttf");
                    Text text("", font, 50);
                    text.setStyle(Text::Italic);
                    text.setFillColor(Color(230, 230, 230));
                    text.setString(L"Оставшееся время: " + std::to_string(Main_player->score) + L" сек");
                    text.setPosition(RESOLUTION / 12, RESOLUTION / 2);
                    text.setScale((float)RESOLUTION / Game_over_texture.getSize().x, (float)RESOLUTION / Game_over_texture.getSize().y);

                    //Анимация экрана окончания
                    if (!flag_EndGame) {
                        RectangleShape Black_helper;
                        for (int i = 255; i >= 0; i--) {
                            GameOver_time.restart();
                            Black_helper.setFillColor(Color(0, 0, 0, i));
                            Black_helper.setSize(Vector2f(RESOLUTION, RESOLUTION / 4));
                            Black_helper.setPosition(0, RESOLUTION / 12);
                            window.clear();
                            window.draw(Game_over);
                            window.draw(Black_helper);
                            Black_helper.setFillColor(Color(0, 0, 0));
                            Black_helper.setPosition(0, RESOLUTION / 3);
                            window.draw(Black_helper);
                            window.display();
                            while (GameOver_time.getElapsedTime().asMilliseconds() <= 5) {};
                        }
                        for (int i = 255; i >= 0; i--) {
                            GameOver_time.restart();
                            Black_helper.setFillColor(Color(0, 0, 0, i));
                            Black_helper.setSize(Vector2f(RESOLUTION, RESOLUTION / 4));
                            Black_helper.setPosition(0, RESOLUTION / 3);
                            window.clear();
                            window.draw(Game_over);
                            window.draw(Black_helper);
                            window.display();
                            while (GameOver_time.getElapsedTime().asMilliseconds() <= 5) {};
                        }
                        flag_EndGame = true;
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

                                    window.clear();
                                    window.draw(Game_over);
                                    window.draw(text);
                                    window.draw(Button2);
                                    window.display();
                                    GameOver_time.restart();
                                    while (GameOver_time.getElapsedTime().asMilliseconds() <= 200) {};
                                    Main_player->hp = 100;
                                    Main_player->score = 30;
                                    Main_player->player_position = { 0,0 };
                                    flag = true;
                                    game.StopMusic_end();
                                    break;
                                }
                            }
                        }
                    }
                    if (flag)break;
                }
                else break;          
            }
        }
    } while (flag);

    return 0;
}