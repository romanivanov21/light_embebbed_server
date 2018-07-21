#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <string>

namespace sys
{
    class directory
    {
    public:
        static std::string get_current_directory();
    };
}

#endif //_DIRECTORY_H_
