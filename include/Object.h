//
// Created by roucr on 14.08.2023.
//

#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include <iostream>
#include <string>
#include "Preference.h"


class Object
{
protected:
    sf::Vector2i screenPosition; //x,y hor, vert
    sf::Vector2i tablePosition;
    sf::Vector2f speed;

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    virtual void Move();
    virtual sf::Vector2i getSize() = 0;

    void Draw(sf::RenderWindow *window);

    void SetSpeed(sf::Vector2f speed);
    void SetScreenPosition(sf::Vector2i position); //TODO: set names without abbreviations
    void SetSprite(sf::Sprite sprite);
    sf::Vector2f getSpeed();
    sf::Vector2i getScreenPosition();
    sf::Sprite getSprite();
};


#endif