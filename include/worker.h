#ifndef _WORKER_H_
#define _WORKER_H_

//internal library thread_api
#include "thread_save_queue.h"

#include "base_session.h"

//std
#include <memory>

class worker
{
public:
    explicit worker(sys::thread_save_queue<network::base_session*>&);
    ~worker();

    void start();
    void stop();
private:
    struct impl;
    std::unique_ptr<impl> d_;
};

#endif //s_WORKER_H_
