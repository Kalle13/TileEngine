#ifndef _USER_INPUT_H_
#define _USER_INPUT_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class UserInput
{
public:

   enum KeyboardFlags
   {
      W = 0x1,
      A = 0x2,
      S = 0x4,
      D = 0x8,
      E = 0x10,
      Space = 0x12,
      Escape = 0x14
   };

   UserInput() : keyboardFlags(0), wKey(false), aKey(false), sKey(false), dKey(false), spaceKey(false), escapeKey(false) {}
   void SetInputState(sf::Keyboard key, bool isKeyPressed);
   unsigned GetInputState(){return keyboardFlags;}
   bool GetKeyState(sf::Keyboard key);

private:

   unsigned keyboardFlags;
   bool wKey;
   bool aKey;
   bool sKey;
   bool dKey;
   bool spaceKey;
   bool escapeKey;

};

#endif // _USER_INPUT_H_
