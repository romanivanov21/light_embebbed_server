#ifndef _CV_HANDLER_H_
#define _CV_HANDLER_H_

//internal
#include "cancellation_handler.h"
#include "cancellation_token.h"
#include "cancellation_guard.h"

//std
#include <memory>
#include <condition_variable>
#include <mutex>

class cv_handler : public cancellation_handler
{
public:
    cv_handler(std::condition_variable&,
               std::mutex&);
    virtual ~cv_handler();
    virtual void cancel() override;

    template <typename Predicate>
    static void cancellable_wait(std::condition_variable& cv, std::unique_lock<std::mutex>& lk,
                                 cancellation_token& t, Predicate p)
    {
        cancellation_guard guard(t, new cv_handler(cv, *lk.mutex()));
        cv.wait(lk, p);
    }

    cv_handler(const cv_handler& other) = delete;
    cv_handler& operator=(const cv_handler& other) = delete;
private:
    struct impl;
    std::unique_ptr<impl> d_;
};

#endif //_CV_HANDLER_H_
