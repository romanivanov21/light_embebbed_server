#ifndef _CANCELLATION_GUARD_H_
#define _CANCELLATION_GUARD_H_

#include "cancellation_token.h"
#include "cancellation_handler.h"

#include <cassert>

class cancellation_guard
{
public:
    using token = cancellation_token;
    using handler_ptr = cancellation_handler*;

    cancellation_guard(token& t, handler_ptr);
    ~cancellation_guard();

    cancellation_guard(const cancellation_guard&) = delete;
    cancellation_guard& operator=(const cancellation_guard&) = delete;
private:
    token& t_;
    handler_ptr h_;
};

#endif //_CANCELLATION_GUARD_H_
