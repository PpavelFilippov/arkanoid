//
// Created by roucr on 14.08.2023.
//
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
    Block(int i, int j, int health);
    ~Block() override = default;
    FeatureType feature;

    sf::Vector2i getSize() override;

    void DecreaseHP();
    void CheckDeath();
    bool isDead();
    void SetTexture(int health);
    void ScreenCheck();

    FeatureType getFeature();

private:
    int health;
    sf::Vector2i size;
    bool Dead = false;
};

class SimpleBlock : public Block
{
public:
    SimpleBlock(int i, int j, int health) :Block(i, j, health) { feature = None; }
    ~SimpleBlock() override = default;
};

class UnbreakableBlock : public Block
{
public:
    UnbreakableBlock(int i, int j, int health) :Block(i, j, health) { feature = Unbreakable; }
    ~UnbreakableBlock() override = default;
};

class AcceleratingBlock : public Block
{
public:
    AcceleratingBlock(int i, int j, int health) :Block(i, j, health) { feature = Accelerating; }
    ~AcceleratingBlock() override = default;
};

class BonusBlock : public Block
{
public:
    BonusBlock(int i, int j, int health) :Block(i, j, health) { feature = WithBonus; }
    ~BonusBlock() override = default;
};

class Ball : public Object
{
private:
    sf::Vector2i size;
    bool OnPaddle = false;
    bool Safe = false;

public:
    Ball();
    ~Ball() override = default;

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
    ~Paddle() override = default;

    void Move()            override;
    sf::Vector2i getSize() override;
    void SetRandomScale();
    void SetSticky();
    bool isSticky();
};


class Bonus;
