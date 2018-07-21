#include "config_traits.h"

bool config::config_server::server_connection::is_valid_ip_address
(const std::string& ip_address, ip_version_type version_type)
{
    bool res = false;
    struct sockaddr_in sa;
    if(version_type == ip_version_type::CONFIG_IPv4)
    {
        res = inet_pton(AF_INET, ip_address.c_str(), &(sa.sin_addr)) != 0;
    }
    else if(version_type == ip_version_type::CONFIG_IPv6)
    {
        res = inet_pton(AF_INET6, ip_address.c_str(), &(sa.sin_addr)) != 0;
    }
    return res;
}
