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
      keyboardFlag |= _UserInput::W;
      break;
   case sf::Keyboard::A:
      keyboardFlag |= _UserInput::A;
      break;
   case sf::Keyboard::S:
      keyboardFlag |= _UserInput::S;
      break;
   case sf::Keyboard::D:
      keyboardFlag |= _UserInput::D;
      break;
   case sf::Keyboard::E:
      keyboardFlag |= _UserInput::E;
      break;
   case sf::Keyboard::Space:
      keyboardFlag |= _UserInput::Space;
      break;
   case sf::Keyboard::Escape:
      keyboardFlag |= _UserInput::Escape;
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


bool UserInput::CheckKeyLevel(_UserInput::KeyboardFlags keyboardFlag)
{
   if(keyStates & keyboardFlag)  return true;
   else                          return false;
}


bool UserInput::CheckKeyEdge(_UserInput::Edge edgeType, _UserInput::KeyboardFlags keyboardFlag)
{
   if(!((prevKeyStates&keyboardFlag)^(keyStates&keyboardFlag)))
      return false;

   switch(edgeType)
   {
   case _UserInput::Rising:
      if(keyStates&keyboardFlag)    return true;
      else                          return false;
   case _UserInput::Falling:
      if(~keyStates&keyboardFlag)   return true;
      else                          return false;
   default:
      printf("(UserInput::CheckEdge()) No rising/falling edge specified?\n");
      return false;
   }
}


void UserInput::HandleInput()
{

}


void UserInput::HandleInput(_UserInput::GameType gameType)
{
   switch(gameType)
   {
   case _UserInput::TopDown:
      break;
   case _UserInput::Platformer:
      break;
   case _UserInput::TwinStick:
      break;
   default:
      break;
   }
}
