/**
 * @file cancellation_token.h
 *
 * @brief
 */

#ifndef _CANCELLATION_TOKEN_H_
#define _CANCELLATION_TOKEN_H_

// internal
#include "cancellation_handler.h"

//std
#include <memory>

class cancellation_token
{
public:
    cancellation_token();
    ~cancellation_token();

    explicit operator bool() const;

    void register_handler(cancellation_handler*);
    void unregister_handler();

    void cancel();

    cancellation_token(const cancellation_token&) = delete;
    cancellation_token& operator=(const cancellation_token&) = delete;
private:
    struct impl;
    std::unique_ptr<impl> d_;
};

#endif //_CANCELLATION_TOKEN_H_
