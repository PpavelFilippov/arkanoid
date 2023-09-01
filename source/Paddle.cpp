//
// Created by roucr on 15.08.2023.
//

#include "GameObjects.h"
#include <random>


Paddle::Paddle()
{
    speed = { 6,0 };
    image.loadFromFile("resourses/Paddle2.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    size = (sf::Vector2i)(texture.getSize());
    screenPosition.x = DisplayX / 2;
    screenPosition.y = DisplayY - size.y;
    sprite.setPosition((float)screenPosition.x, (float)screenPosition.y);
}


sf::Vector2i Paddle::getSize()
{
    return size;
}


void Paddle::SetSticky()
{
    stickyHealth = DURATION;
}


bool Paddle::isSticky()
{
    if (stickyHealth > 0)
    {
        stickyHealth--;
        return true;
    }
    return false;
}


void Paddle::Move()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition();

    //Converting mouse coordinates from screen coordinates to window coordinates.
    sf::Vector2f mousePositionWindow(
            static_cast<float>(mousePosition.x) * DisplayX / static_cast<float>(sf::VideoMode::getDesktopMode().width),
            static_cast<float>(mousePosition.y) * DisplayY / static_cast<float>(sf::VideoMode::getDesktopMode().height)
    );

    screenPosition.x = static_cast<int>(mousePositionWindow.x - size.x / 2);

    if (screenPosition.x < 0)
        screenPosition.x = 0;
    else if (screenPosition.x + size.x > DisplayX)
        screenPosition.x = DisplayX - size.x;

    sprite.setPosition(static_cast<float>(screenPosition.x), static_cast<float>(screenPosition.y));
}


void Paddle::SetRandomScale()
{
    sf::Vector2f scale = sprite.getScale();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.5f, 1.5f);

    float rnd = dis(gen); // Generating a random number in the range from 0.5 to 1.5.

    sprite.setScale(scale.x * rnd, scale.y);
    size.x *= rnd;
    size.y *= rnd;
}
