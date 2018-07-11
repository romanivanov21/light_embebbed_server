//internal
#include "worker.h"

//internal library thread_api
#include "joinable_thread_traits.h"
#include "joinable_thread.h"
#include "cancellation_token.h"
#include "thread_save_queue.h"

//internal library network_api
#include "connection_traits.h"
#include "base_session.h"
#include "selector_epoll.h"
#include "slave_connection.h"

//std
#include <memory>
#include <functional>
#include <mutex>

//namespace sys
using sys::joinable_thread;
using sys::joinable_thread_unique_ptr;
using sys::thread_save_queue;

//namespace thread_api
using network::selector_epoll;
using network::base_session;
using network::slave_connection;


struct worker::impl
{
    impl(thread_save_queue<network::base_session *>&);

    void run(cancellation_token&);

    void on_data_ready(const base_session* session);

    void on_end_session(base_session* session);

    thread_save_queue<base_session*>& session_queue_; /* the thread save queue                  */
    joinable_thread_unique_ptr therad_ = nullptr;     /* joinable raii thread                   */
    selector_epoll selector_;                         /* linux kernel async network event queue */
};

worker::impl::impl(thread_save_queue<base_session*>& session_queue)
    : session_queue_(session_queue), therad_(nullptr)
{
    selector_.data_ready_callback
            (std::bind(&worker::impl::on_data_ready, this,
                       std::placeholders::_1));
}

void worker::impl::run(cancellation_token& token)
{
    while(token)
    {
        selector_.check_data_ready(10, 100);
        base_session* session = nullptr;
        if(session_queue_.try_pop(session))
        {
            session->end.connect(std::bind(&worker::impl::on_end_session,
                                 this, std::placeholders::_1));
            selector_.add_connection(session);
        }
    }
}

void worker::impl::on_data_ready(const base_session* session)
{
    if(session)
    {
        slave_connection* connection
                = const_cast<slave_connection*>
                (session->get_slave_connection());
        if(connection)
        {
            connection->data_ready.emit();
        }
    }
}

void worker::impl::on_end_session(base_session* session)
{
    selector_.delete_connection(session);
}

worker::worker(thread_save_queue<base_session*>& session_queue)
    : d_(std::make_unique<impl>(session_queue))
{
}

worker::~worker()
{
}

void worker::start()
{
    d_->therad_ = std::make_unique<joinable_thread>
            (std::bind(&worker::impl::run, d_.get(),
                       std::placeholders::_1));
}

void worker::stop()
{
    d_->therad_->interrupt();
}
