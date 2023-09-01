//
// Created by roucr on 14.08.2023.
//

#ifndef GameObjects_H
#pragma once

#include "Object.h"

sf::Vector2f RotateVector(sf::Vector2f vec, float alpha);

enum FeatureType      //Block features
{
    None,
    Unbreakable,
    WithBonus,
    Accelerating
};

class Block : public Object
{
public:
    //Block(int i, int j);
    Block(int i, int j, int health); //TODO: rename health to more suitable word like endurance
    FeatureType feature;

    sf::Vector2i getSize() override;

    void DecreaseHP();
    void CheckDeath();
    bool isDead();
    void SetTexture(int health);
    void ScreenCheck();

    FeatureType getFeature();

    //~Block() {};

private:
    int health;
    sf::Vector2i size;
    bool Dead = false;
};

class SimpleBlock : public Block
{
public:
    SimpleBlock(int i, int j, int health) :Block(i, j, health) { feature = None; }
};

class UnbreakableBlock : public Block
{
public:
    UnbreakableBlock(int i, int j, int health) :Block(i, j, health) { feature = Unbreakable; }
};

class AcceleratingBlock : public Block
{
public:
    AcceleratingBlock(int i, int j, int health) :Block(i, j, health) { feature = Accelerating; }
};

class BonusBlock : public Block
{
public:
    BonusBlock(int i, int j, int health) :Block(i, j, health) { feature = WithBonus; }
};

class Ball : public Object
{
private:
    sf::Vector2i size;
    bool OnPaddle = false;
    bool Safe = false;

public:
    Ball();

    sf::Vector2i getSize() override;
    virtual void Move(sf::Vector2f speed);

    void InitBall();
    void ResetBall();
    void SetUnInit();
    void SetSafe();
    void SetUnsafe();
    bool isOnPaddle();
    bool isSafe();
    void ReverseSpeed(char axis);
};

class Paddle : public Object
{
private:
    sf::Vector2i size;
    int stickyHealth = 0;

public:
    Paddle();

    void Move() override;
    sf::Vector2i getSize() override;
    void SetRandomScale();
    void SetSticky();
    bool isSticky();
};


class Bonus;

#endif