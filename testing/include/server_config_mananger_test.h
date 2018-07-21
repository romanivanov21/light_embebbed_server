#ifndef _SERVER_CONFIG_MANANGER_TEST_H_
#define _SERVER_CONFIG_MANANGER_TEST_H_

//internal
#include "server_config_mananger.h"
#include "yaml_config_parser.h"

//common
#include "directory.h"

//gtest
#include <gtest/gtest.h>

//std
#include <string>
#include <fstream>

TEST(config001, server_config_mananger)
{
    config::config_server cfg1 { };
    cfg1.name_ = "web_server.ru";
    cfg1.connection_.ip_version_ = config::config_server::server_connection
            ::ip_version_type::CONFIG_IPv4;
    cfg1.connection_.ip_address_ = "192.168.0.1";
    cfg1.connection_.listen_ = 8080;
    cfg1.directories_.document_root_ = "/var/www/light_embedded_server";
    cfg1.logs_.access_log_ = "/var/www/log/access/light_embedded_server";
    cfg1.logs_.error_log_ = "/var/www/log/error/light_embedded_server";
    const std::string data = "Server:\n"
      " Name: '" + cfg1.name_ + "'\n"
      "\n"
      " Connection:\n"
      "  ip_version: '" + std::to_string
      (static_cast<std::uint8_t>(cfg1.connection_.ip_version_)) + "'\n"
      "  ip_address: '" + cfg1.connection_.ip_address_ + "'\n"
      "  listen: '" + std::to_string(cfg1.connection_.listen_) + "'\n"
      "\n"
      " Directories:\n"
      "  document_root: '"+ cfg1.directories_.document_root_ + "'\n"
      "\n"
      " Logs:\n"
      "  error_log: '" + cfg1.logs_.error_log_ + "'\n"
      "  access_log: '" + cfg1.logs_.access_log_ + "'\n"
      "\n";
    const std::string filename = "test_server_config.yaml";
    std::ofstream fout("test_server_config.yaml");
    fout << data;
    fout.close(); // закрываем файл

    CONFIG_INIT(sys::directory::get_current_directory() + "/" + filename);
    const auto& cfg2 = GET_CONFIG();
    ASSERT_EQ(cfg2.name_, cfg1.name_);
    ASSERT_EQ(cfg2.connection_.ip_version_, cfg1.connection_.ip_version_);
    ASSERT_EQ(cfg2.connection_.ip_address_, cfg1.connection_.ip_address_);
    ASSERT_EQ(cfg2.connection_.listen_, cfg1.connection_.listen_);
    ASSERT_EQ(cfg2.directories_.document_root_, cfg1.directories_.document_root_);
    ASSERT_EQ(cfg2.logs_.access_log_, cfg1.logs_.access_log_);
    ASSERT_EQ(cfg2.logs_.error_log_, cfg1.logs_.error_log_);
}

#endif //_SERVER_CONFIG_MANANGER_TEST_H_