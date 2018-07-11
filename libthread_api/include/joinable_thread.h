/**
 * @file joinable_thread.h
 *
 * @class joinable_thread
 *
 * @brief wrapper over the standart class
 *               std::thread to support the idiom RAII
 *        class is noncopyable
 *
 * @author Ivanov R. V. 2018 (c)
 */

#ifndef _JOINABLE_THREAD_H_
#define _JOINABLE_THREAD_H_

//internal
#include "cancellation_token.h"

//std
#include <thread>

namespace sys
{
    class joinable_thread
    {
    public:
        using id = std::thread::id;
        using native_handle_type = std::thread::native_handle_type;

    public:
        /**
         * @brief first parameter of therad callback function must be
         *        the reference to cancellation token
         */
         template <class Function, class... Args>
         explicit joinable_thread(Function&& f, Args&&... args);

        /**
         * @brief destructor call join()
         */
        ~joinable_thread();

        /**
         * @brief interrupt this thread
         */
        void interrupt();


        /**
         * @brief get this thread id
         *
         * @return this thrad id
         */
        id get_id() const noexcept;

        native_handle_type native_handle();


        /**
         * @brief wrapper over standart method of std::thread hardware_concurrency
         *
         * @return hardware concurrency thread count
        */
        static unsigned int hardware_concurrency() noexcept;

        /**
         * @brief this class is not copyble
         */
        joinable_thread(const joinable_thread& other) = delete;

        /**
         * @brief this class does not copyble and does not support operator =
         */
        joinable_thread& operator=(const joinable_thread& other) = delete;

    public:
        std::thread         impl_; /* this thread (C++11) */
        cancellation_token token_; /* customer token to correct interrupt this thread */
    };
}

#endif //_JOINABLE_THREAD_H_

/* include implementaion file with templates methods */
#include "joinable_thread_impl.h"
