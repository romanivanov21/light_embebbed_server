#include <stdio.h>  /* defines FILENAME_MAX */
#include <string>
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GET_CURRENT_DIR _getcwd
#else
#include <unistd.h>
#define GET_CURRENT_DIR getcwd
#endif

#include "directory.h"

std::string sys::directory::get_current_directory()
{
    char buff[FILENAME_MAX];
    GET_CURRENT_DIR(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}