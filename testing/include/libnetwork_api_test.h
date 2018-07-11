#ifndef _LIBNETWORK_API_TEST_H_
#define _LIBNETWORK_API_TEST_H_

// external testing library headres
#include "test_network_api.h"
#include "endpoint.h"
#include "endpoint_ipv4.h"
#include "connection_traits.h"
#include "master_connection.h"
#include "tcp_master_connection.h"
#include "slave_connection.h"
#include "connection_error.h"
#include "selector_traits.h"
#include "base_selector.h"
#include "selector_epoll.h"

// std
#include <memory>
#include <string>
#include <functional>
#include <iostream>

//class test_connection
//{
//public:
//    test_connection(network::selector_epoll* selector)
//    {
//        selector_ = selector;
//    }

//    void on_connected(const network::slave_connection_shared_ptr& connection)
//    {
//        selector_->add_connection(connection);
//        std::cout << "on_connected" << std::endl;
//    }

//    void on_connection_error(const network::connection_error& error)
//    {
//        std::cout << "on_connection_error" <<  error.what() << std::endl;
//    }

//    void on_disconnected()
//    {
//        std::cout << "on_disconnected" << std::endl;
//    }

//    void on_timeout()
//    {
//        std::cout << "on_timeout" << std::endl;
//    }

//private:
//    network::selector_epoll* selector_;
//};

TEST(enpoint_v4, libnetwork_api)
{
    // enpoint IPv4 testing default ip address
    network::connection_port port = 8080;
    network::endpoint_unique_ptr ep1 =
            std::make_unique<network::endpoint_ipv4>(port);
    ASSERT_EQ(ep1->get_ip_address(), "0.0.0.0");
    ASSERT_EQ(ep1->get_port(), port);
    ASSERT_EQ(ep1->get_domain(), AF_INET);
    ASSERT_EQ(ep1->get_protocol(), IPPROTO_TCP);
    ASSERT_EQ(ep1->get_type(), SOCK_STREAM);

    // endpoint IPv4 testing seted ip address
    auto ip_address = "127.0.0.1";
    network::endpoint_unique_ptr ep2 =
            std::make_unique<network::endpoint_ipv4>(ip_address, port);
    ASSERT_EQ(ep2->get_ip_address(), ip_address);
    ASSERT_EQ(ep2->get_port(), port);
    ASSERT_EQ(ep2->get_domain(), AF_INET);
    ASSERT_EQ(ep2->get_protocol(), IPPROTO_TCP);
    ASSERT_EQ(ep2->get_type(), SOCK_STREAM);
}

TEST(tcp_master_connection, libnetwork_api)
{
//    network::selector_epoll selector;

//    test_connection test(&selector);

//    //create enpoin with ip addres and port
//    network::connection_port port = 8080;
//    auto ip_address = "127.0.0.1";
//    network::endpoint_unique_ptr ep =
//            std::make_unique<network::endpoint_ipv4>
//            (ip_address, port);
//    //create tcp connection object
//    network::master_connection_unique_ptr master_connection =
//            std::make_unique<network::tcp_master_connection>(ep);

//    //register callbacks
//    master_connection->connected_callback
//            (std::bind(&test_connection::on_connected,
//                       &test, std::placeholders::_1));
//    master_connection->error_callback
//            (std::bind(&test_connection::on_connection_error,
//                       &test, std::placeholders::_1));
//    master_connection->disconnected_callback
//            (std::bind(&test_connection::on_disconnected,
//                       &test));
//    master_connection->timeout_callback
//            (std::bind(&test_connection::on_timeout,
//                       &test));

//    //open connection
//    master_connection->open_connection();

//    //set option
//    master_connection->set_reusaddr();
//    master_connection->set_nonblock();

//    while(1)
//    {
//        //listen connection
//        master_connection->listen_connection();
//        selector.check_data_ready(10, 50);
//    }
}

#endif //_LIBNETWORK_API_TEST_H_
