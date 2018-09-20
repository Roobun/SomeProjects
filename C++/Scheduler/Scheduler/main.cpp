#include "Factory.h"
#include "Scheduler.h"

int main(int argc, char *argv[])
{
   Factory f;
   Scheduler timetable(&f);

   timetable.Init(argv[1]);
   timetable.Launch();

   return 0;
}