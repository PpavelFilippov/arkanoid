//
// Created by roucr on 19.08.2023.
//

#include "Interface.h"

void Interface::Render(Builder *Manager) const
{
    DrawObjects(Manager);
    Manager->MakeFrame();
}

void Interface::DrawObjects(Builder *Manager) const
{
    //Paddle
    Manager->getPaddle()->Draw(window);

    //Balls
        Manager->getBall()->Draw(window);


    //Blocks
    for (int i = 0; i < Manager->getFieldSize().x; i++)
    {
        for (int j = 0; j < Manager->getFieldSize().y; j++)
        {
            Manager->getBlock(i, j)->Draw(window);
        }
    }

    //Bonuses
    for (int i = 0; i < Manager->getMaxBonuses(); i++)
    {
        Manager->getBonus(i)->Draw(window);
    }

}