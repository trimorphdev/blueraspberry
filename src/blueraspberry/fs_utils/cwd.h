#ifndef _CWD_H
#define _CWD_H

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <iostream>
#include <string>

std::string cwd() {
   char buff[FILENAME_MAX];
   GetCurrentDir(buff, FILENAME_MAX);
   std::string current_working_dir(buff);
   return current_working_dir;
}

#endif