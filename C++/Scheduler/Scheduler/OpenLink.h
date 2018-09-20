#pragma once

#include "Tasks.h"
#include <iostream>
#include <windows.h>

using namespace std;

class OpenLink : public Task {
   string link_;

public:
   ~OpenLink() = default;
   void Init(string parameter);
   void Run(const std::string parameter);
};

void OpenLink::Init(string parameter)
{
   link_ = parameter;
}

void OpenLink::Run(const std::string parameter)
{
   Init(parameter);

   try {
      ShellExecuteA(NULL, "open", link_.c_str(), NULL, NULL, SW_SHOW);
   } catch (...) {
      cout << "Invalid link." << endl;
   }
}