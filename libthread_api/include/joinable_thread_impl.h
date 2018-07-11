/**
 * @file joinable_therad_impl.h
 *
 * @brief implementation templates methods
 *
 * @author Ivanov R. V. 2018 (c)
 */
#ifndef _JOINABLE_THREAD_IMPL_H_
#define _JOINABLE_THREAD_IMPL_H_

namespace sys
{
    template <class Function, class... Args>
    joinable_thread::joinable_thread(Function&& f, Args&&... args)
    {
        impl_ = std::thread(std::forward<Function>(f), std::forward<Args>(args)...,
                        std::ref(token_));
    }

} //namespace

#endif //_JOINABLE_THREAD_IMPL_H_
