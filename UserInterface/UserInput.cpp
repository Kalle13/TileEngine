#include "UserInput.h"

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


void UserInput::SetGameInputFlag(_UserInput::GameInputFlags gameInputFlag, bool setFlag)
{
   unsigned tempGameInputFlag = 0;

   switch(gameInputFlag)
   {
   case _UserInput::MoveUp:
      tempGameInputFlag |= _UserInput::MoveUp;
      break;
   case _UserInput::MoveLeft:
      tempGameInputFlag |= _UserInput::MoveLeft;
      break;
   case _UserInput::MoveDown:
      tempGameInputFlag |= _UserInput::MoveDown;
      break;
   case _UserInput::MoveRight:
      tempGameInputFlag |= _UserInput::MoveRight;
      break;
   case _UserInput::Use:
      tempGameInputFlag |= _UserInput::Use;
      break;
   case _UserInput::ChangeColor:
      tempGameInputFlag |= _UserInput::ChangeColor;
      break;
   case _UserInput::ExitGame:
      tempGameInputFlag |= _UserInput::ExitGame;
      break;
   default:
      break;
   }

   if(setFlag){
      gameInputFlags |= tempGameInputFlag;
   } else {
      gameInputFlags &= ~tempGameInputFlag;
   }
}


void UserInput::HandleInput()
{
   if(CheckKeyEdge(_UserInput::Rising,_UserInput::W))       gameInputFlags |= _UserInput::MoveUp;
   else                                                     gameInputFlags &= ~_UserInput::MoveUp;

   if(CheckKeyEdge(_UserInput::Rising,_UserInput::A))       gameInputFlags |= _UserInput::MoveLeft;
   else                                                     gameInputFlags &= ~_UserInput::MoveLeft;

   if(CheckKeyEdge(_UserInput::Rising,_UserInput::S))       gameInputFlags |= _UserInput::MoveDown;
   else                                                     gameInputFlags &= ~_UserInput::MoveDown;

   if(CheckKeyEdge(_UserInput::Rising,_UserInput::D))       gameInputFlags |= _UserInput::MoveRight;
   else                                                     gameInputFlags &= ~_UserInput::MoveRight;

   if(CheckKeyEdge(_UserInput::Rising,_UserInput::E))       gameInputFlags |= _UserInput::Use;
   else                                                     gameInputFlags &= ~_UserInput::Use;

   if(CheckKeyEdge(_UserInput::Rising,_UserInput::Space))   gameInputFlags |= _UserInput::ChangeColor;
   else                                                     gameInputFlags &= ~_UserInput::ChangeColor;

   if(CheckKeyEdge(_UserInput::Rising,_UserInput::Escape))  gameInputFlags |= _UserInput::ExitGame;
   else                                                     gameInputFlags &= ~_UserInput::ExitGame;
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
