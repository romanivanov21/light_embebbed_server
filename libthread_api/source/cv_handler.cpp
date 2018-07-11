// internal
#include "cv_handler.h"
#include "cancellation_guard.h"

#include <mutex>

struct cv_handler::impl
{
    impl(std::condition_variable& condition, std::mutex& lock)
        : condition_(condition), lock_(lock) { }

    std::condition_variable& condition_;
    std::mutex& lock_;
};

cv_handler::cv_handler(std::condition_variable& condition,
                       std::mutex& lock)
    : d_(std::make_unique<cv_handler::impl>(condition, lock)) { }

cv_handler::~cv_handler() = default;

void cv_handler::cancel()
{
    std::unique_lock<std::mutex> lk(d_->lock_);
    d_->condition_.notify_all();
}
