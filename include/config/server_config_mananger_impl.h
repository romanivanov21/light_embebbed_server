#ifndef _SERVER_CONFIG_MANANGER_IMPL_H_
#define _SERVER_CONFIG_MANANGER_IMPL_H_

#include "yaml.h"

namespace config
{
    server_config_mananger* server_config_mananger::instance()
    {
        static server_config_mananger obj;
        return &obj;
    }

    template <typename Parser>
    bool server_config_mananger::cfg_file_load
      (const std::string& file_name)
    {
        Parser p;
        return p.parse(file_name, cfg_);
    }

    const config_server& server_config_mananger::get_config() const
    {
        return cfg_;
    }

} //namespace

#endif //_SERVER_CONFGI_MANANGER_IMPL_H_
