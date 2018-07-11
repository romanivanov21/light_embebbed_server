#include "session_handler.h"

//internal library network_api
#include "slave_connection.h"

//internal library common
#include "event.h"

//internal library http_api
#include "http_request_parser.h"

//std
#include <string>
#include <iostream> //for testing

using network::slave_connection;

struct session_handler::impl
{
    impl(slave_connection* connection_);

    void on_data_ready();

    slave_connection* connection_;
};

session_handler::impl::impl(slave_connection* connection)
    : connection_(connection) { }

session_handler::session_handler
    (slave_connection* connection)
        : d_(std::make_unique<impl>(connection))
{
}

session_handler::~session_handler()
{
    delete d_->connection_;
}

void session_handler::start()
{
    d_->connection_->data_ready.connect
            (std::bind(&session_handler::on_data_ready,
                       this));
}

void session_handler::on_data_ready()
{
    std::string request;
    request.resize(200);
    d_->connection_->read_data(request);

    http_request parse_request;
    http_request_parser parser;
    http_request_parser::request_parse_result result
            = parser.parse(request, parse_request);

    std::unordered_map<std::string, std::string> temp;

    if(result == http_request_parser
            ::request_parse_result::COMPLETE)
    {
        std::cout << parse_request.method_.c_str() << std::endl;
        std::cout << parse_request.uri_.c_str() << std::endl;

        for(auto it = parse_request.headers_.begin();
            it != parse_request.headers_.end(); ++it)
        {

        }
        d_->connection_->send_data("COMPLETE\n");
    }
    else
    {
        d_->connection_->send_data("BAD REQUEST\n");
    }

    end.emit(this);
    delete this;
}

const network::slave_connection*
    session_handler::get_slave_connection() const
{
    return d_->connection_;
}
