//
// Created by roucr on 15.08.2023.
//

#include "AllObj.h"

Ball::Ball()
{
    screenPosition = { -100,-100 };

    speed = { 0,0 };

    image.loadFromFile("resourses/Ball2.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setPosition(-1000, -1000);

    size = (sf::Vector2i)(texture.getSize());

}

bool Ball::isOnPaddle()
{
    return OnPaddle;
}

bool Ball::isSafe()
{
    return Safe;
}

void Ball::SetUnInit()
{
    OnPaddle = 0;
}

void Ball::InitBall()
{
    speed = { 0.0,0.0 };
    OnPaddle = true;
}


void Ball::Move(sf::Vector2f speed)
{
    screenPosition.x = screenPosition.x + speed.x;
    screenPosition.y = screenPosition.y + speed.y;
    sprite.setPosition((float)screenPosition.x, (float)screenPosition.y);
}

sf::Vector2i Ball::getSize()
{
    return size;
}


void Ball::ResetBall()
{
    sf::Vector2f v = { 0,0 };
    SetSpeed(v);
    sf::Vector2i p = { -100,-100 };
    SetScreenPosition(p);
}


void Ball::ReverseSpeed(char axis)
{
    if (axis == 'x')
    {
        speed.x = -speed.x;
    }
    else
    {
        speed.y = -speed.y;
    }
}
void Ball::SetSafe()
{
    Safe = true;
}
void Ball::SetUnsafe()
{
    Safe = false;
}