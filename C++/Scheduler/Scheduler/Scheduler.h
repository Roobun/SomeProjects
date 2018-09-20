#pragma once

#include <map>
#include <ctime>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Factory.h"
#include "Tasks.h"

#define SECONDS_IN_DAY 86400

using namespace std;

class Scheduler {
   ifstream fin_;
   void Parser();

   int time_;
   string task_;

   Factory* factory_;
   void Access(time_t rawtime);
   void MakeTask(multimap<int, string>::iterator it);

   vector<thread> threads;
   void Check();

   void Screen(time_t rawtime);

 protected:
   multimap <int, string> timetable_;

   int CountTime(string timeString);
   
public:
   Scheduler(Factory* f);
   ~Scheduler() = default;

   void Init(const std::string fileName);
   void Launch();

};

Scheduler::Scheduler(Factory *f)
{
   factory_ = f;
}

int Scheduler::CountTime(string timeString)
{
   return ((timeString[0] - '0') * 10 + (timeString[1] - '0')) * 3600 +
          ((timeString[3] - '0') * 10 + (timeString[4] - '0')) * 60 + 
          ((timeString[6] - '0') * 10 + (timeString[7] - '0'));
}

void Scheduler::Init(const std::string fileName)
{
   try {
      fin_.open(fileName.c_str(), ios::in);
   } catch (...) {
      cout << "Invalid file's direction." << endl;
   }
   
   Parser();
}

void Scheduler::Parser()
{
   string timeString;
   while (fin_.eof() != true) {
      fin_ >> timeString;
      time_ = CountTime(timeString);

      getline(fin_, task_);
      task_.erase(0, 1);

      timetable_.insert(pair<int, string>(time_, task_));
   }
   fin_.close();
}

void Scheduler::MakeTask(multimap<int, string>::iterator it)
{
   stringstream ss;
   string taskName;

   ss << it->second;
   ss >> taskName;

   unsigned int position = it->second.find(" ");
   it->second.erase(0, position + 1);

   unique_ptr<Task> task(factory_->Create(taskName));

   thread tr(&Task::Run, move(task), it->second);
   threads.push_back(move(tr));
}

void Scheduler::Access(time_t rawtime)
{
   typedef multimap<int, string>::iterator MyMapIterator;

   pair <MyMapIterator, MyMapIterator> pairIt;
   pairIt = timetable_.equal_range((int)rawtime);

   for (MyMapIterator it = pairIt.first; it != pairIt.second; it++) {
      MakeTask(it);
   }

   timetable_.erase((int)rawtime);
}

void Scheduler::Check()
{
   while (threads.empty() == false) {
      if (threads.back().joinable() == true) {
         threads.back().join();
      }
      threads.pop_back();
   }
}

void Scheduler::Launch()
{
   while (timetable_.empty() == false) {
      clock_t start, end;
      time_t rawtime;
      struct tm *tmTemp;

      system("cls");
      start = clock();

      time(&rawtime);
      tmTemp = localtime(&rawtime);
      rawtime = tmTemp->tm_hour * 3600 + tmTemp->tm_min * 60 + tmTemp->tm_sec;

      rawtime %= SECONDS_IN_DAY;

      Screen(rawtime);

      Access(rawtime);

      do {
         end = clock();
      } while (1.0 - (float)(end - start)/CLOCKS_PER_SEC);
   }

   Check(); // treads safety before ends program
}

void Scheduler::Screen(time_t rawtime)
{
   int sub, hour, min, sec;

   typedef multimap<int, string>::iterator MyMapIterator;

   for (MyMapIterator it = timetable_.begin(); it != timetable_.end(); it++) {
      sub = ((int)(it->first - rawtime) + 86400) % 86400;

      hour =  ((sub / 3600)       + 24) % 24;
      min  = (((sub % 3600) / 60) + 60) % 60;
      sec  = (((sub % 3600) % 60) + 60) % 60;

      printf("%02d:%02d:%02d before ", hour, min, sec);
      cout << it->second << endl << endl;
   }
}
