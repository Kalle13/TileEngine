#include "Game.h"

Game::Game()
{
   printf("Game constructor\n");
   numberOfEntities = 0;
}

Game::~Game()
{
   printf("Game destructor\n");
   delete[] entity;
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

      if(userInput.CheckKeyEdge(_UserInput::Rising,_UserInput::Escape)){
         window.close();
      }
   }
}

void Game::Update(float deltaT)
{
   if(level.GetLevelNumber() != 0){
      level.ChangeLevel(0);
      InitEntities();
   }

   GameLogic(0);

   level.LevelToggleTiles(entity[0].GetPosition(),userInput.CheckKeyEdge(_UserInput::Rising,_UserInput::E));

   userInput.UpdateKeyStates();
}

void Game::GameLogic(float deltaT)
{
   if(userInput.CheckKeyEdge(_UserInput::Rising, _UserInput::W))  entity[0].UpdatePosition(entity[0].GetPosition() - sf::Vector2f(0,32));
   if(userInput.CheckKeyEdge(_UserInput::Rising, _UserInput::A))  entity[0].UpdatePosition(entity[0].GetPosition() - sf::Vector2f(32,0));
   if(userInput.CheckKeyEdge(_UserInput::Rising, _UserInput::S))  entity[0].UpdatePosition(entity[0].GetPosition() + sf::Vector2f(0,32));
   if(userInput.CheckKeyEdge(_UserInput::Rising, _UserInput::D))  entity[0].UpdatePosition(entity[0].GetPosition() + sf::Vector2f(32,0));
}


void Game::Render()
{
   window.clear(sf::Color::Black);
   window.draw(level);
   for(unsigned i=0;i<numberOfEntities;++i){
      window.draw(entity[i]);
   }
   window.display();
}


void Game::InitEntities()
{
   if(numberOfEntities>0){
      delete[] entity;
   }

   numberOfEntities = level.GetLevelNumberOfEntites();

   if(numberOfEntities == 0){
      printf("(Game::InitEntities) Level does not contain entities\n");
   }

   entity = new Entity[numberOfEntities];

   for(unsigned i=0;i<numberOfEntities;++i){
      if(!level.GetEntityData(i,entity[i])){
         printf("(Game::InitEntities) Error: Failed to obtain entity information from level data (entity index %d)\n",i);
      }
      entity[i].UpdateEntity();
   }
}
