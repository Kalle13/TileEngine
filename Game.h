#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

#include "Entity/Entity.h"
#include "Level/Level.h"
#include "UserInterface/UserInput.h"

class Game
{
public:

   unsigned numberOfEntities;
   sf::RenderWindow window;
   UserInput userInput;
   Level level;
   Entity *entity;

   Game();
   ~Game();

   void GameLoop();
   void ProcessEvents();
   void Update(float deltaT);
   void GameLogic(float deltaT);
   void Render();

   // Function to initialize entities after the level changes
   void InitEntities();
};

#endif // _GAME_H_

