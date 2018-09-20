#pragma once

#include "Unit.h"
#include "User.h"
#include <ctime>
#include <cmath>

class Ghost : public Unit {

   const char appearence_ = 'M';
   float calculateLenght(iPair pacman, iPair ghost);
   void Wait(int time);

   char temp_;
   void checkDirection(Map map, bool arr[4]);
   void Invert();

public:
   void Init();
   void otherInit(int x, int y, direction vector);
   char Appearence();

   void Movement(Map *map);
   void Energizer(Map *map, bool *first, Pacman pacman, bool *escape, int x, int y);

   void LookAround(Map map, iPair purpose);
   void Gone2Home(Map *map);

   ~Ghost() = default;
};

float Ghost::calculateLenght(iPair pacman, iPair ghost)
{
   short Xx =pacman.first - ghost.first;
   Xx *= Xx;
   short Yy = pacman.second - ghost.second;
   Yy *= Yy;

   return (float)sqrt(Xx + Yy);
}

void Ghost::Wait(int time)
{
   clock_t start, end;
   start = clock();

   do {
      end = clock();
   } while (time - (float)(end - start) / CLOCKS_PER_SEC > 0);
}

void Ghost::Init()
{
   (*this).coordinates_ = {11, 13};
   temp_ = ' ';

   vector_ = LEFT;
   isStarted_ = 1;

   colorRed;
   Show(Appearence());
}

void Ghost::otherInit(int x, int y, direction vector)
{
   Init();
   coordinates_.first = x;
   coordinates_.second = y;

   vector_ = vector;
}

char Ghost::Appearence()
{
   return appearence_;
}

void Ghost::Movement(Map *map)
{
   if (map->isDead() == TRUE) {
      Show(' ');
      map->changeObject(getCoordinates(), ' ');

      Init();
      map->PacmansDeath(FALSE);
      return;
   }

   iPair P = sumCoordinates(coordinates_, vector2Pair(vector_));

   if (temp_ != GHOST) {
      colorWhite;
      Show(temp_);
      map->changeObject(getCoordinates(), temp_);

   }

   temp_ = map->getObject(P.first, P.second);

   map->changeObject(P, Appearence());

   changeCoordinates(P);
      
   colorRed;
   Show(Appearence());
}

void Ghost::LookAround(Map map, iPair purpose)
{
   bool direction[4] = {FALSE, FALSE, FALSE, FALSE};

   checkDirection(map, direction);

   float min = 0.0;
   float current;

   if (direction[0] == TRUE) {
      iPair xy = sumCoordinates(getCoordinates(), vector2Pair(UP));
      current = calculateLenght(purpose, xy);
      if (current < min || min == 0) {
         min = current;
         vector_ = UP;
      }
   }

   if (direction[1] == TRUE) {
      iPair xy = sumCoordinates(getCoordinates(), vector2Pair(LEFT));
      current = calculateLenght(purpose, xy);
      if (current < min || min == 0) {
         min = current;
         vector_ = LEFT;
      }
   }

   if (direction[2] == TRUE) {
      iPair xy = sumCoordinates(getCoordinates(), vector2Pair(DOWN));
      current = calculateLenght(purpose, xy);
      if (current < min || min == 0) {
         min = current;
         vector_ = DOWN;
      }
   }

   if (direction[3] == TRUE) {
      iPair xy = sumCoordinates(getCoordinates(), vector2Pair(RIGHT));
      current = calculateLenght(purpose, xy);
      if (current < min || min == 0) {
         min = current;
         vector_ = RIGHT;
      }
   }

   if (vector_ == LEFT && coordinates_.first == 14 && coordinates_.second == 0) {
      vector_ = RIGHT;
   }

   if (vector_ == RIGHT && coordinates_.first == 14 && coordinates_.second == 27) {
      vector_ = LEFT;
   }
}

void Ghost::checkDirection(Map map, bool arr[4])
{
   int x = coordinates_.first;
   int y = coordinates_.second;

   if (map.getObject(x - 1, y) != WALL && vector_ != DOWN  && map.getObject(x - 1, y) != DOOR) {
      arr[0] = TRUE;
   }

   if (map.getObject(x, y - 1) != WALL && vector_ != RIGHT && map.getObject(x, y - 1) != DOOR) {
      arr[1] = TRUE;
   }

   if (map.getObject(x + 1, y) != WALL && vector_ != UP    && map.getObject(x + 1, y) != DOOR) {
      arr[2] = TRUE;
   }

   if (map.getObject(x, y + 1) != WALL && vector_ != LEFT  && map.getObject(x, y + 1) != DOOR) {
      arr[3] = TRUE;
   }
}

void Ghost::Invert()
{
   switch (vector_) {
   case UP:
      vector_ = DOWN;
      break;
   case LEFT:
      vector_ = RIGHT;
      break;
   case DOWN:
      vector_ = UP;
      break;
   case RIGHT:
      vector_ = LEFT;
      break;
   }
}

void Ghost::Energizer(Map *map, bool *first, Pacman pacman, bool *escape, int x, int y)
{  
   iPair P = sumCoordinates(coordinates_, vector2Pair(vector_));

   if (getCoordinates() == pacman.getCoordinates() || P == pacman.getCoordinates() || (*escape) == TRUE) {
      (*escape) = TRUE;
      Gone2Home(map);
      return;
   }

   if (*first) {
      (*first) = FALSE;
      Invert();

   } else {
      LookAround(*map, {x, y});
   }
   
   Movement(map);
   colorWhite;
   Show(Appearence());
}

void Ghost::Gone2Home(Map *map)
{
   LookAround(*map, {11, 13});
   Movement(map);

   LookAround(*map, {11, 13});
   Movement(map);

   colorWhite;
   Show(Appearence());
}
