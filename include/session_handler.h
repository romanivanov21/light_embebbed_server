#ifndef _SESSION_HANDLER_H_
#define _SESSION_HANDLER_H_

#include "base_session.h"
#include "connection_traits.h"

class session_handler : public network::base_session
{
public:
    session_handler(network::slave_connection*);
    ~session_handler() override;

    void start() final;

    const network::slave_connection*
                   get_slave_connection() const;

private:
    void on_data_ready();

private:
    struct impl;
    std::unique_ptr<impl> d_;
};

#endif //_SESSION_HANDLER_H_
