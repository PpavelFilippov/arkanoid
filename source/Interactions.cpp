//
// Created by roucr on 18.08.2023.
//

#include "GameObjects.h"
#include "Builder.h"
//#include "Bonus.h"

void Builder::PaddleInteraction(Ball *ball)
{
    float  mult;

    if (ball->getSprite().getGlobalBounds().intersects(paddle->getSprite().getGlobalBounds()))
    {
        sf::Vector2f v = ball->getSpeed();
        sf::Vector2f v1;
        v1.x = 0;
        v1.y = -sqrt(v.x * v.x + v.y * v.y);
        v = v1;

        if (!ball->isOnPaddle())
        {
            if (paddle->isSticky())
            {
                ball->InitBall();
                return;
            }

            mult = ball->getScreenPosition().x + ball->getSize().x / 2;
            mult = (float)(mult - (paddle->getScreenPosition().x + paddle->getSize().x / 2)) / paddle->getSize().x;

            v = RotateVector(v, (M_PI / 2 * mult));

            ball->SetSpeed(v);
        }
    }
}


void Builder::BlocksInteraction(Ball *ball)
{
    sf::Vector2i t1 = ball->getScreenPosition(), t2;

    sf::Vector2f v = ball->getSpeed();

    bool changedX, changedY = changedX = false;

    for (int i = 0; i < FieldSize.x; i++)
    {
        for (int j = 0; j < FieldSize.y; j++)
        {
            if (!Blocks[i][j]->isDead())
            {
                t2 = Blocks[i][j]->getScreenPosition();

                if (ball->getSprite().getGlobalBounds().intersects(Blocks[i][j]->getSprite().getGlobalBounds()))
                {
                    float L, R, U, D, minV, minH;

                    L = t1.x - (t2.x + Blocks[i][j]->getSize().x);
                    R = t1.x + ball->getSize().x - t2.x;
                    D = t1.y - (t2.y + Blocks[i][j]->getSize().y);
                    U = t1.y + ball->getSize().y - t2.y;

                    minV = (fabs(D) > fabs(U)) ? fabs(U) : fabs(D);
                    minH = (fabs(R) > fabs(L)) ? fabs(L) : fabs(R);


                    if (minV < minH)
                    {
                        if (!changedY)
                        {
                            v.y = -v.y;
                            changedY = true;
                        }
                    }
                    else
                    {
                        if (!changedX)
                        {
                            v.x = -v.x;
                            changedX = true;
                        }
                    }

                    switch (Blocks[i][j]->getFeature())
                    {
                        case Accelerating: {v.x *= 1.05; v.y *= 1.05;	printf("Speed now: %f\n", sqrt(v.x*v.x + v.y*v.y) ); Blocks[i][j]->DecreaseHP(); break; }
                        case Unbreakable: {break; }
                        case WithBonus: {Blocks[i][j]->DecreaseHP(); break; }
                        default: {Blocks[i][j]->DecreaseHP(); }
                    }

                    sf::Vector2f t = { -ball->getSpeed().x, -ball->getSpeed().y };
                    ball->Move(t);

                    ball->SetSpeed(v);

                    sf::Vector2i position_for_bonus = Blocks[i][j]->getScreenPosition();

                    Blocks[i][j]->CheckDeath();

                    if (Blocks[i][j]->isDead() && Blocks[i][j]->getFeature() == WithBonus)
                    {
                        for (int b = rand()%6; b < MaxBonuses; b++)
                        {
                            if (Bonuses[b]->getSpeed().y == 0)
                            {
                                Bonuses[b]->InitBonus(position_for_bonus);
                                printf("+Bonus\n");
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}


