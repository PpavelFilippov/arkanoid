//
// Created by roucr on 20.08.2023.
//


#ifndef ARCANOID_H
#define ARCANOID_H

#include "AllObj.h"
#include "Initializer.h"
#include "Builder.h"
#include "Interface.h"


class Game
{
public:
    Game() ;
    ~Game();
    void Play();

    Initializer *Init;
    Builder *Build;
    std::vector < std::vector<Block*>> Blocks;
    std::vector < Bonus*> Bonuses;
    Ball *ball;
    Paddle *paddle;
};

#endif