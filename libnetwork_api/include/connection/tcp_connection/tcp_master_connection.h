#ifndef _TCP_MASTER_CONNECTION_H_
#define _TCP_MASTER_CONNECTION_H_

//internal
#include "connection_traits.h"
#include "master_connection.h"

namespace network
{
    class tcp_master_connection : public network::master_connection
    {
    public:
        explicit tcp_master_connection(endpoint_unique_ptr&);

        ~tcp_master_connection() final;

        void open_connection() override;

        void listen_connection() noexcept;

        void set_timeout(const connection_timeout& t) override;

        void set_reusaddr() override;

        void set_nonblock() override;

        bool is_connection_nonblock() const;

        void close_connection() override;

        tcp_master_connection
          (const tcp_master_connection& other) = delete;

        tcp_master_connection& operator=
          (const tcp_master_connection& other) = delete;

        tcp_master_connection(tcp_master_connection&& other) = default;

        tcp_master_connection& operator=(tcp_master_connection&& other) = default;

    private:
        tcp_master_connection();

    private:
        class impl;
        std::unique_ptr<impl> d_;
    };

} //namespace

#endif //_TCP_MASTER_CONNECTION_H_
