#ifndef _SERVER_CONFIG_MANANGER_TEST_H_
#define _SERVER_CONFIG_MANANGER_TEST_H_

//internal
#include "server_config_mananger.h"
#include "yaml_config_parser.h"

//common
#include "directory.h"

//thread_api
#include "joinable_thread.h"

//gtest
#include <gtest/gtest.h>

//std
#include <string>
#include <fstream>

class cfg_test
{
public:
    cfg_test()
    {
        // set default config data
        cfg_.name_ = "web_server.ru";
        cfg_.connection_.ip_version_ = config::config_server::server_connection
        ::ip_version_type::CONFIG_IPv4;
        cfg_.connection_.ip_address_ = "192.168.0.1";
        cfg_.connection_.listen_ = 8080;
        cfg_.directories_.document_root_ = "/var/www/light_embedded_server";
        cfg_.logs_.access_log_ = "/var/www/log/access/light_embedded_server";
        cfg_.logs_.error_log_ = "/var/www/log/error/light_embedded_server";

        create_test_config_file();
    }

    const config::config_server get_config() const { return cfg_; }

    void set_config(const config::config_server& cfg)
    {
        cfg_ = cfg;
        create_test_config_file();
    }

private:
    void create_test_config_file()
    {
        const std::string data = "Server:\n"
                                        " Name: '" + cfg_.name_ + "'\n"
                                        "\n"
                                        " Connection:\n"
                                        "  ip_version: '" + std::to_string
                                        (static_cast<std::uint8_t>(cfg_.connection_.ip_version_)) + "'\n"
                                        "  ip_address: '" + cfg_.connection_.ip_address_ + "'\n"
                                        "  listen: '" + std::to_string(cfg_.connection_.listen_) + "'\n"
                                        "\n"
                                        " Directories:\n"
                                        "  document_root: '"+ cfg_.directories_.document_root_ + "'\n"
                                        "\n"
                                        " Logs:\n"
                                        "  error_log: '" + cfg_.logs_.error_log_ + "'\n"
                                        "  access_log: '" + cfg_.logs_.access_log_ + "'\n"
                                        "\n";
        std::ofstream fout(filename_);
        fout << data;
        fout.close(); // закрываем файл

        CONFIG_INIT(sys::directory::get_current_directory() + "/" + filename_);
    }
private:
    const std::string filename_ = "test_server_config.yaml";
    config::config_server cfg_ { };
};

cfg_test test;

void cmp_config(const config::config_server& cfg1, const config::config_server& cfg2)
{
    ASSERT_EQ(cfg2.name_, cfg1.name_);
    ASSERT_EQ(cfg2.connection_.ip_version_, cfg1.connection_.ip_version_);
    ASSERT_EQ(cfg2.connection_.ip_address_, cfg1.connection_.ip_address_);
    ASSERT_EQ(cfg2.connection_.listen_, cfg1.connection_.listen_);
    ASSERT_EQ(cfg2.directories_.document_root_, cfg1.directories_.document_root_);
    ASSERT_EQ(cfg2.logs_.access_log_, cfg1.logs_.access_log_);
    ASSERT_EQ(cfg2.logs_.error_log_, cfg1.logs_.error_log_);
}

TEST(config001, server_config_mananger)
{
    cmp_config(test.get_config(), GET_CONFIG());
}

void thread1_function(cancellation_token& token)
{
    cmp_config(test.get_config(), GET_CONFIG());
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cmp_config(test.get_config(), GET_CONFIG());
    std::this_thread::sleep_for(std::chrono::seconds(4));
    cmp_config(test.get_config(), GET_CONFIG());
}
void thread2_function(cancellation_token& token)
{
    cmp_config(test.get_config(), GET_CONFIG());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cmp_config(test.get_config(), GET_CONFIG());
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cmp_config(test.get_config(), GET_CONFIG());
}

void thread3_function(cancellation_token& token)
{
    config::config_server cfg_test;
    cfg_test.name_ = "web_server1.ru";
    cfg_test.connection_.ip_version_ = config::config_server::server_connection
    ::ip_version_type::CONFIG_IPv4;
    cfg_test.connection_.ip_address_ = "192.168.0.2";
    cfg_test.connection_.listen_ = 8081;
    cfg_test.directories_.document_root_ = "/var/www/light_embedded_server1";
    cfg_test.logs_.access_log_ = "/var/www/log/access/light_embedded_server1";
    cfg_test.logs_.error_log_ = "/var/www/log/error/light_embedded_server1";
    test.set_config(cfg_test);
    cfg_test.name_ = "web_server2.ru";
    cfg_test.connection_.ip_version_ = config::config_server::server_connection
    ::ip_version_type::CONFIG_IPv4;
    cfg_test.connection_.ip_address_ = "192.168.0.2";
    cfg_test.connection_.listen_ = 8081;
    cfg_test.directories_.document_root_ = "/var/www/light_embedded_server2";
    cfg_test.logs_.access_log_ = "/var/www/log/access/light_embedded_server2";
    cfg_test.logs_.error_log_ = "/var/www/log/error/light_embedded_server2";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    test.set_config(cfg_test);
    cfg_test.name_ = "web_server3.ru";
    cfg_test.connection_.ip_version_ = config::config_server::server_connection
    ::ip_version_type::CONFIG_IPv4;
    cfg_test.connection_.ip_address_ = "192.168.0.3";
    cfg_test.connection_.listen_ = 8083;
    cfg_test.directories_.document_root_ = "/var/www/light_embedded_server3";
    cfg_test.logs_.access_log_ = "/var/www/log/access/light_embedded_server3";
    cfg_test.logs_.error_log_ = "/var/www/log/error/light_embedded_server3";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    test.set_config(cfg_test);
    cfg_test.name_ = "web_server4.ru";
    cfg_test.connection_.ip_version_ = config::config_server::server_connection
    ::ip_version_type::CONFIG_IPv4;
    cfg_test.connection_.ip_address_ = "192.168.0.4";
    cfg_test.connection_.listen_ = 8081;
    cfg_test.directories_.document_root_ = "/var/www/light_embedded_server4";
    cfg_test.logs_.access_log_ = "/var/www/log/access/light_embedded_server4";
    cfg_test.logs_.error_log_ = "/var/www/log/error/light_embedded_server4";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    test.set_config(cfg_test);
}

TEST(config002, server_config_mananger)
{
    sys::joinable_thread thread1(thread1_function);
    sys::joinable_thread thread2(thread2_function);
    sys::joinable_thread thread3(thread3_function);

}

#endif //_SERVER_CONFIG_MANANGER_TEST_H_