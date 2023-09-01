//
// Created by roucr on 17.08.2023.
//

#include "GameObjects.h"
#include "Builder.h"
#include "Bonus.h"


sf::Vector2i Builder::getFieldSize()
{
    return FieldSize;
}


sf::Vector2i Builder::getSize() //plug
{
    return { -1,-1 };
}


void Builder::BallMakeStep(Ball *ball)
{
    ball->Move(ball->getSpeed());

    PaddleInteraction(ball);
    BlocksInteraction(ball);

    //For init ball
    if (ball->isOnPaddle())
    {
        sf::Vector2i pos = paddle->getScreenPosition();
        sf::Vector2i size = paddle->getSize();
        pos.x += size.x / 2 - ball->getSize().x;
        pos.y -= (ball->getSize().y + 2);
        ball->SetScreenPosition(pos);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            ball->SetUnInit();
            sf::Vector2f v = { 0.0, -5.0 };
            // float maxAngle = M_PI / 4;
            // float alpha = (float)(rand() % 100) / 100.0 * maxAngle;
            v = RotateVector(v, 0.0); //TODO: alpha == 0 seems to me the best angle to start
            ball->SetSpeed(v);
        }
    }
    ScreenCheck(ball);
}


void Builder::BlockMakeStep(Block *block)
{
    if (block->getSpeed().x == 0.0)
        return;

    block->Move();

    sf::Vector2f currentSpeed = block->getSpeed();
    const float horizontalSpeedInverseFactor = -1.0f;

    for (int i = 0; i < FieldSize.x; i++)
    {
        for (int j = 0; j < FieldSize.y; j++)
        {
            if (Blocks[i][j] == block)
                continue;

            sf::FloatRect blockBounds = block->getSprite().getGlobalBounds();
            sf::FloatRect otherBlockBounds = Blocks[i][j]->getSprite().getGlobalBounds();

            // Check for intersection between the two block bounds
            if (blockBounds.intersects(otherBlockBounds))
            {
                currentSpeed.x = horizontalSpeedInverseFactor * currentSpeed.x;
                block->SetSpeed(currentSpeed);
            }
        }
    }
    block->ScreenCheck();
}


void Builder::BonusMakeStep(Bonus *bonus)
{
    bonus->Move();

    if (bonus->getSprite().getGlobalBounds().intersects(paddle->getSprite().getGlobalBounds()))
    {
        bonus->MakeAction();
        bonus->ResetBonus();
    }
}


void Builder::GameOverCheck()
{
    if (RemainingLives <= 0)
    {
        GameStatus = -1;
        std::cout << "You lose.(" << std::endl;
    }
}

void Builder::VictoryCheck()
{
    if(GameStatus!=-1) //idk, I'm not sure about necessarity for this check, but let it be
    {
        for (int i = 0; i < FieldSize.x; i++)
        {
            for (int j = 0; j < FieldSize.y; j++)
            {
                if (!Blocks[i][j]->isDead())
                    return;
            }
        }
        GameStatus = 1;
        std::cout << "You win!" << std::endl;
    }
}


void Builder::MakeFrame()
{
    paddle->Move();
    BallMakeStep(ball);

    for (int i = 0; i < FieldSize.x; i++)
    {
        for (int j = 0; j < FieldSize.y; j++)
        {
            BlockMakeStep(Blocks[i][j]);
        }
    }

    for (int i = 0; i < MaxBonuses; i++)
    {
        BonusMakeStep(Bonuses[i]);
    }

    VictoryCheck();
}


void Builder::ScreenCheck(Ball *ball)
{
    if (ball->getScreenPosition().x <= 0 || ball->getScreenPosition().x >= DisplayX - ball->getSize().x)
        ball->ReverseSpeed('x');

    if (ball->getScreenPosition().y <= 0)
        ball->ReverseSpeed('y');

    if (ball->getScreenPosition().y >= DisplayY - ball->getSize().y)
    {
        if (ball->isSafe())
        {
            ball->ReverseSpeed('y');
            ball->SetUnsafe();
            if (GameStatus == -1)												//additional ball
                ball->InitBall();
        }else
        {
            if(RemainingLives > 0)
            {
                std::cout << "Ball lost" << std::endl;
                ball->ResetBall();
                ball->InitBall();
                RemainingLives--;
                std::cout << "Remaining lives: " << RemainingLives << std::endl;
            }else
                GameOverCheck();
        }
    }
}


int Builder::getMaxBonuses() const
{
    return MaxBonuses;
}


int Builder::getRemainingLives() const
{
    return RemainingLives;
}


int Builder::getGameStatus() const
{
    return GameStatus;
}


Block* Builder::getBlock(int i, int j)
{
    return Blocks[i][j];
}


Ball* Builder::getBall()
{
    return ball;
}


Bonus* Builder::getBonus(int i)
{
    return Bonuses[i];
}


Paddle* Builder::getPaddle()
{
    return paddle;
}