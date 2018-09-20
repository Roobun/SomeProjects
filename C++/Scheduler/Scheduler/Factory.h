#pragma once

#include <string>

#include "FileCopy.h"
#include "OpenLink.h"
#include "PlayMusic.h"
#include "ShowMessage.h"

class Factory {
public:
   Factory() = default;
   ~Factory() = default;
   Task* Create(string taskName);
};

Task* Factory::Create(string taskName)
{
   if (taskName == "play_music") {
      return new PlayMusic;
   }
   if (taskName == "copy_file") {
      return new FileCopy;
   }
   if (taskName == "open") {
      return new OpenLink;
   }
   if (taskName == "show_message") {
      return new ShowMessage;
   }
   return nullptr;
}
