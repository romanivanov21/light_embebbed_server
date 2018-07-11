#ifndef _CANCELLATION_HANDLER_H_
#define _CANCELLATION_HANDLER_H_

class cancellation_handler
{
public:
    virtual ~cancellation_handler() = default;

    virtual void cancel() = 0;
};

#endif // _CANCELLATION_HANDLER_H_
