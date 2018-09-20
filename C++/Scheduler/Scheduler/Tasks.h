#pragma once
#include <string>

using namespace std;

class Task {
public:
   virtual ~Task() {};
   virtual void Init(string parameter) = 0;
   virtual void Run(const std::string parameter) = 0;
};