/**
 *  @file config_traits.h
 *
 *  @brief Структура, содержащий инфломации из конфиг файла
 *
 */

#ifndef _CONFIG_TRAITS_H_
#define _CONFIG_TRAITS_H_

// posix
#ifdef __linux__
#include <netinet/in.h>
#include <arpa/inet.h>
#endif //__linux__

// std
#include <string>
#include <map>
#include <vector>

#define CONFIG_INIT(FILE_NAME) config::server_config_mananger \
                               ::instance()->cfg_file_load<config \
                               ::yaml_config_parser>(FILE_NAME)

#define GET_CONFIG() config::server_config_mananger \
                        ::instance()->get_config()

namespace config
{
    /* Структра для харнения основную конфигурацию сервера */
    struct config_server
    {
        /* Структра для хранения инцормации о сетевом соединении */
        struct server_connection
        {
            /* Перечисление для опеределения валидности конфигурации ip_version */
            enum class ip_version_type : std::uint8_t { CONFIG_IPv4 = 4, CONFIG_IPv6 = 6 };

            static bool is_valid_ip_address(const std::string&, ip_version_type);

            ip_version_type ip_version_;      // версия ip адреса
            std::string ip_address_;          // ip адрес
            std::uint16_t listen_;            // порт, на котором принимаются входящие соединение
        };

        /* Структра для хранения основных диркторий сервера */
        struct server_directories
        {
            std::string document_root_;       // корневая директория сервера
        };

        /* Струтра для хранения информации о лог файлах */
        struct server_logs
        {
            std::string error_log_;           // директория до файла логирования ошибок
            std::string access_log_;          // директория до файла логирования выполненных действий
        };

        std::string name_;                    // доменное имя сервера
        server_connection connection_;
        server_directories directories_;
        server_logs logs_;
    };

    /* Структра для хранения конфигураций дополнительных модулей сервера */
    struct config_modules
    {
        std::map<std::string, std::string> mod_; // информация о дополнительных модулях ( имя и директория конфиг файла)
    };

    /* Основная структрадля хранения информации из конфигурационного файла сервера */
    struct config_struct
    {
        config_server server_;                // конфигурация сервера
        config_modules modules_;              // конфигурация дополниельных модулей
    };

} //namespace

#endif //_CONFIG_TRAITS_H_
