//
// Created by roucr on 17.08.2023.
//

#ifndef BUILDER_H
#define BUILDER_H

#include "Object.h"
#include "GameObjects.h"
#include "Bonus.h"




class Builder : public Object
{

public:
    Builder(Ball *ball, std::vector < Bonus*> Bonuses, Paddle *paddle, std::vector<std::vector<Block*>> Blocks) : ball(ball), paddle(paddle), Bonuses(Bonuses), Blocks(Blocks) {};

    sf::Vector2i getFieldSize();
    virtual sf::Vector2i getSize(); //make override

    void BallMakeStep(Ball* ball);
    void BlockMakeStep(Block *block);
    void BonusMakeStep(Bonus *bonus);
    void GameOverCheck();
    void VictoryCheck();
    void MakeFrame();
    void ScreenCheck(Ball *ball);

    void PaddleInteraction(Ball *ball);
    void BlocksInteraction(Ball *ball);

    int getMaxBonuses() const;
    int getRemainingLives() const;
    int getGameStatus() const;
    Block* getBlock(int i, int j);
    Ball* getBall();
    Bonus* getBonus(int i);
    Paddle* getPaddle();

private:
    std::vector < std::vector<Block*>> Blocks;
    std::vector < Bonus*> Bonuses;
    Ball *ball;
    Paddle *paddle;
    sf::Vector2i FieldSize = { WIDTH, HEIGHT };

    int GameStatus = 0;
    int RemainingLives = 3;
};


#endif