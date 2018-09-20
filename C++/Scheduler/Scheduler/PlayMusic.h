#pragma once
#pragma comment(lib, "winmm")

#include "Tasks.h"
#include <iostream>
#include <windows.h>
#include <ShellAPI.h>

using namespace std;

class PlayMusic : public Task {
   string direction_;

public:
   ~PlayMusic() = default;
   void Init(string parameter);
   void Run(const std::string parameter);

};

void PlayMusic::Init(string parameter)
{
   direction_ = parameter;
}

void PlayMusic::Run(const std::string parameter)
{
   Init(parameter);

   try {
      PlaySoundA(direction_.c_str(), NULL, SND_FILENAME);
   } catch (...) {
      cout << "Invalid direction of a sound file." << endl;
   }
}