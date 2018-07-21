// internal
#include "yaml_config_parser.h"

// external library yaml-cpp
#include "yaml.h"

// std
#include <cassert>

using config::yaml_config_parser;

bool yaml_config_parser::parse(const std::string& filename,
                               config_server& cfg) noexcept
{
    assert(!filename.empty());

    try
    {
        YAML::Node yaml_parser = YAML::LoadFile(filename);
        cfg.name_ = yaml_parser["Server"]["Name"].as<std::string>();
        cfg.connection_.ip_version_
          = static_cast<config::config_server::server_connection::ip_version_type>
        (yaml_parser["Server"]["Connection"]["ip_version"].as<int>());
        cfg.connection_.ip_address_
          = yaml_parser["Server"]["Connection"]["ip_address"].as<std::string>();
        cfg.connection_.listen_
          = yaml_parser["Server"]["Connection"]["listen"].as<std::uint16_t>();
        cfg.directories_.document_root_
          = yaml_parser["Server"]["Directories"]["document_root"].as<std::string>();
        cfg.logs_.access_log_
          = yaml_parser["Server"]["Logs"]["access_log"].as<std::string>();
        cfg.logs_.error_log_
          = yaml_parser["Server"]["Logs"]["error_log"].as<std::string>();

        return true;
    }
    catch(...)
    {
        return false;
    }
}