#ifndef _BASE_SERVER_H_
#define _BASE_SERVER_H_

// internal library common
#include "event.h"

//std
#include <string>
#include <functional>

namespace network
{
    class base_server
    {
    public:
        using connection_error
        = std::function<void(const std::string&)>;

        virtual ~base_server() = default;

        virtual void run() = 0;

        virtual void stop() = 0;
    protected:
        event<void(const std::string&)> server_error;
        bool is_cancel_;
    };
}

#endif //_BASE_SERVER_H_
