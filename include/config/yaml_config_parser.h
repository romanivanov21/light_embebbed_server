#ifndef _YAML_CONFIG_PARSER_H_
#define _YAML_CONFIG_PARSER_H_

#include "base_config_parser.h"

namespace config
{
    class yaml_config_parser : public base_config_parser
    {
    public:
        bool parse(const std::string&, config_server&) noexcept;
    };
}

#endif //_YAML_CONFIG_PARSER_H_