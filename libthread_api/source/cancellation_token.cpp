//internal
#include "cancellation_token.h"

//std
#include <condition_variable>
#include <atomic>
#include <mutex>
#include <memory>

struct cancellation_token::impl
{
    std::atomic<bool>      cancelled_ {false};
    mutable std::mutex                 mutex_;
    cancellation_handler*  handler_ {nullptr};
};

cancellation_token::cancellation_token()
    : d_(std::make_unique<impl>()) {}

cancellation_token::~cancellation_token() = default;

void cancellation_token::cancel()
{
    d_->cancelled_ = true;
    std::unique_lock<std::mutex> lk(d_->mutex_);
    if(d_->handler_ != nullptr)
    {
        d_->handler_->cancel();
    }
}

cancellation_token::operator bool() const
{ return !d_->cancelled_; }

void cancellation_token::register_handler
    (cancellation_handler* handler)
{
    std::unique_lock<std::mutex> lk(d_->mutex_);
    d_->handler_ = handler;
}

void cancellation_token::unregister_handler()
{
    std::unique_lock<std::mutex> lk(d_->mutex_);
    delete d_->handler_;
}
