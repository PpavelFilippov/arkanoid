//
// Created by roucr on 14.08.2023.
//

#ifndef BONUS_H
#define BONUS_H

#include "GameObjects.h"
#include <random>

class Bonus : public Object
{
private:
    sf::Vector2i size;

public:
    std::vector < std::vector<Block*>> Blocks;
    Ball *ball;
    Paddle *paddle;
    sf::Vector2i FieldSize = { WIDTH,HEIGHT };

    Bonus( Ball* ball, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int i);

    void InitBonus(sf::Vector2i t);
    virtual void MakeAction() {};
    void ResetBonus();
    virtual sf::Vector2i getSize();
};


class BChangePaddleScale : public Bonus
{
public:
    BChangePaddleScale(Ball* ball, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int i) :Bonus(ball, paddle, Blocks, i) {};
    void MakeAction()
    {
        std::cout << "Paddle change bonus is activated" << std::endl;
        paddle->SetRandomScale();
        std::cout << "Paddle size is changed" << std::endl;
    }

};


class BChangeBallSpeed :public Bonus
{
public:
    BChangeBallSpeed( Ball* ball, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int i) :Bonus(ball, paddle, Blocks, i) {};
    void MakeAction()
    {
        sf::Vector2f speed, zeros = { 0,0 };
        sf::Vector2f v1, v2;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(0, 99);
        float rnd = distribution(gen) / 100.0 + 0.5;
       // float rnd = (float)(rand() % 100) / 100.0 + 0.5;
            if (ball->getSpeed() != zeros)
            {
                speed = ball->getSpeed();
                speed.x *= rnd;
                speed.y *= rnd;
                ball->SetSpeed(speed);
            }
            std::cout << "Ball change bonus is activated" << std::endl;
    }
};


class BStickyPaddle : public Bonus
{
public:
    BStickyPaddle( Ball* ball, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int i) :Bonus(ball, paddle, Blocks, i) {};
    void MakeAction()
    {
        paddle->SetSticky();
        std::cout << "Sticky paddle bonus is activated" << std::endl;
    }
};


class BSafeBottom : public Bonus
{
public:
    BSafeBottom( Ball* ball, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int i) :Bonus(ball, paddle, Blocks, i) {};
    void MakeAction()
    {
        ball->SetSafe();
        std::cout << "Safe bottom bonus id activated!" << std::endl;
    }
};


class BCreateMovingBlock : public Bonus
{
public:
    BCreateMovingBlock( Ball* ball, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int i) :Bonus(ball, paddle, Blocks, i) {};
    void MakeAction()
    {
        for (int i = FieldSize.y - 1; i >= 0; i--)
        {
            for (int j = FieldSize.y - 1; j >= 0; j--)
            {
                if (!Blocks[i][j]->isDead())
                {
                    sf::Vector2f v = { 3.0, 0 };
                    Blocks[i][j]->SetSpeed(v);
                    std::cout << "Moving block bonus is activated" << std::endl; //TODO: check bonus
                    return; // delete for fun
                }
            }
        }
    }
};


class BChangeBallDirection : public Bonus
{
public:
    BChangeBallDirection( Ball* ball, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int i) :Bonus(ball, paddle, Blocks, i) {};

    void MakeAction() override
    {
        sf::Vector2f v1, v2;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> angleDistribution(0.0f, 360.0f);
        float randomAngle = angleDistribution(gen);
        float angleInRadians = randomAngle * M_PI / 180.0f; //TODO: make rand time

            v1 = ball->getSpeed();
            v2 = RotateVector(v1, angleInRadians);
            std::cout << "Change direction ball bonus is activated" << std::endl;
            ball->SetSpeed(v2);
    }
};


#endif