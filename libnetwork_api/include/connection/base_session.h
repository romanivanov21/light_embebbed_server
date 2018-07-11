#ifndef _BASE_SESSION_H_
#define _BASE_SESSION_H_

#include "event.h"
#include "connection_traits.h"

namespace network
{
    class base_session
    {
    public:
        virtual ~base_session() = default;

        virtual void start() = 0;

        virtual const network::slave_connection*
               get_slave_connection() const = 0;

    public:
        event<base_session*> end;

    protected:
        event<void> received;
    };
}

#endif //_BASE_SESSION_H_
