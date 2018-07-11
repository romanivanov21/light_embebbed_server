#ifndef _LIBTHREAD_API_TEST_H_
#define _LIBTHREAD_API_TEST_H_

#include "joinable_thread_traits.h"
#include "joinable_thread.h"
#include "cancellation_token.h"
#include "cv_handler.h"
#include "cancellation_guard.h"
#include "thread_save_queue.h"
#include "function_wrapper.h"

#include <functional>

using namespace sys;

class worker
{
public:
    void work(thread_save_queue<std::function<void()>> & queue,
              cancellation_token& token)
    {
        while(token)
        {
            std::function<void()> f;
            if(queue.wait_and_pop(f, token)) f();
        }
        std::cout << "interrupt" << std::endl;
    }
};

/**
 * @brief testing correct interrupt threads
 *        by cancellation_token
 */
TEST(interrupt, thread_api_test)
{
    worker w;
    thread_save_queue<std::function<void()> > queue;

    joinable_thread worker_thread1(std::bind(&worker::work, &w,
                                             std::placeholders::_1,
                                             std::placeholders::_2),
                                   std::ref(queue));

    joinable_thread worker_thread2(std::bind(&worker::work, &w,
                                             std::placeholders::_1,
                                             std::placeholders::_2),
                                   std::ref(queue));

    joinable_thread worker_thread3(std::bind(&worker::work, &w,
                                             std::placeholders::_1,
                                             std::placeholders::_2),
                                   std::ref(queue));

    joinable_thread worker_thread4(std::bind(&worker::work, &w,
                                             std::placeholders::_1,
                                             std::placeholders::_2),
                                   std::ref(queue));

    queue.push([](){ std::cout << "task1" << std::endl; });
    queue.push([](){ std::cout << "task2" << std::endl; });
    queue.push([](){ std::cout << "task3" << std::endl; });
    queue.push([](){ std::cout << "task4" << std::endl; });
    std::this_thread::sleep_for(std::chrono::seconds(5));
    worker_thread1.interrupt();
    worker_thread2.interrupt();
    worker_thread3.interrupt();
    queue.push([](){ std::cout << "task5" << std::endl; });
    worker_thread4.interrupt();
    queue.push([](){ std::cout << "task2" << std::endl; });

    ASSERT_EQ(5, 5);
}


#endif // _LIBTHREAD_API_TEST_H_
