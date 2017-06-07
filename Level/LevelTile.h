#ifndef _LEVEL_TILE_H_
#define _LEVEL_TILE_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

#define TILE_WIDTH 32
#define TILE_HEIGHT 32


namespace Tile
{
   enum Type{Base, Wall, Gate, Switch};
}


class LevelTile : public sf::Drawable{
public:

   LevelTile(unsigned initTileIndex, float initTileBorderWidth, sf::Vector2f initTilePosition, Tile::Type initTileType,
             sf::Color initTileColor1, sf::Color initTileColor2) :
                tileIndex(initTileIndex),
                tileBorderWidth(initTileBorderWidth),
                tilePosition(initTilePosition),
                tileType(initTileType),
                tileColor1(initTileColor1),
                tileColor2(initTileColor2)
   {
      tileRectangle.setSize(sf::Vector2f(TILE_WIDTH,TILE_HEIGHT));
      tileRectangle.setOutlineThickness(initTileBorderWidth);
      tileRectangle.setFillColor(initTileColor1);
      tileRectangle.setOutlineColor(initTileColor2);
      tileRectangle.setOrigin(TILE_WIDTH/2,TILE_HEIGHT/2);
      tileRectangle.setPosition(initTilePosition);
   }
   virtual ~LevelTile() {};
   void           SetTileColors(sf::Color newTileColor1, sf::Color newTileColor2);
   void           SetTilePosition(sf::Vector2f newTilePosition);
   void           UpdateTileRectangle(sf::Vector2f newPosition, sf::Color newColor1, sf::Color newColor2);
   void           UpdateTileRectangleColor(sf::Color newRectColor1, sf::Color newRectColor2);
   void           ToggleTileColor();

   sf::Color      GetTileColor1()      {return tileColor1;}
   sf::Color      GetTileColor2()      {return tileColor2;}
   sf::Vector2f   GetTilePosition()    {return tilePosition;}

   bool           TestVectorCollision(sf::Vector2f testVector);
   bool           TestRectangleCollision(sf::FloatRect floatRect);

   Tile::Type     GetTileType()        {return tileType;}
   virtual void   UpdateTile() = 0;
   virtual void   ToggleTile() = 0;
   virtual bool   GetTileState() = 0;

protected:

   unsigned             tileIndex;     // Tile index helpful for when tiles need to act upon one another
   float                tileBorderWidth;
   sf::Vector2f         tilePosition;
   Tile::Type           tileType;
   sf::Color            tileColor1;
   sf::Color            tileColor2;
   sf::RectangleShape   tileRectangle;

private:

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(tileRectangle);
   }
};


class BaseTile : public LevelTile{
public:

   BaseTile(unsigned initTileIndex, sf::Vector2f initTilePosition,
            sf::Color initTileColor1, sf::Color initTileColor2) :
            LevelTile(initTileIndex, -0.5f, initTilePosition, Tile::Base, initTileColor1, initTileColor2)
   {}

   void UpdateTile() override;
   void ToggleTile() override;
   bool GetTileState() override;

};


class WallTile : public LevelTile{
public:

   WallTile(unsigned initTileIndex, sf::Vector2f initTilePosition,
            sf::Color initTileColor1, sf::Color initTileColor2,
            bool wallTileEnabled) :
               LevelTile(initTileIndex, -8.0f, initTilePosition, Tile::Wall, initTileColor1, initTileColor2),
               wallEnabled(wallTileEnabled)
   {}

   void UpdateTile() override;
   void ToggleTile() override;
   bool GetTileState() override;

   bool GetWallState(){return wallEnabled;}
   void SetWallState(bool setWallEnabled){wallEnabled = setWallEnabled;}    // Used to enable/disable a wall from a switch
   void ToggleWallState();

private:

   bool wallEnabled;

};


class GateTile : public LevelTile{
public:

   GateTile(unsigned initTileIndex, sf::Vector2f initTilePosition,
            sf::Color initTileColor1, sf::Color initTileColor2,
            bool initGateState) :
               LevelTile(initTileIndex, -2.0f, initTilePosition, Tile::Gate, initTileColor1, initTileColor2),
               gateOpen(initGateState)
   {}

   void           UpdateTile() override;
   void           ToggleTile() override;
   bool           GetTileState() override;

   bool           GetGateState()             {return gateOpen;}
   unsigned       GetLevelDestination()      {return levelDestination;}          // Returns level number of gate destination (for inter-level gates)
   sf::Vector2f   GetLocationDestination()   {return locationDestination;}       // Returns position of gate destination (for intra-level gates)

   void           SetGateState(bool gateIsOpen)                      {gateOpen = gateIsOpen;}
   void           SetLevelDestination(unsigned newLevel)             {levelDestination = newLevel;}
   void           SetLocationDestination(sf::Vector2f newLocation)   {locationDestination = newLocation;}
   void           ToggleGateState();

private:

   unsigned       levelDestination;          // Level to send player (can be same as current level number if gate "warps" player)
   bool           gateOpen;
   sf::Vector2f   locationDestination;       // Location in level to send player

};


class SwitchTile : public LevelTile{
public:

   SwitchTile(unsigned initTileIndex, sf::Vector2f initTilePosition,
              sf::Color initTileColor1, sf::Color initTileColor2,
              bool initSwitchState) :
                 LevelTile(initTileIndex, -12.0f, initTilePosition, Tile::Switch, initTileColor1, initTileColor2),
                 switchState(initSwitchState)
   {
      numSwitchedTiles = 0;
   }
   ~SwitchTile(){delete[] switchedTileIndexes;}

   void        UpdateTile() override;
   void        ToggleTile() override;
   bool        GetTileState() override;

   void        SetSwitchState(bool switchState);
   void        SetSwitchedTileIndexes(unsigned *tileIndexArray, unsigned numTileIndexes);
   bool        GetSwitchState(){return switchState;}
   void        ToggleSwitchState();

private:

   unsigned    numSwitchedTiles;       // Number of tiles associated with specific SwitchTile; these associated tiles will be toggled when their SwitchTile is toggled by the player
   bool        switchState;            // The current state of the SwitchTile
   unsigned    *switchedTileIndexes;   // Tile indexes can correspond to Wall, Gate, or other Switch tiles to turn a Wall off, open/close a gate, or toggle another switch

};

#endif // _LEVEL_TILE_H_
