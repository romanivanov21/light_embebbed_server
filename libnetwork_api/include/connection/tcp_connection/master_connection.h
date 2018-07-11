#ifndef _MASTER_CONNECTION_H_
#define _MASTER_CONNECTION_H_

//internal
#include "event.h"
#include "connection_traits.h"
#include "connection_timeout.h"

namespace network
{
    class master_connection
    {
    public:
        using connected_function =
        std::function<void(slave_connection*)>;

        using timeout_function = std::function<void()>;

        using connection_error_function
        = std::function<void(const connection_error&)>;

        using disconnected_function = std::function<void()>;

        master_connection() = default;

        virtual ~master_connection() = default;

        virtual void open_connection() = 0;

        virtual void listen_connection() noexcept = 0;

        virtual void set_nonblock() = 0;

        virtual void set_reusaddr() = 0;

        virtual void set_timeout(const connection_timeout&) = 0;

        virtual bool is_connection_nonblock() const = 0;

        virtual void close_connection() = 0;

        void connected_callback(connected_function const& f) noexcept;

        void timeout_callback(timeout_function const& f) noexcept;

        void error_callback(connection_error_function const& f) noexcept;

        void disconnected_callback(disconnected_function const& f) noexcept;

        master_connection(const master_connection&) = delete;

        master_connection& operator=(const master_connection&) = delete;

        master_connection(master_connection&&) = default;

        master_connection& operator=(master_connection&&) = default;

    protected:
        /**
         * @brief async connected client event
         */
        event<slave_connection*> connected;

        /**
         * @brief async connection timeout event
         */
        event<void> timeout;

        /**
         * @brief async connection error event
         */
        event<const connection_error&> error;

        /**
         * @brief async disconnection event
         */
        event<void> disconnected;
    };
}

#endif //_MASTER_CONNECTION_H_
