#pragma once

#include "Unit.h"
#include <cctype>

class Pacman : public Unit {
   void DeathAnimation();

public: 
   void Init();

   void Control(char button);
   void Movement(Map *map);

   char Direction();

   ~Pacman() = default;
};

void Pacman::Init()
{
   (*this).coordinates_ = {23, 13}; // compare it with reality plz
   
   vector_ = LEFT;
   isStarted_ = 0;

   Show(Direction());
}

void Pacman::Control(char button)
{
   button = tolower(button);
   switch (button) {
   case 'w': 
      vector_ = UP;
      break;
   case 'a':
      vector_ = LEFT;
      break;
   case 's':
      vector_ = DOWN;
      break;
   case 'd':
      vector_ = RIGHT;
      break;
   }
   // you can expand to pause button
}

void Pacman::Movement(Map *map)
{
   isStarted_ = 1;
   iPair P = sumCoordinates(coordinates_, vector2Pair(vector_));

   if (vector_ == LEFT && coordinates_.first == 14 && coordinates_.second == 0) { // left tp
      colorWhite;
      Show(' ');
      map->changeObject(getCoordinates(), ' ');  // place where've been pacman

      (*this).changeCoordinates({14, 28});

      colorYellow;
      Show(Direction());
      map->changeObject(getCoordinates(), Direction());          // place where pacman is now

      return;
   }

   if (vector_ == RIGHT && coordinates_.first == 14 && coordinates_.second == 27) { // right tp
      colorWhite;
      Show(' ');
      map->changeObject(getCoordinates(), ' ');  // place where've been pacman

      (*this).changeCoordinates({14, 0});

      colorYellow;
      Show(Direction());
      map->changeObject(getCoordinates(), Direction());          // place where pacman is now

      return;
   }

   char temp = map->getObject(P.first, P.second);

   if (temp == GHOST || map->getObject(coordinates_.first, coordinates_.second) == GHOST) {
      if (map->isEnergy() == FALSE) {
         isStarted_ = 0;
         DeathAnimation();

         iPair temporary = getCoordinates();
         changeCoordinates(P);
         Show(' ');

         changeCoordinates(temporary);
         Show(' ');
         map->changeObject(getCoordinates(), ' ');

         map->Death();
         map->PacmansDeath(TRUE);
         Init();
         return;
      } else {
         colorRed;
         Show('+');

         iPair temporary = getCoordinates();
         changeCoordinates(P);

         Show('+');
         changeCoordinates(temporary);

         map->addPoints(200);
         Sleep(700);
         return;
      }
   }

   if (temp == SPACE || temp == FOOD || temp == ENERGIZER) {
      if (temp == FOOD) {
         map->addPoints(10);
      }

      if (temp == ENERGIZER) {
         map->addPoints(100);
         map->Energy();
      }

      colorWhite;
      Show(' ');
      map->changeObject(getCoordinates(), ' ');  // place where've been pacman

      (*this).changeCoordinates(P);

      colorYellow;
      Show(Direction());
      map->changeObject(P, Direction());          // place where pacman is now
      
      return;
   }
   
   colorYellow;
   Show(Direction());
   map->changeObject(getCoordinates(), Direction());
   //isStarted_ = 0;
}

char Pacman::Direction()
{
   switch (vector_) {
   case UP:
      return 'v';
   case LEFT:
      return '>';
   case DOWN:
      return '^';
   case RIGHT:
      return '<';
   }
}

void Pacman::DeathAnimation()
{
   colorYellow;
   vector_ = UP;
   Show(Direction());
   Sleep(100);

   vector_ = LEFT;
   Show(Direction());
   Sleep(100);

   vector_ = DOWN;
   Show(Direction());
   Sleep(100);

   vector_ = RIGHT;
   Show(Direction());
   Sleep(100);
}