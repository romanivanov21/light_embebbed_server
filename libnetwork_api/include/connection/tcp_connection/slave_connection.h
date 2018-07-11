/**
 *  Файл: slave_connection.h
 *
 *  Описание: общий интерфейс взалимодействия с клиентом, через сокет клиента
 *
 *  Автор: Иванов Роман Витальевич (с)
 */

#ifndef _SLAVE_CONNECTION_H_
#define _SLAVE_CONNECTION_H_

//internal
#include "event.h"
#include "byte_vector.h"

//std
#include <vector>
#include <string>

namespace network
{
    class slave_connection
    {
    public:
        using receive_data_ready_callback =
            std::function<void>;
    public:
        slave_connection() = default;

        virtual ~slave_connection() = default;

        virtual std::int64_t send_data
          (const byte_vector&) noexcept = 0;

        virtual std::int64_t send_data
            (const std::string&) noexcept = 0;

        virtual std::int64_t read_data(byte_vector&) = 0;

        virtual std::int64_t read_data(std::string&) = 0;

        virtual int get_socket() const noexcept = 0;

        void receive_data_callback(receive_data_ready_callback const& f)
        {
            //data_ready.connect(f);
        }

        slave_connection(const slave_connection&) = delete;

        slave_connection& operator=(const slave_connection&) = delete;

        slave_connection(slave_connection&&) = default;

        slave_connection& operator=(slave_connection&&) = default;

    public:
        /**
         * @brief соединение разорвано
         */
        event<void> disconnected;

        event<void> data_ready;
    };
}

#endif //_CLIENT_CONNECTION_H_
