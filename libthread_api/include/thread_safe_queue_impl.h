/**
 * @file thread_safe_queue_impl.h
 *
 * @class thrad_safe_queue
 *
 * @brief implementation template class thread_safe_queue mthods
 *
 * @author Ivanov R. V.
 *
 */

#ifndef _THREAD_SAFE_QUEUE_IMPL_H_
#define _THREAD_SAFE_QUEUE_IMPL_H_

namespace sys
{
    template <typename T, typename Container>
    void thread_save_queue<T, Container>::wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut_);
        data_cond_.wait(lk, [this] { return !data_queue_.empty(); });
        value = data_queue_.front();
        data_queue_.pop();
    }

    template <typename T, typename Container>
    bool thread_save_queue<T, Container>::wait_and_pop
        (T& value, cancellation_token& token)
    {
        std::unique_lock<std::mutex> lk(mut_);
        bool is_queue_empty = data_queue_.empty();
        cv_handler::cancellable_wait(data_cond_, lk, token,
                     [&] { return !is_queue_empty || !token; });
        if(!is_queue_empty)
        {
            value = data_queue_.front();
            data_queue_.pop();
            return true;
        }
        return false;
    }

    template <typename T, typename Container>
    bool thread_save_queue<T, Container>::try_pop( T& value )
    {
        std::lock_guard<std::mutex> lk( mut_ );
        if (data_queue_.empty())
            return false;
        value = data_queue_.front();
        data_queue_.pop();
        return true;
    }

    template <typename T, typename Container>
    std::shared_ptr<T> thread_save_queue<T, Container>::wait_and_pop
        (cancellation_token& token)
    {
        std::unique_lock<std::mutex> lk( mut_ );
        bool is_queue_empy = data_queue_.empty();
        cv_handler::cancellable_wait(data_cond_, lk, token,
                         [&] { return !is_queue_empy || !token; } );
        std::shared_ptr<T> res = nullptr;
        if(!is_queue_empy)
        {
            res = data_queue_.front();
            data_queue_.pop();
        }
        return res;
    }

    template <typename T, typename Container>
    std::shared_ptr<T> thread_save_queue<T, Container>::wait_and_pop()
    {
        std::unique_lock<std::mutex> lk( mut_ );
        data_cond_.wait( lk, [this] { return !data_queue_.empty(); } );
        std::shared_ptr<T> res = data_queue_.front();
        data_queue_.pop();
        return res;
    }

    template <typename T, typename Container>
    std::shared_ptr<T> thread_save_queue<T, Container>::try_pop()
    {
        std::shared_ptr<T> res = nullptr;
        std::lock_guard<std::mutex> lk( mut_ );
        if(data_queue_.empty())
        {
            res = data_queue_.front();
            data_queue_.pop();
        }
        return res;
    }

    template <typename T, typename Container>
    void thread_save_queue<T, Container>::push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut_);
        data_queue_.push(new_value);
        data_cond_.notify_one();
    }

    template <typename T, typename Container>
    bool thread_save_queue<T, Container>::empty() const
    {
        std::lock_guard<std::mutex> lk( mut_ );
        return data_queue_.empty();
    }

} //namespace

#endif //_THREAD_SAFE_QUEUE_IMPL_H_
