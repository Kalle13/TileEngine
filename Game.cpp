#include "Game.h"

Game::Game()
{
   printf("Game constructor\n");
   numberOfEntities = 0;
   timeAcc = 0;
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

   userInput.HandleInput();
}

void Game::Update(float deltaT)
{
   if(level.GetLevelNumber() != 0){
      level.ChangeLevel(0);
      InitEntities();
   }

   timeAcc += deltaT;
   GameLogic(0);

   userInput.UpdateKeyStates();
}

void Game::GameLogic(float deltaT)
{
   // Need to read gameInputFlags that were set in userInput.HandleInput() and respond accordingly
   // Check whether each input is a valid move before moving the player Entity

   unsigned gameInputs = userInput.GetGameInputFlags();

   sf::Vector2f currentEntityPosition = entity[0].GetPosition();

   bool wallUp    = level.CheckLevelForWalls(currentEntityPosition - sf::Vector2f(0,32));
   bool wallLeft  = level.CheckLevelForWalls(currentEntityPosition - sf::Vector2f(32,0));
   bool wallDown  = level.CheckLevelForWalls(currentEntityPosition + sf::Vector2f(0,32));
   bool wallRight = level.CheckLevelForWalls(currentEntityPosition + sf::Vector2f(32,0));

   if((gameInputs & _UserInput::MoveUp) && !wallUp)         entity[0].SetPosition(entity[0].GetPosition() - sf::Vector2f(0,32));
   if((gameInputs & _UserInput::MoveLeft) && !wallLeft)     entity[0].SetPosition(entity[0].GetPosition() - sf::Vector2f(32,0));
   if((gameInputs & _UserInput::MoveDown) && !wallDown)     entity[0].SetPosition(entity[0].GetPosition() + sf::Vector2f(0,32));
   if((gameInputs & _UserInput::MoveRight) && !wallRight)   entity[0].SetPosition(entity[0].GetPosition() + sf::Vector2f(32,0));
   if(gameInputs & _UserInput::Use)                         level.ToggleLevelTiles(entity[0].GetPosition(),true);

   entity[0].UpdateEntity();
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
