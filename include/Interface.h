//
// Created by roucr on 19.08.2023.
//

#ifndef HEADER_H
#define HEADER_H

#include "GameObjects.h"
#include "Builder.h"
#include "Bonus.h"


class Interface
{
public:
    sf::RenderWindow *window;
    sf::Texture backgroundTex;
    sf::Sprite background;
    sf::Vector2i FieldSize = { WIDTH,HEIGHT };

    explicit Interface(sf::RenderWindow *window) : window(window) {}

    void Render(Builder *Manager) const;
    void DrawObjects(Builder *Manager) const;
};





#endif