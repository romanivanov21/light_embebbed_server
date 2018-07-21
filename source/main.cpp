//internal
#include "tcp_server.h"
#include "yaml.h"
#include "server_config_mananger.h"
#include "server_config_parser.h"
#include "yaml_config_parser.h"

#include "directory.h"

//internal library
#include "endpoint.h"
#include "endpoint_ipv4.h"

#include <iostream>

int main(int argc, char** argv)
{
    CONFIG_INIT(sys::directory::get_current_directory() + "/server_config.yaml");
    const auto& cfg = GET_CONFIG();

//    network::endpoint_unique_ptr ep =
//            std::make_unique<network::endpoint_ipv4>
//            ("127.0.0.1", 8080);
//    tcp_server s(ep);
//    s.run();

	return 0;
}
