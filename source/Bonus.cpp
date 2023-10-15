//
// Created by roucr on 15.08.2023.
//


#include "AllObj.h"
#include "Bonus.h"


Bonus::Bonus(Ball *ball, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int i) : ball(ball), paddle(paddle), Blocks(Blocks)
{
    static sf::String Names[6] = { "bonus_paddlescale1","bonus_ballspeed1","bonus_stickypaddle1","bonus_safebottom1","bonus_changedirection1","bonus_movingblock1" };
    speed = { 0, 0 };
    screenPosition = { -100,-100 };
    image.loadFromFile("resourses/" + Names[i % 6] + ".png");
    image.createMaskFromColor(image.getPixel(0, 0));
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    size = (sf::Vector2i)(texture.getSize());
}


void Bonus::InitBonus(sf::Vector2i t)
{
    screenPosition = t;
    speed = { 0, 2 };
}


void Bonus::ResetBonus()
{
    sf::Vector2f v = { 0,0 };
    SetSpeed(v);
    sf::Vector2i p = { -100,-100 };
    SetScreenPosition(p);
}


sf::Vector2i Bonus::getSize()
{
    return size;
}