//
// Created by roucr on 15.08.2023.
//

#include "AllObj.h"

Block::Block(int i, int j, int h)
{
    texture.loadFromFile("resourses/SPRT.png");
    size = (sf::Vector2i)(texture.getSize());
    size.x /= 6;

    sprite.setTexture(texture);

    health = h;
    SetTexture(health);

    tablePosition.x = i;
    tablePosition.y = j;
    screenPosition.x = 5 + (1.5 * size.x + 5) * i;
    screenPosition.y = 3 + (1.5 * size.y + 3) * j;

    speed = { 0,0 };
}


void Block::ScreenCheck()
{
    if (this != nullptr)
    {
        if (screenPosition.x <= 0 || screenPosition.x >= DisplayX - size.x)
            speed.x = -speed.x;
    }
}

void Block::SetTexture(int health)
{
    sprite.setTextureRect(sf::IntRect((health - 1) * size.x, 0, size.x, size.y));
}

void Block::DecreaseHP()
{
    health--;
    SetTexture(health);
}

sf::Vector2i Block::getSize()
{
    return size;
}

FeatureType Block::getFeature()
{
    return feature;
}

void Block::CheckDeath()
{
    if (health <= 0)
    {
        sf::Vector2i t = { -100, -100 };
        SetScreenPosition(t);
        sf::Vector2f v = { 0,0 };
        SetSpeed(v);
        Dead = true;

    }
}

bool Block::isDead()
{
    return Dead;
}