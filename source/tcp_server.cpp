//internal
#include "tcp_server.h"
#include "worker.h"
#include "listener.h"

//internal library network_api
#include "tcp_master_connection.h"
#include "base_session.h"

//internal library therad_api
#include "joinable_thread.h"
#include "thread_save_queue.h"

//namespace network
using network::base_session;
using network::endpoint_unique_ptr;
using network::master_connection_shared_ptr;
using network::tcp_master_connection;

using sys::joinable_thread;
using sys::thread_save_queue;

struct tcp_server::impl
{
    impl(endpoint_unique_ptr& ep);

    std::unique_ptr<listener> listener_ = nullptr;
    std::vector<std::unique_ptr<worker> > workers_;
    thread_save_queue<base_session*> session_queue_;
};

tcp_server::impl::impl(endpoint_unique_ptr& ep)
{
    listener_ = std::make_unique<listener>(ep, session_queue_);
    for(auto i = 0; i < joinable_thread::hardware_concurrency(); ++i)
    {
        workers_.push_back(std::make_unique<worker>
                   (session_queue_));
    }
}

tcp_server::tcp_server(endpoint_unique_ptr& ep)
    : d_(std::make_unique<impl>(ep))
{ }

tcp_server::~tcp_server() = default;

void tcp_server::run()
{
    d_->listener_->start();
    for(auto& w : d_->workers_)
    {
        w->start();
    }
}

void tcp_server::stop()
{
    d_->listener_->stop();
    for(auto& w : d_->workers_)
    {
        w->stop();
    }
}
