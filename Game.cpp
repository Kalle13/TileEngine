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
      switch(event.type)
      {
      case sf::Event::Closed:
         window.close();
         break;
      case sf::Event::KeyPressed:
         userInput.SetKeyState(event.key.code,true);
         break;
      case sf::Event::KeyReleased:
         userInput.SetKeyState(event.key.code,false);
         break;
      default:
         break;
      }
   }

}

void Game::Update(float deltaT)
{
   if(level.GetLevelNumber() != 0){
      level.ChangeLevel(0);
   }

   if(userInput.CheckKeyEdge(UserInterface::Rising,UserInterface::W))
      printf("W key rising edge detected\n");
   if(userInput.CheckKeyEdge(UserInterface::Falling,UserInterface::W))
      printf("W key falling edge detected\n");

   level.LevelUpdateTiles(sf::Vector2f(32,64),userInput.CheckKeyEdge(UserInterface::Rising,UserInterface::E));

   userInput.UpdateKeyStates();
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
