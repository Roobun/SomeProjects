#pragma once

#include "Tasks.h"
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>

using namespace std;

class FileCopy : public Task {
   string from_;
   string to_;

public:
   ~FileCopy() = default;
   void Init(string parameter);
   void Run(const std::string parameter);

};

void FileCopy::Init(string parameter)
{
   stringstream ss;

   ss << parameter;
   ss >> from_;

   ss << parameter;
   ss >> to_;
   
}

void FileCopy::Run(const std::string parameter)
{
   Init(parameter);

   try {
      CopyFile(from_.c_str(), to_.c_str(), false);
   } catch (...) {
      cout << "Invalid direction of a file." << endl;
   }
}