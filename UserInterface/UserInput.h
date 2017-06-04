#ifndef _USER_INPUT_H_
#define _USER_INPUT_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace _UserInput
{
   enum KeyboardFlags
   {
      W = 0x1,
      A = 0x2,
      S = 0x4,
      D = 0x8,
      E = 0x10,
      Space = 0x20,
      Escape = 0x40
   };

   enum GameInputFlags
   {
      MoveUp      = 0x1,
      MoveLeft    = 0x2,
      MoveDown    = 0x4,
      MoveRight   = 0x8,
      Use         = 0x10,
      ChangeColor = 0x20,
      ExitGame    = 0x40
   };

   enum Edge{Rising, Falling};   // Rising = key press; Falling = key release
   enum Level{High, Low};        // Make sure there aren't any name collisions with the "Level" class

   enum GameType{TopDown, Platformer, TwinStick};
}

class UserInput
{
public:

   UserInput() : keyStates(0), prevKeyStates(0), gameInputFlags(0), wKey(false), aKey(false), sKey(false), dKey(false), eKey(false), spaceKey(false), escapeKey(false) {}
   void        UpdateKeyStates(){prevKeyStates = keyStates;}         // Function to update prevKeyStates for any unhandled inputs at end of Game::Update() method
   void        SetInputState(sf::Keyboard::Key key, bool isKeyPressed);
   bool        GetInputState(sf::Keyboard::Key key);
   void        SetKeyState(sf::Keyboard::Key key, bool state);
   unsigned    GetKeyState(){return keyStates;}
   unsigned    GetPrevKeyState(){return prevKeyStates;}
   bool        CheckKeyLevel(_UserInput::KeyboardFlags keyboardFlag);
   bool        CheckKeyEdge(_UserInput::Edge edgeType, _UserInput::KeyboardFlags keyboardFlag);

   void        HandleInput();
   void        HandleInput(_UserInput::GameType gameType);  // Function to handle user input in a context-specific manner (may not be a good idea)

private:

   unsigned    keyStates;        // Updated every time a keyboard button is pressed
   unsigned    prevKeyStates;    // Updated after a CheckLevel or CheckEdge function call
   unsigned    gameInputFlags;
   bool        wKey;
   bool        aKey;
   bool        sKey;
   bool        dKey;
   bool        eKey;
   bool        spaceKey;
   bool        escapeKey;

};

#endif // _USER_INPUT_H_
