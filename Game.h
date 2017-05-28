#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

#include "UserInterface/UserInput.h"

class Game
{
public:

   sf::RenderWindow window;
   UserInput userInput;

   Game();
   ~Game();

   void GameLoop();
   void ProcessEvents();
   void Update(float deltaT);
   void Render();
};

#endif // _GAME_H_

