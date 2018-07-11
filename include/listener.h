#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "connection_traits.h"
#include "thread_save_queue.h"
#include "base_session.h"

#include <memory>

class listener
{
public:
    listener(network::endpoint_unique_ptr&,
      sys::thread_save_queue<network::base_session*>&);

    ~listener();

    void start();
    void stop();

private:
    struct impl;
    std::unique_ptr<impl> d_;
};

#endif //_LISTENER_H_
