#ifndef _JOINABLE_THREAD_TRAITS_H_
#define _JOINABLE_THREAD_TRAITS_H_

// std
#include <vector>
#include <memory>

namespace sys
{
    class joinable_thread;

    using joinable_thread_ptr = joinable_thread*;
    using joinable_thread_unique_ptr = std::unique_ptr<joinable_thread>;
    using joinable_thread_pool = std::vector<joinable_thread>;

} // sys

#endif //_JOINABLE_THREAD_TRAITS_H_
