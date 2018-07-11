#ifdef __linux__

//internal
#include "selector_epoll.h"
#include "slave_connection.h"

//std
#include <cassert>

//linux
#include <sys/epoll.h>

using network::selector_epoll;
using network::slave_connection_shared_ptr;
using network::slave_connection;
using network::base_session;

struct selector_epoll::impl
{
    bool add_epoll(int fd) noexcept;
    bool delete_epoll(int fd) noexcept;

    std::map<int, base_session*> sessions_ { };
    int epoll_ = 0;
    std::vector<epoll_event> events_ { };
};

selector_epoll::selector_epoll() : d_(std::make_unique<impl>())
{
    if(!d_) return;

    d_->epoll_ = epoll_create1(0);
}

selector_epoll::~selector_epoll() { }

void selector_epoll::add_connection
  (base_session* session) noexcept
{
    assert(session != nullptr);
    if(session == nullptr) return;

    int socket = session->get_slave_connection()->get_socket();
    if(d_->add_epoll(socket))
    {
        std::pair<int, base_session*>
          item(socket, session);
        d_->sessions_.insert(item);
    }
    else
    {
        error.emit(selector_error::ADD_ERROR);
    }
}

void selector_epoll::delete_connection
  (base_session* session) noexcept
{
    assert(session != nullptr);
    if(session == nullptr) return;

    const slave_connection* connection
            = session->get_slave_connection();
    if(connection == nullptr) return;
    int socket = connection->get_socket();
    if(d_->delete_epoll(socket))
        d_->sessions_.erase(socket);
    else
        error.emit(selector_error::DELETE_ERROR);
}

void selector_epoll::delete_all_connection() noexcept
{
    for(auto it = d_->sessions_.begin(); it != d_->sessions_.end(); ++it)
    {
        delete_connection(it->second);
    }
}

void selector_epoll::check_data_ready
  (int max_event, int wait_timeout) noexcept
{
    if(max_event <= 0) return;

    d_->events_.resize(static_cast<std::size_t>(max_event));
    int n = epoll_wait(d_->epoll_, d_->events_.data(),
                       max_event, wait_timeout);
    if(n <= 0) return;

    if(errno != EAGAIN) error.emit(selector_error::UNKNOWN_ERROR);

    for(size_t i = 0; i < n; i++)
        data_ready.emit
          (d_->sessions_[d_->events_[i].data.fd]);
}

bool selector_epoll::impl::add_epoll(int fd) noexcept
{
    bool result = false;
    if(fd > 0)
    {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = EPOLLIN;
        if(epoll_ctl(epoll_, EPOLL_CTL_ADD, fd, &event) != default_error_code)
            result = true;
    }
    return result;
}

bool selector_epoll::impl::delete_epoll(int fd) noexcept
{
    bool result = false;
    if(fd > 0)
    {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = EPOLLIN;
        result = (epoll_ctl(epoll_, EPOLL_CTL_DEL, fd, &event) == 0);
    }
    return result;
}

#endif //__linux__
