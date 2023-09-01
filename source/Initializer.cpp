//
// Created by roucr on 17.08.2023.
//

#include "GameObjects.h"
#include "Bonus.h"
#include "Initializer.h"
#include <random>


Initializer::Initializer()
{
    paddle = new Paddle;

    Blocks = std::vector <std::vector<Block*>> (FieldSize.x, std::vector<Block*>(FieldSize.y));
    Bonuses = std::vector <Bonus*>(MaxBonuses);

    for (int i = 0; i < FieldSize.x; i++)
    {
        for (int j = 0; j < FieldSize.y; j++)
        {
            Blocks[i][j] = InitBlock(i, j);
        }
    }

    ball = new Ball;
    ball->InitBall();

    Bonus *p = nullptr;
    for (int i = 0; i < MaxBonuses; i++)
    {
        switch (i % 6)
        {
            case 0: { p = new BChangePaddleScale(ball, paddle, Blocks, i);  break; }
            case 1: { p = new BChangeBallSpeed(ball, paddle, Blocks, i); break; }
            case 2: { p = new BStickyPaddle(ball, paddle, Blocks, i); break; }
            case 3: { p = new BSafeBottom(ball, paddle, Blocks, i); break; }
            case 4: { p = new BChangeBallDirection(ball, paddle, Blocks, i); break; }
            case 5: { p = new BCreateMovingBlock(ball, paddle, Blocks, i); break; }
        }
        Bonuses[i] = p;
    }
}


Initializer::~Initializer()
{
    for (int i = 0; i < FieldSize.x; i++)
    {
        for (int j = 0; j < FieldSize.y; j++)
        {
            delete Blocks[i][j];
        }
    }

    delete ball;

    for (int j = 0; j < MaxBonuses; j++)
    {
        delete Bonuses[j];
    }
    //delete paddle;
}


Block* Initializer::InitBlock(int i, int j) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 99);
    int random = distribution(gen);

    if (random >= 95)
        return new UnbreakableBlock(i, j, UNBREAKABLE);
    else if (random >= 75)
        return new BonusBlock(i, j, random % 5 + 1);
    else if (random >= 60)
        return new AcceleratingBlock(i, j, random % 5 + 1);
    return new SimpleBlock(i, j, random % 5 + 1);
}


std::vector<std::vector<Block*>> Initializer::getblocksptr()
{
    return Blocks;
}


Ball* Initializer::getballsptr()
{
    return ball;
}


std::vector <Bonus*> Initializer::getbonusesptr()
{
    return Bonuses;
}


Paddle* Initializer::getpaddleptr()
{
    return paddle;
}


