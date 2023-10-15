//
// Created by roucr on 17.08.2023.
//

#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "AllObj.h"
#include "Bonus.h"
#include <vector>


class Initializer
{
public:
    Initializer();
    ~Initializer();
    Block* InitBlock(int i, int j);
    std::vector<std::vector<Block*>> getblocksptr();
    Ball*  getballsptr();
    std::vector < Bonus*>  getbonusesptr();
    Paddle* getpaddleptr();

private:
    sf::Vector2i FieldSize = { WIDTH, HEIGHT};
    std::vector < std::vector<Block*>> Blocks;
    std::vector < Bonus*> Bonuses;
    Ball* ball;
    Paddle *paddle;
};


#endif