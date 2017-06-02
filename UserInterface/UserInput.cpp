#include "UserInput.h"

void UserInput::SetInputState(sf::Keyboard::Key key, bool isKeyPressed)
{
   switch(key)
   {
   case sf::Keyboard::W:
      wKey = isKeyPressed;
      break;
   case sf::Keyboard::A:
      aKey = isKeyPressed;
      break;
   case sf::Keyboard::S:
      sKey = isKeyPressed;
      break;
   case sf::Keyboard::D:
      dKey = isKeyPressed;
      break;
   case sf::Keyboard::E:
      eKey = isKeyPressed;
      break;
   case sf::Keyboard::Space:
      spaceKey = isKeyPressed;
      break;
   case sf::Keyboard::Escape:
      escapeKey = isKeyPressed;
      break;
   default:
      printf("Key not mapped to input\n");
      break;
   }
}

bool UserInput::GetKeyState(sf::Keyboard::Key key)
{
   switch(key)
   {
   case sf::Keyboard::W:
      return wKey;
   case sf::Keyboard::A:
      return aKey;
   case sf::Keyboard::S:
      return sKey;
   case sf::Keyboard::D:
      return dKey;
   case sf::Keyboard::E:
      return eKey;
   case sf::Keyboard::Space:
      return spaceKey;
   case sf::Keyboard::Escape:
      return escapeKey;
   default:
      return false;
   }

   return false;
}
