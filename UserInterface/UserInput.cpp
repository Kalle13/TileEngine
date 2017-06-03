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
      printf("(UserInput::SetInputState()) Key not mapped to input\n");
      break;
   }
}

bool UserInput::GetInputState(sf::Keyboard::Key key)
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


void UserInput::SetKeyState(sf::Keyboard::Key key, bool state)
{
   unsigned keyboardFlag = 0;

   switch(key)
   {
   case sf::Keyboard::W:
      keyboardFlag |= UserInterface::W;
      break;
   case sf::Keyboard::A:
      keyboardFlag |= UserInterface::A;
      break;
   case sf::Keyboard::S:
      keyboardFlag |= UserInterface::S;
      break;
   case sf::Keyboard::D:
      keyboardFlag |= UserInterface::D;
      break;
   case sf::Keyboard::E:
      keyboardFlag |= UserInterface::E;
      break;
   case sf::Keyboard::Space:
      keyboardFlag |= UserInterface::Space;
      break;
   case sf::Keyboard::Escape:
      keyboardFlag |= UserInterface::Escape;
      break;
   default:
      printf("(UserInput::SetKeyState()) Key not mapped to input\n");
      break;
   }

   if(state){
      keyStates |= keyboardFlag;
   } else {
      keyStates &= ~keyboardFlag;
   }

   //printf("prevKeyStates: 0x%.8x\n    KeyStates: 0x%.8x\n",prevKeyStates,keyStates);
}


bool UserInput::CheckKeyLevel(UserInterface::KeyboardFlags keyboardFlag)
{
   if(keyStates & keyboardFlag){
      //prevKeyStates |= keyStates;
      return true;
   } else {
      //prevKeyStates &= ~keyboardFlag;
      return false;
   }
}


bool UserInput::CheckKeyEdge(UserInterface::Edge edgeType, UserInterface::KeyboardFlags keyboardFlag)
{
   if(!((prevKeyStates&keyboardFlag)^(keyStates&keyboardFlag)))
   {
      return false;
   }

   switch(edgeType)
   {
   case UserInterface::Rising:
      if(keyStates&keyboardFlag)    return true;
      else                          return false;
   case UserInterface::Falling:
      if(~keyStates&keyboardFlag)   return true;
      else                          return false;
   default:
      printf("(UserInput::CheckEdge()) No rising/falling edge specified?\n");
      return false;
   }
}
