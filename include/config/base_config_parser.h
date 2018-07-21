#ifndef _BASE_CONFIG_PARSER_H_
#define _BASE_CONFIG_PARSER_H_

//internal
#include "config_traits.h"

//std
#include <string>

namespace config
{
    class base_config_parser
    {
    public:
        virtual bool parse(const std::string&, config_server&) noexcept = 0;
    };
}

#endif //_BASE_CONFIG_PARSER_H_