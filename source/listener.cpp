#include "listener.h"
#include "session_handler.h"

//internal library network_api
#include "endpoint.h"
#include "master_connection.h"
#include "tcp_master_connection.h"
#include "slave_connection.h"
#include "tcp_slave_connection.h"
#include "base_session.h"
#include "connection_error.h"
#include "base_session.h"

//internal library thread_api
#include "joinable_thread.h"
#include "joinable_thread_traits.h"
#include "thread_save_queue.h"
#include "cancellation_token.h"

#include <iostream>

using network::endpoint_unique_ptr;
using network::base_session;
using network::master_connection_unique_ptr;
using network::tcp_master_connection;
using network::slave_connection;
using network::connection_error;

using sys::joinable_thread;
using sys::joinable_thread_unique_ptr;
using sys::thread_save_queue;

struct listener::impl
{
    impl(endpoint_unique_ptr&,
         thread_save_queue<network::base_session *>&);

    void run(cancellation_token&);

    void on_connected(slave_connection*);

    void on_connection_error(const connection_error&);

    master_connection_unique_ptr      master_connection_;
    thread_save_queue<base_session*>& session_queue_;
    joinable_thread_unique_ptr        thread_ = nullptr;
};

listener::impl::impl(endpoint_unique_ptr &ep,
                     thread_save_queue<base_session*>& session_queue)
    : master_connection_(std::make_unique<tcp_master_connection>(ep)),
      session_queue_(session_queue)
{ }

void listener::impl::on_connected
(slave_connection* connection)
{
    base_session* new_session = new session_handler(connection);
    session_queue_.push(new_session);
    new_session->start();

    std::cout << "on_connected" << std::endl;
}

void listener::impl::on_connection_error
(const connection_error& error)
{
    std::cout << "on_connection_error" << error.what() << std::endl;
}

void listener::impl::run(cancellation_token& token)
{
    while(token)
    {
        master_connection_->listen_connection();
    }
}

listener::listener(endpoint_unique_ptr &ep,
    thread_save_queue<base_session*>& session_queue)
    : d_(std::make_unique<impl>(ep, session_queue))
{
    d_->master_connection_->connected_callback
            (std::bind(&listener::impl::on_connected,
                       d_.get(), std::placeholders::_1));
    d_->master_connection_->error_callback
            (std::bind(&listener::impl::on_connection_error,
                       d_.get(), std::placeholders::_1));
    //open connection
    d_->master_connection_->open_connection();

    //set option
    d_->master_connection_->set_reusaddr();
    d_->master_connection_->set_nonblock();
}

listener::~listener()
{ }

void listener::start()
{
    d_->thread_ = std::make_unique<joinable_thread>
            (std::bind(&listener::impl::run, d_.get(),
                       std::placeholders::_1));
}
void listener::stop()
{
    d_->master_connection_->close_connection();
    d_->thread_->interrupt();
}
