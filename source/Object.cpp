//
// Created by roucr on 14.08.2023.
//


#include <cmath>
#include "AllObj.h"


void Object::Move()
{
    if (this != nullptr)
    {
        screenPosition.x = screenPosition.x + speed.x;
        screenPosition.y = screenPosition.y + speed.y;
        sprite.setPosition((float)screenPosition.x, (float)screenPosition.y);
    }
}


void Object::Draw(sf::RenderWindow *window)
{
    sprite.setPosition((float)screenPosition.x, (float)screenPosition.y);
    window->draw(sprite);
}


void Object::SetSpeed(sf::Vector2f speed)
{
    this->speed = speed;
}

void Object::SetScreenPosition(sf::Vector2i position)
{
    screenPosition = position;
}

void Object::SetSprite( sf::Sprite s)
{
    sprite = s;
}


sf::Sprite Object::getSprite()
{
    return sprite;
}

sf::Vector2i Object::getScreenPosition()
{
    return screenPosition;
}

sf::Vector2f Object::getSpeed()
{
    return speed;
}


sf::Vector2f RotateVector(sf::Vector2f vec, float alpha)
{
    sf::Vector2f newVec = vec;
    newVec.x = vec.x * std::cos(alpha) - vec.y * std::sin(alpha);
    newVec.y = vec.x * std::sin(alpha) + vec.y * cos(alpha);

    return newVec;
}



