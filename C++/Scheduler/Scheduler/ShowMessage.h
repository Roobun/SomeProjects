#pragma once

#include "Tasks.h"
#include <windows.h>

using namespace std;

class ShowMessage : public Task {
   string message_;

public: 
   ~ShowMessage() = default;
   void Init(string parameter);
   void Run(const std::string parameter);
};

void ShowMessage::Init(string parameter)
{
   message_ = parameter;
}

void ShowMessage::Run(const std::string parameter)
{
   Init(parameter);

   MessageBox(NULL, message_.c_str(), "Ok", MB_OK);
}