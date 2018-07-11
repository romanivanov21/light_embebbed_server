#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

//internal library network_api
#include "base_server.h"
#include "connection_traits.h"

//std
#include <memory>

class tcp_server : public network::base_server
{
public:
    tcp_server(network::endpoint_unique_ptr&);

    ~tcp_server() override;

    void run() override;

    void stop() override;

    tcp_server(const tcp_server&) = delete;

    tcp_server& operator=(const tcp_server&) = delete;

    tcp_server(tcp_server&&) = default;

    tcp_server& operator=(tcp_server&&) = default;
private:
    struct impl;
    std::unique_ptr<impl> d_;
};

#endif //_TCP_SERVER_H_
