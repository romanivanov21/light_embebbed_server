//internal
#include "tcp_slave_connection.h"
#include "endpoint.h"

//linux
#include <unistd.h> // close()

using namespace network;

struct tcp_slave_connection::impl
{
    int slave_socket_;
    endpoint_unique_ptr ep_;
};

tcp_slave_connection::tcp_slave_connection
  (int slave_socket, endpoint_unique_ptr& ep) :
    d_(std::make_unique<impl>())
{
    if(!d_) return;
    d_->ep_ = std::move(ep); d_->slave_socket_ = slave_socket;
}

tcp_slave_connection::~tcp_slave_connection()
{
    close(d_->slave_socket_);
    disconnected.emit();
}

std::int64_t tcp_slave_connection::send_data
(const std::string& data) noexcept
{
    return send(d_->slave_socket_, data.data(), data.size(), MSG_NOSIGNAL);
}

std::int64_t tcp_slave_connection::send_data
(const std::vector<byte>& data) noexcept
{
    return send(d_->slave_socket_, data.data(), data.size(), MSG_NOSIGNAL);
}

std::int64_t tcp_slave_connection::read_data(byte_vector &data)
{
    std::int64_t res = -1;
    if(data.size() > 0)
        res = recv(d_->slave_socket_, &data[0], data.size(), MSG_NOSIGNAL);
    return res;
}

std::int64_t tcp_slave_connection::read_data(std::string& data)
{
    std::int64_t res = -1;
    if(data.size() > 0)
        res = recv(d_->slave_socket_, &data[0], data.size(), MSG_NOSIGNAL);
    return res;
}

int tcp_slave_connection::get_socket() const noexcept { return d_->slave_socket_; }
