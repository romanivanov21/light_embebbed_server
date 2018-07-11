#include "cancellation_guard.h"

cancellation_guard::cancellation_guard
(token& t, handler_ptr h) : t_(t)
{
    assert(h != nullptr);
    t.register_handler(h);
}

cancellation_guard::~cancellation_guard()
{
    t_.unregister_handler();
}
