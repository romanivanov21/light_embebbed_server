#ifndef _SERVER_CONFIG_MANANGER_H_
#define _SERVER_CONFIG_MANANGER_H_

#include "config_traits.h"

namespace config
{
    class server_config_mananger
    {
    public:
        // C++11 the static varible is thread-safe
        static server_config_mananger* instance();

        template <typename Parser>
        bool cfg_file_load(const std::string&);

        const config_server& get_config() const;
    private:
        server_config_mananger() = default;

    private:
        config::config_server cfg_;
    };

} // namespcae

#endif //_SERVER_CONFIG_MANANGER_H_

/* impl header file */
#include "server_config_mananger_impl.h"
