//
// Created by roucr on 20.08.2023.
//

#include "Game.h"

Game::Game()
{
    Init = new Initializer;

    paddle = Init->getpaddleptr();
    Bonuses = Init->getbonusesptr();
    Blocks = Init->getblocksptr();
    ball = Init->getballsptr();

    Build = new Builder(ball, Bonuses, paddle, Blocks);
}


Game::~Game()
{
    delete Init;
    delete Build;
}


void Game::Play()
{
    //Window settings
    sf::RenderWindow window;
    window.create(sf::VideoMode(DisplayX, DisplayY), "Arkanoid!");
    window.setFramerateLimit(FPS);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("resourses/background3.png"); //need to think about textures
    sf::Sprite background(backgroundTexture);
    sf::Font font;
    font.loadFromFile("resourses/FONT.ttf");
    sf::Text livesText("", font, 30);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(780, 710);
    Interface UI(&window);


    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        window.draw(background);
        UI.Render(Build);
        window.draw(livesText);
        livesText.setString("Lives: " + std::to_string(Build->getRemainingLives()));
       // sf::Vector2i mousePosition = sf::Mouse::getPosition(window); //cringe to check coords
       // std::cout << "Mouse X: " << mousePosition.x << ", Mouse Y: " << mousePosition.y << std::endl;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Build->getGameStatus() == -1 || Build->getGameStatus() == 1 )
                window.close();
        }
        window.display();
    }
}