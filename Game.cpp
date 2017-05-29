#include "Game.h"

Game::Game()
{
   printf("Game constructor\n");
}

Game::~Game()
{
   printf("Game destructor\n");
}

void Game::GameLoop()
{

   sf::VideoMode videoMode(800,600);
   window.create(videoMode,"Game Window");

   sf::Clock gameClock;
   sf::Time timeSinceLastUpdate = sf::Time::Zero;
   sf::Time timePerFrame = sf::seconds(1.f/60.f);

   while(window.isOpen())
   {
      timeSinceLastUpdate += gameClock.restart();

      while(timeSinceLastUpdate > timePerFrame)
      {
         timeSinceLastUpdate -= timePerFrame;
         ProcessEvents();
         Update(timePerFrame.asSeconds());
      }

      Render();
   }
}

void Game::ProcessEvents()
{

   sf::Event event;
   while(window.pollEvent(event))
   {
      if(event.type == sf::Event::Closed)
      {
         window.close();
      }
   }

}

void Game::Update(float deltaT)
{

   if(level.GetLevelNumber() != 0){
      printf("Do we get here?\n");
      level.UpdateLevel(0);
      printf("Or here?\n");
   }

}

void Game::Render()
{
   window.clear(sf::Color::Black);
   window.draw(level);
   window.display();
}
