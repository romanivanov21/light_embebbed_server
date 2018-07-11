/**
 *  @file: thread_save_queue.h
 *
 *  @class thrad_safe_queue
 *
 *  @brief the thread safe queue, support the RAII thread class joinable_thread
 *
 *  @author: Ivanov R. V. (c) 2018
 *
 */

#ifndef _THREAD_SAVE_QUEUE_H_
#define _THREAD_SAVE_QUEUE_H_

#include "cv_handler.h"
#include "cancellation_token.h"
#include "cancellation_guard.h"

#include <memory>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace sys
{
    template <typename T, typename Container = std::queue<T> >
    class thread_save_queue
    {
    public:
        /**
         *   @brief получение элемента из очереди, ожидается пока очередь пустая
         *
         *   @param value ссылка на переменную, куда будет записан элемент из очереди
         */
        void wait_and_pop(T& value);

        /**
         *   @brief получение элемента из очереди, ожидается пока очередь пустая
         *
         *   @param value ссылка на переменную, куда будет записан элемент из очереди
         */
        bool wait_and_pop(T& value, cancellation_token& token);

        /**
         *   @brief попоытка получения элемента из очереди
         *
         *   @param value ссылка на переменную, куда будет записан элмемн из очереди
         *
         *   @return true если элемент удалось получить из очереди, false - иначе ( очередь пустая )
         */
        bool try_pop(T& value);

        /**
         *   @brief получение элемента из очереди, ожидается пока очередь пустая
         *
         *   @return shared_ptr куда будет записан элемент из очереди
         */
        std::shared_ptr<T> wait_and_pop(cancellation_token& token);

        /**
         *   @brief получение элемента из очереди, ожидается пока очередь пустая
         *
         *   @return shared_ptr куда будет записан элемент из очереди
         */
        std::shared_ptr<T> wait_and_pop();

        /**
         *   @brief попоытка получения элемента из очереди
         *
         *   @return sstd::hared_ptr если элемент удалось получить из очереди, false std::shared_ptr
         *           будут содержать nullptr ( очередь пустая )
         */
        std::shared_ptr<T> try_pop();

        /**
         *   @brief зписать переменную в очередь
         *
         *   @param new_value значение
         */
        void push(T new_value);

        /**
         *   @brief проверка очередь не пустая
         *
         *   @return truе, если очередь содержит элементы, false - иначе
         */
        bool empty() const;

    private:
        mutable std::mutex            mut_;
        Container              data_queue_;
        std::condition_variable data_cond_;
    };
} // namespace

#endif //_THREAD_SAVE_QUEUE_H_

#include "thread_safe_queue_impl.h"
