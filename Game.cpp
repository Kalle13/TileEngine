#include "Game.h"

Game::Game()
{
   printf("Game constructor\n");
   timeAccumulator = 0;
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
      if(event.type == sf::Event::KeyPressed)
      {
         userInput.SetInputState(event.key.code,true);
         printf("key pressed\n");
      }
      if(event.type == sf::Event::KeyReleased)
      {
         userInput.SetInputState(event.key.code,false);
         printf("key released\n");
      }
   }

}

void Game::Update(float deltaT)
{

   if(level.GetLevelNumber() != 0){
      printf("Do we get here?\n");
      level.ChangeLevel(0);
      printf("Or here?\n");
   }

   level.LevelUpdateTiles(sf::Vector2f(32,64),userInput.GetKeyState(sf::Keyboard::E));
/*
   timeAccumulator += deltaT;
   if(timeAccumulator>1.0){
      level.LevelUpdateTiles(sf::Vector2f(32,64),userInput.GetKeyState(sf::Keyboard::E));
      timeAccumulator = 0;
   }
*/
}

void Game::GameLogic(float deltaT)
{

}

void Game::Render()
{
   window.clear(sf::Color::Black);
   window.draw(level);
   window.display();
}
